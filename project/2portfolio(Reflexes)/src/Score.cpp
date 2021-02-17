#include"Score.h"
#include"Main.h"

//-----------------------
//!コンストラクタ
//-----------------------
Score::Score()
{
	_score = 0;
	_isUp = false;
}

//-----------------------
//!デストラクタ
//-----------------------
Score::~Score()
{

}

//-----------------------
//! ゲームごとの初期化
//-----------------------
void Score::reset()
{
	_score = 0;
	_isUp = false;

}

void Score::update()
{
	add();
}

void Score::draw()
{
	DrawString(30, 150, "SCORE:", GetColor(255, 255, 255),true);
	checgeText(_score, 90, 150, 255, 255, 255);
}

//! 加点
void Score::add()
{
	if(_isUp){
		_score += 10;
		_isUp = false;
	}

}

