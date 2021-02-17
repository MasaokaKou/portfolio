
#pragma once
#include"Base.h"

//------------------------------------
//! 選択枝を出すためのクラス
//------------------------------------

// 選択枝の箱
class SelectBox
{
public:
	SelectBox();
	~SelectBox();

	////! 四つの箱の位置を決める
	//void setPos(s16 x, s16 y);
	
	
	//! ランダムで一設定するときの枠を定める
	bool  frameChecker(Vector2 pos_);

	
	//! 場所をランダムで設定 
	void setPos();




	//! 当たり判定 
	s16 hit();

	//! 描画
	void Draw();

	// BOXの位置取得用
	Vector2 getPos() { return _pos; }

	// BOXのサイズ取得用
	s16 getSize() { return _size; }

	// 色を持たせる
	void setCol(s16 color);
	// 色を返す
	s16 getColor() { return _color; }

	//! 図形のセット
	void setFigure(s16 figure_) { _figure = figure_; }
	void setColor(u64 color_) { _setColor = color_; }

	//! 図形のゲッター
	s16 getFigureNum() { return _figure; }


private:
	Vector2  _pos;
	s16      _size; //! 図形のサイズ
	s16      _color;//! 配色番号

	s16      _figure; //! 図形設定用変数
	u64      _setColor; //! 色情報

	//! 選択用フレームの有無
	bool    _isFrame;
};


class Selecter
	:Base
	
{
public:
	Selecter();
	~Selecter();

	bool initialize();									//! 初期化
	void update(s16 &que_color, s16 &que_figure);		//! 更新
	void draw();										//! 描画
	void exit();										//! 破棄

	void updateSelBox();	//! selBox描画
	void drawSelBox();	    //! selBox描画


	//! 選択肢を出す
	void setSel();
	//! 同じ数字が出ないように処理する	
	void shuffle(s16 ary[], s16 size);
	
	//! 出た乱数によって問題の配色を決める
	void setCol();

	//! 図形をランダムで決める
	void setFig();

	//! 一つだけ問題と一致させる
	void matchToQue(s16 &que_color, s16 &que_figure);

	//! 当たり判定用
	bool hit();

	//! 図形同士が重ならないようにする
//! 図形の上下左右にサイズ分の空きを作る
	bool notOverlap(Vector2 &p0, Vector2 &p1);

	//! 同じ色と同じ形が答え以外にあればSetしなおす
	void check(s16 &que_color, s16 &que_figure);

	s16 getColorNum() { return _colorNum; }
	s16 getFigureNum() { return _figureNum; }
	
private:
	//! 配色番号を返す
	s16 _colorNum;
	//! 図形番号を返す
	s16 _figureNum;

	SELECT sel_color[SELECT_MAX];


	//! 選択枝の箱のインスタンス
	SelectBox * _selBox[SELECT_MAX];

	
};


