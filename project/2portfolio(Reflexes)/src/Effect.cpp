#include"Effect.h"
#include"Main.h"

//------------------------------------
//! Effect関連全般の管理
//------------------------------------
EffectManager::EffectManager()
{

	//! 正解かどうか
	_isCorrect = false;
	
	//! エフェクトの時間調整用
	_timer = 0;

	//! 正解エフェクトのインスタンス
	corIns = new Correct;

	//! 不正解エフェクトのインスタンス
	unCorIns = new unCorrect;

	//! エフェクトが始まっているかどうか
	_isStart = false;


}

EffectManager::~EffectManager()
{
}

//! ゲームごとの初期化
void EffectManager::reset()
{
	//! 正解かどうか
	_isCorrect = false;

	//! エフェクトの時間調整用
	_timer = 0;

	//! 正解エフェクトのインスタンス
	corIns = new Correct;

	//! 不正解エフェクトのインスタンス
	unCorIns = new unCorrect;

	//! エフェクトが始まっているかどうか
	_isStart = false;
}


void EffectManager::update()
{
	
	Count(15);
	
}


void EffectManager::draw()
{
	if (!_isStart)return;

	if (_isCorrect) {
		corIns->draw();
	}

	if (!_isCorrect) {
		unCorIns->draw();
	}


}

//------------------------------------
//! エフェクトの時間調整用
//------------------------------------
s16 EffectManager::Count(s16 timer_)
{

	if(!_isStart)
	_timer = timer_;


	if(_timer <=0)
	{
		_isStart = false;
		_timer = 0;
		return true;
	}
	else
	{
		_timer--;
	}


	return false;
}

//------------------------------------
//! 正解と不正解のエフェクト
//------------------------------------
Correct::Correct()
{
	_x = 640.0f / 2.0f;
	_y = 480.0f / 2.0f;
	_size = 150;
}

Correct::~Correct()
{
}


//------------------------------------
//! 描画
//------------------------------------
void Correct::draw()
{
	for(f32 i = 0;i < 15.0f ; i+=0.5f)
	DrawCircle(_x, _y, _size - i, GetColor(255, 0, 0), false);
	
}

unCorrect::unCorrect()
{
	_x = 640.0f / 2.0f - 100.0f;
	_y = 480.0f / 2.0f - 100.0f;
	_size = 250;
}

unCorrect::~unCorrect()
{
}

//------------------------------------
//! 描画
//------------------------------------

void unCorrect::draw()
{
	s16 x1 = _x;
	s16 y1 = _y;
	s16 x2 = _x + _size;
	s16 y2 = _y + _size;


	DrawLine(x1, y1, x2, y2, GetColor(255, 0, 0), 10);

	DrawLine(x2, y1, x1, y2, GetColor(255, 0, 0), 10);

}
