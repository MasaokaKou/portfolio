#include"chenge2.h"
#include"Game.h"
#include"MAIN.H"
#include"KEYINPUT.H"
#include"player.h"

Chenge2::Chenge2() {
	_color = GetColor(0,0,0);

}

Chenge2::~Chenge2() {


}


void Chenge2::SetCirclePos() {
	_image[0] = LoadGraph("data/chenge2.png");
	_image[1] = LoadGraph("data/chenge2_pad.png");
	_x = WINDOW_W / 2;
	_y = WINDOW_H / 2;
	_r = 0;
	_blend = 255;
	}

void Chenge2::SetFlag() {
	start = false;
	_once = true;

}


void Chenge2::CircleRender() {
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _blend);
	DrawCircle(_x, _y, _r, _color);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (scene == CHENGE2 && start == true && _once == true) {
		//ジョイパッドがつながっていなければ
		if (GetJoypadNum() == 0) {
			DrawGraph(0, 0, _image[0], true);
		}
		else {
			DrawGraph(0, 0, _image[1], true);
		}
	

	}


}

void Chenge2::MoveCircle(){
	if (scene == CHENGE2) {
		if (GetJoypadInputState(DX_INPUT_PAD1) & (PAD_INPUT_2)) {
			if ((player._before_BIT & PAD_INPUT_2) == false) {
				start = false;
			}
		}

		if (GetJoypadNum() == 0) {
			if (IsKeyOn(KEY_INPUT_RETURN))
				start = false;
		}
		}


	if (scene == CHENGE2) {
		if (start == false) {
			_r += 5;
		}
	}



	if (scene == GAME) {
		if (_r >= 0) {
			_r -= 5;
			//_blend -= 2;
		}
	}

}




void Chenge2::ChengeScene() {
	if (_r == 390) {
		start = true;
	}

	

	if (scene==CHENGE2&&_r > 400) {
		scene = GAME;
	}

	if(scene==GAME)_once = false;

}
