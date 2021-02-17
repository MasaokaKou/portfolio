#pragma once
#include"Typedef.h"
#include"Vector2.h"
const s16 SELECT_MAX = 6;


//-------------------------
//!配色
//-------------------------

enum class SELECT
{


	BLUE,
	PURPLE,
	RED,
	PINK,
	ORANGE,
	YELLOW,
	YELLOWGREEN,
	GREEN,
	LIGHTBLUE,
	LIGHTOLANGE,
	WHITE,
	BROWN

};





//-------------------------
//!基底クラス
//-------------------------

class Base
{
public:
	Base();
	virtual~Base();

	//! 出た乱数によって問題の配色を決める
	virtual void setCol(SELECT &color, s16 obj, s16 &colorNum);
	//! 出た乱数によって問題の配色する
	virtual void CheckCol(SELECT &color, u64 &setColor_);

	bool initialize();  //! 初期化
	void update();		//! 更新
	void draw();		//! 描画
	void exit();		//! 破棄



protected:


	s16 _que;               //! 問題
	s16 _sel[SELECT_MAX];   //! 選択枝
	s16 _fig[SELECT_MAX];   //! 選択枝の図形
	s16 _ans;				//! 答え

	Vector2 _pos;				//! 問題の位置
	s16     _size;              //! 問題の大きさ
	s16     _color[SELECT_MAX]; //! 問題の色
	
	u64		_setColor[SELECT_MAX];			//! 色のあてはめ


								// 配色用列挙体
	SELECT sel_COLOR[SELECT_MAX];
	



};

