#include"MainBase.h"
#include"Main.h"
#include"Game.h"
#include"Keyinput.h"
#include"player.h"
#include"title.h"
#include"sound.h"
#include"map.h"
Title title;

Title::Title() {
	counter = 0;
	true_title_move = true;
	door_check = false;
	door_counter = 0;
	chara_x = 1000;
	chara_y = 100;
	for (int i = 0; i < 5; i++) {
		chara_r[i] = 0.0;
	}
	chara_size = 1.3f;
	chara_counter = 0;
	chara2_y = -200;
	scene = TITLE;
	player.SetX(322);
	player.SetY(-10);
	//start_counter = 0;


}
Title::~Title() {
	//画像破棄
	DeleteGraph(title_image);
	for (int i = 0; i < 12; i++) {
		DeleteGraph(door_image[i]);
	}
	DeleteGraph(True_Title);
	DeleteGraph(title_r);
}


//画像読み込み
void Title::Load() {
	title_image = LoadGraph("data/picture/OPback.png");
	LoadDivGraph("data/door/door.png", 12, 3, 4, 86, 64, door_image);
	True_Title = LoadGraph("data/picture/title.png");
	title_chara_image[0] = LoadGraph("data/picture/title_chara1.png");
	title_chara_image[1] = LoadGraph("data/picture/title_chara2.png");
	title_chara_image[2] = LoadGraph("data/picture/title_chara3.png");
	title_chara_image[3] = LoadGraph("data/picture/title_chara4.png");
	title_chara_image[4] = LoadGraph("data/picture/title_chara5.png");
	subtitle_chara_image = LoadGraph("data/picture/title_chara.png");
	count_image[0] = LoadGraph("data/count/1.png");
	count_image[1] = LoadGraph("data/count/2.png");
	count_image[2] = LoadGraph("data/count/3.png");
	count_image[3] = LoadGraph("data/count/4.png");
	count_image[4] = LoadGraph("data/count/5.png");
	go= LoadGraph("data/count/go.png");

}

//タイトル落ちてくるようのカウンター増加
void Title::AddTitleCount() {
	counter++;
}
//ドアを開ける用のカウンター増加
void Title::AddDoorCount() {
	if (scene == SELECT && door_check == true || scene == CHENGE2 && door_check == true) door_counter++;

}
//ゲーム開始カウンター増加
void Title::AddStartCounter() {
	if (scene == GAME) {
		start_counter++;
	}
}

//タイトル画面描画
void Title::RenderTitle() {
	if (scene == TITLE) {
		DrawGraph(0, 0, True_Title, false);
	}
}
//初期画面
void Title::RenderTitle2() {
	if (scene == SELECT||scene==CHENGE2) {
		DrawGraph(0, 0, title_image, false);

		//ドア描画
		if (door_counter > 20 && door_counter <= 70) {
			DrawGraph(275, 150, door_image[3], true);
		}
		else if (door_counter > 70 && door_counter <= 120) {
			DrawGraph(275, 150, door_image[6], true);
		}
		else if (door_counter > 120 ) {
			DrawGraph(275, 150, door_image[9], true);
		}

		else DrawGraph(275, 150, door_image[0], true);

	}

}

//	タイトル文字描画用
void Title::RenderTitleChara() {

	//タイトル表記
	if (true_title_move == true)
	{
		//跳ねる（1回）
		if (scene == TITLE && player.GetY() == 200)
		{
			player.SetV(10.0f);
			true_title_move = false;
		}
	}
	//タイトル画面描画
	if (scene == TITLE && true_title_move == false && counter > 200)
	{
		for (int i = 0, a = 1; i < 5; i++, a++) {
			DrawRotaGraph(chara_x + 70 * a, chara_y, chara_size, chara_r[i], title_chara_image[i], true, false);
		}
	}
	if (scene == TITLE && true_title_move == false && counter > 550)
	{
		DrawGraph(200, chara2_y, subtitle_chara_image, false);
	}

	if (scene == TITLE && true_title_move == false && counter > 1000) {
		DrawString(500, 200, "PUSH KEY　「S」", GetColor(0, 0, 0));
	}

}
//タイトル文字動かす用
void Title::MoveTitleChara() {
	chara_x -= 2;
	if (scene == TITLE && true_title_move == false && counter > 550 && chara2_y < 120)
	{
		chara2_y++;
	}
	if (scene == TITLE && true_title_move == false && counter > 950) {
		//タイトル文字を回転させる
		float a = 0.01f;
		chara_counter++;
		if (chara_counter > 120) {
			for (int i = 0; i < 5; ++i) {
				chara_r[i] += 0.03f + a;
				a += 0.01f;
			}
		}
		chara_x = 120;
		chara_y = 50;

	}
}

//タイトル画面終了
void Title::EndTitle() {
	if (IsKeyOn(KEY_INPUT_S)) {
		if (scene == TITLE) {
			sound.EndTitle();
			scene = INPUT_NAME;
		}
	}
}
//初期画面終了
void Title::EndTitle2() {

	if (player.GetSize() < 0.7f) {
		door_counter = 0;
		door_check = false;
		player.SetSize(1.0f);	
		StopMusic();
	
		scene = CHENGE2;

	}


}
//ドアの開く音
void Title::PlayDoorSound() {

	//ジョイパッド
	if (GetJoypadInputState(DX_INPUT_PAD1) & (PAD_INPUT_UP)) {
		if ((player._before_BIT & PAD_INPUT_UP) == false) {
			//タイトル画面以外
			if (scene == SELECT)
			{
				//扉を開ける音
				if (player.GetX() > 302 && player.GetX() < 344) {
					if (door_check == false) {
						sound.PlayDoor();
						door_check = true;
					}
				}
			}
		}
	}


	if (GetJoypadNum() != 0)return;


	if (IsKeyOn(KEY_INPUT_UP))
	{
		//タイトル画面以外
		if (scene == SELECT)
		{
			//扉を開ける音
			if (player.GetX() > 302 && player.GetX() < 344) {
				if (door_check == false) {

					sound.PlayDoor();
					door_check = true;
				}
			}
		}
	}
}

//ゲームスタートのカウントダウン
void Title::StartCountDown() {
	if (start_counter > 0 && start_counter < 60) {
		DrawGraph(400, 0, count_image[4], true);
	}
	else if (start_counter >= 60 && start_counter < 120) {
		DrawGraph(300, 0, count_image[3], true);
	}
	else if (start_counter >= 120 && start_counter < 180) {
		DrawGraph(200
			, 0, count_image[2], true);
	}
	else if (start_counter >= 180 && start_counter < 240) {
		DrawGraph(100, 0, count_image[1], true);
	}
	else if (start_counter >= 240 && start_counter < 300) {
		DrawGraph(0, 0, count_image[0], true);
	}
	else if (start_counter >= 300 && start_counter < 310) {
		DrawGraph(0, 0, go, true);
	}


}

void TitleInit() {
	title.Load();
}
void TitleExit() {

}
void TitleUpdate() {

	title.AddTitleCount();
	title.AddDoorCount();
	title.MoveTitleChara();
	title.PlayDoorSound();
	title.EndTitle();
	title.EndTitle2();
}
void TitleRender() {
	if (scene == TITLE||scene==SELECT) {
		title.RenderTitle2();
		title.RenderTitle();
		title.RenderTitleChara();
	}
	}
