#include"Main.h"
#include"Question.h"

//------------------------------------
//!コンストラクタ
//------------------------------------
Question::Question()
{
	_pos.set(55, 55);
	_size = 130;
	_color[0] = 0;

	que_color = SELECT::BLUE;
	Question::_setColor[0] = GetColor(0, 0, 0);

}

//------------------------------------
//!デストラクタ
//------------------------------------
Question::~Question()
{
}

//------------------------------------
//! 問題を出す
//------------------------------------
void Question::setQue()
{
	_que = rand() % 12;
	_fig[0] = rand() % 3;
}

//------------------------------------
//! 出た乱数によって問題の配色を決める
//------------------------------------
void Question::setCol()
{
	Base::setCol(que_color, _que, Question::_color[0]);
	Base::CheckCol(que_color, Question::_setColor[0]);
	

}


//------------------------------------
//! 初期化
//------------------------------------
bool Question::initialize()
{
	_que = 0;
	return true;;

}

//------------------------------------
//! 更新
//------------------------------------
void Question::update()
{
	setQue(); //問題を出す
	setCol(); //出た乱数によって問題の配色を決める
}

//------------------------------------
//! 描画
//------------------------------------
void Question::draw()
{
	
	// 描画モードをアルファブレンドにして透明度を５０％にする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawBox(0, 0, 120, 120, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	for(s16 i =0 ; i <= 5;i++ )
	DrawBox(5 + i, 5 + i, 120 - i, 120 - i, GetColor(0,0,0), false);
	
	_size = 50;

	//! 図形設定用
	switch (_fig[0])
	{
	case 0:  //! 円
		_pos.set(62, 62);
		DrawCircle(_pos.x, _pos.y, _size, Question::_setColor[0]);
		break;

	case 1:  //! 三角
		_pos.set(62, 42);
		DrawTriangle(_pos.x, _pos.y  -_size / 2, _pos.x - _size, _pos.y + _size, _pos.x + _size, _pos.y + _size, Question::_setColor[0], true);
		break;

	case 2:  //! 四角
		_size = 80;
		_pos.set(22, 22);
		DrawBox(_pos.x, _pos.y, _pos.x + _size, _pos.y + _size, Question::_setColor[0], true);
		break;

	default:
		break;
	}

	
#ifdef _DEBUG

	// 微調整用
	s16 text_x = _pos.x + _size / 2;
	s16 text_y = _pos.y + _size / 2;
	checgeText(_color[0], text_x, text_y, 255, 255, 255);
#endif // _DEBUG
}

//------------------------------------
//! 破棄
//------------------------------------
void Question::exit()
{
}


