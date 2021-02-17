#include"Gameover.h"
#include"Game.h"
#include"KEYINPUT.H"
#include"Main.h"
#include"Score.h"
#include"player.h"

GameOver::GameOver() {
	_cx = 100;
	_show = false;
}

GameOver::~GameOver() {

}

void GameOver::Load() {
	_continue_image = LoadGraph("data/gameover/continue.png");
	_no_image= LoadGraph("data/gameover/no.png");
	_yes_image= LoadGraph("data/gameover/yes.png");
	_gameover_image = LoadGraph("data/gameover/GameOver.png");
	_text_image[0]= LoadGraph("data/result_txt.png");
	_text_image[1] = LoadGraph("data/result_txt.pad.png");
}


void GameOver::BoxRender() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawBox(100, 100, 540, 220, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawGraph(120, 120, _yes_image, true);
	DrawGraph(360, 120, _no_image, true);
	if (GetJoypadNum() == 0) {
		DrawGraph(240, 230, _text_image[0], true);
	}
	else
	{
		DrawGraph(240, 230, _text_image[1], true);
	}


	DrawGraph(180, 40, _continue_image, true);
	DrawLineBox(_cx, 100, _cx + 220, 220, GetColor(255, 255, 555));

	if (_show == true){
		DrawGraph(0, -50, _gameover_image, false);
	}

}

void GameOver::AddSceneCount() {
	if (_show == true)
	{
		_scene_counter++;
	}

}


void GameOver::MoveCursor() {


	if (GetJoypadInputState(DX_INPUT_PAD1) & (PAD_INPUT_RIGHT)) {

		if ((player._before_BIT & PAD_INPUT_RIGHT) == false) {
			if (_cx == 100)
				_cx += 220;
		}
	}

	if (GetJoypadInputState(DX_INPUT_PAD1) & (PAD_INPUT_LEFT)) {
		if ((player._before_BIT & PAD_INPUT_LEFT) == false) {
			
			if (_cx == 320)
				_cx -= 220;
		}
	}
	if (GetJoypadInputState(DX_INPUT_PAD1) & (PAD_INPUT_2)) {
		if ((player._before_BIT & PAD_INPUT_2) == false) {

			if (_cx == 100) {
				scene = GAME;
				ReStart();
			}
			else if (_cx == 320) {
				_show = true;
			}
		}
	}



	if (GetJoypadNum() != 0)return;

	if (IsKeyOn(KEY_INPUT_RIGHT)) {
		if(_cx==100)
		_cx += 220;
	
	}if (IsKeyOn(KEY_INPUT_LEFT)) {
		if (_cx == 320)
		_cx -= 220;
	}

	if (IsKeyOn(KEY_INPUT_RETURN)) {
		if (_cx == 100) {
			scene = GAME;
			ReStart();
		}
		else if (_cx == 320) {
			_show = true;
		}
	}
}


void GameOver::ChengeScene() {

	if (_scene_counter > 120) {
		
		_scene_counter = 0;
		_show = false;
		ReStart();
		scene = INPUT_NAME;
		
	}
}


void GameOver::Update() {


	MoveCursor();
	AddSceneCount();
	ChengeScene();

}

void GameOver::Draw() {
	BoxRender();

}




