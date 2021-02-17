#pragma once
#include"Base.h"

//------------------------------------
//!問題を出すためのクラス
//------------------------------------

class Question
	:public Base
{
public:
	Question();
	~Question();

	bool initialize();  //! 初期化
	void update();		//! 更新
	void draw();		//! 描画
	void exit();		//! 破棄

	// 問題をだす
	void setQue();
	//// 出た乱数によって問題の配色を決める
	void setCol();

	// 問題になっている色を返す（答え合わせ用）
	SELECT &getSelectColor() { return que_color; }
	// 問題になっている色番号を返す（答え合わせ用）
	s16 &getColorNum() { return _color[0]; }
	s16 &getFigureNum() { return _fig[0]; }
private:

	SELECT que_color;




};

