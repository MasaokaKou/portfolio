#include"MAIN.H"
#include"GAME.H"
#include"Score.h""
#include"map.h"
#include"player.h"
Score::Score() {
	_score = 0;
	_counter = 0;
	_time = 0;

	_re_score = 0;
	_re_time=0;
}

Score::~Score() {


}

//常にカウント増加
void Score::AddCount() {
	if (scene == GAME) {
		_counter++;
	}
}

//一秒毎、マップスピードの速さによるスコア増加
void Score::Add() {
	if (_counter % 60 == 0) {
		if (map.GetSpeed() == 1.6f) {
			_score += 20;
		}
		else if (map.GetSpeed() == 2.0f) {
			_score += 40;
		}
		else if (map.GetSpeed() == 2.5f) {
			_score += 60;
		}
	}
}

//時間加算
void Score::AddTime() {
	if (scene == GAME) {
		if (_counter != 0&&_counter % 60 == 0) {
			_time++;
		}
	}
}



//エネミーを倒したとき
void Score::AddEnemyScore() {
	if (player.GetConbo() ==1) {
		_score += 100;
	}
	else if (player.GetConbo() ==2)
	{
		_score += 150;
	}
	else if (player.GetConbo() == 3)
	{
		_score += 200;
	}
	else if (player.GetConbo() == 4)
	{
		_score += 250;
	}
	else if (player.GetConbo() >= 5) {
		_score += 300;
	}

}

//コインを取った時
void Score::AddCoinScore() {
	
	_score +=500;

}

//リセット時
void Score::Reset() {
	_score = 0;
	_time = 0;
}

//スコア描画
void Score::Show() {
	if (scene == GAME || scene == RESULT || scene == GAMEOVER) {
		char text[256];
		sprintf_s(text, "%d", _score);
		char text2[256];
		sprintf_s(text2, "%d", _time);
		DrawString(350, 275, "score", GetColor(255, 255, 255));
		DrawString(400, 275, text, GetColor(255, 255, 255));
		DrawString(350, 290, "time", GetColor(255, 255, 255));
		DrawString(400, 290, text2, GetColor(255, 255, 255));

	}
}

//スコアと時間の受け渡し
void Score::GiveData1() {
	if (_re_score <= _score) {
		_re_score+=50;
	}

	if (_re_score > _score) {
		_re_score = _score;
	}

	if (_re_time < _time&&_re_score == _score) {
		_re_time++;
	}
}

//リザルト画面で描画
void Score::ShowResult(){
	char text[256];
	sprintf_s(text, "%d", _re_score);
	char text2[256];
	sprintf_s(text2, "%d", _re_time);
	
	if (scene == RESULT) {
		DrawString(290, 130, "score", GetColor(255, 255, 255));
		DrawString(290, 150, text, GetColor(255, 255, 255));
		DrawString(290, 170, "time", GetColor(255, 255, 255));
		DrawString(290, 190, text2, GetColor(255, 255, 255));

	}
}

//ゲーム終了時のデータリセット
void Score::ResetData() {
	if (scene == GAME) {
		_re_score = 0;
		_re_time = 0;
	}
}