#include"Base.h"
#include"Main.h"

//-----------------------
//!コンストラクタ
//-----------------------
Base::Base()
{
}

//-----------------------
//!デストラクタ
//-----------------------
Base::~Base()
{
}

//------------------------------------
//! 出た乱数によって問題の配色を決める
//------------------------------------
 void Base::setCol(SELECT &color , s16 obj, s16 &colorNum)
{
	switch (obj)
	{
	case 0:
		color = SELECT::BLUE;
		colorNum = 0; 
		break;

	case 1:
		color = SELECT::PURPLE;
		colorNum = 1;
		break;

	case 2:
		color = SELECT::RED;
		colorNum = 2;
		break;

	case 3:
		color = SELECT::PINK;
		colorNum = 3;
		break;

	case 4:
		color = SELECT::ORANGE;
		colorNum = 4;
		break;

	case 5:
		color = SELECT::YELLOW;
		colorNum = 5;
		break;

	case 6:
		color = SELECT::YELLOWGREEN;
		colorNum = 6;
		break;

	case 7:
		color = SELECT::GREEN;
		colorNum = 7;
		break;

	case 8:
		color = SELECT::LIGHTBLUE;
		colorNum = 8;
		break;

	case 9:
		color = SELECT::LIGHTOLANGE;
		colorNum = 9;
		break;

	case 10:
		color = SELECT::WHITE;
		colorNum = 10;
		break;

	case 11:
		color = SELECT::BROWN;
		colorNum = 11;
		break;

	default:
		break;
	}
}

 //! 出た乱数によって問題の配色する
 void Base::CheckCol(SELECT &color , u64 &setColor_)
 {
	 switch (color)
	 {
	 case SELECT::BLUE:
		 setColor_ = GetColor(0, 0, 255);
		 break;
	 case SELECT::PURPLE:
		 setColor_ = GetColor(155, 114, 176);
		 break;
	 case SELECT::RED:
		 setColor_ = GetColor(255, 0, 0);
		 break;
	 case SELECT::PINK:
		 setColor_ = GetColor(234, 145, 152);
		 break;
	 case SELECT::ORANGE:
		 setColor_ = GetColor(255, 164, 0);
		 break;
	 case SELECT::YELLOW:
		 setColor_ = GetColor(255, 212, 0);
		 break;
	 case SELECT::YELLOWGREEN:
		 setColor_ = GetColor(185, 196, 47);
		 break;
	 case SELECT::GREEN:
		 setColor_ = GetColor(0, 128, 0);
		 break;
	 case SELECT::LIGHTBLUE:
		 setColor_ = GetColor(68,85, 90);
		 break;
	 case SELECT::LIGHTOLANGE:
		 setColor_ = GetColor(254, 216, 177);
		 break;
	 case SELECT::WHITE:
		 setColor_ = GetColor(255, 255, 255);
		 break;
	 case SELECT::BROWN:
		 setColor_ = GetColor(150, 75, 0);
		 break;
	 default:
		 break;
	 }

 }

