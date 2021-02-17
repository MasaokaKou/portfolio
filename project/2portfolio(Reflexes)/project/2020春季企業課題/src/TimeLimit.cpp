#include"TimeLimit.h"
#include"Main.h"


//-----------------------
//!コンストラクタ
//-----------------------
TimeLimit::TimeLimit()
{
	//! 一門ごとの制限時間
	_limit = 300;
	//! 全体の経過時間
	_time = 0;
	_timeCounter = 0;

	//! 時間切れかどうか
    _end = false;

	//! 制限時間開始
	_startLimiter = false;

	color = GetColor(255, 255, 255);

	_limitMax[0] = 300;
	_limitMax[1] = 180;
	_limitMax[2] = 120;
	_limitMax[3] = 60;
	//! 割合の計算
	_par[0] = 120.0f; 
	
	//! なんウェーブ目か
	_wave = 0;
}

//-----------------------
//!デストラクタ
//-----------------------
TimeLimit::~TimeLimit()
{
}


//! ゲームごとの初期化
void TimeLimit::reset()
{//! 一門ごとの制限時間
	_limit = 300;
	//! 全体の経過時間
	_time = 0;
	_timeCounter = 0;

	//! 時間切れかどうか
	_end = false;

	//! 制限時間開始
	_startLimiter = true;

	//! なんウェーブ目か
	_wave = 0;

	color = GetColor(255, 255, 255);

}

//! 秒数変換
void TimeLimit::time()
{

	_timeCounter++;
	if (_timeCounter % 60 == 0)
	{
		_time++;
	}
}


//! 制限時間
void TimeLimit::limit()
{
	if (_limit <= 0) {
		_limit = 0;
		_end = true;

	}
}

//! ウェーブ切り替え	
void TimeLimit::setWave()
{
	
	if (_score == 400) {
		_wave = 3;
	}else	
	if (_score == 300) {
		_wave = 2;
	}else
	if (_score == 150) {
		_wave = 1;
	}
	
}

//! 初期化
bool TimeLimit::initialize()
{
	_end = false;

	//! 一門ごとの制限時間
	setWave();
	_limit = _limitMax[0 +_wave];
	color = GetColor(255, 255, 255);
	_startLimiter = true;
	return false;
}

//! 更新
void TimeLimit::update() 
{
	time();
	limit();
	

	if (_startLimiter) {
		_limit--;
	}


if (_limit <= _limitMax[0 + _wave] * 0.4)
		color = GetColor(255, 0, 0);


}

//! 描画
void TimeLimit::draw()
{
	//! ウインドウサイズ

	s16 size = 60;
	

	//checgeText(_time, 640 / 2 - 10 , 0, 255, 255, 255);
	//checgeText(_limit, 640 / 2 , 0, 255, 255, 255);
	//checgeText(_wave, 640 / 2, 20, 255, 255, 255);

	if (_wave == 1) {
		int a = 0;
	}
	
	DrawBox(WINDOW_W / 2 + size -(_limit  / (_limitMax[0 + _wave] / (_par[0]))), 20, WINDOW_W / 2 + size, 40, color, true);
	DrawBox(WINDOW_W / 2 - size, 20, WINDOW_W / 2 + size, 40,GetColor(255, 255, 255), false);



}
