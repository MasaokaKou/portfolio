#pragma once
#include"Typedef.h"
//------------------------------------
//! Effect関連全般の管理
//------------------------------------


//! ゲーム開始のエフェクト
//! ゲーム終了のエフェクト



//! 正解と不正解のエフェクト

class EffectBase
{
public:
	EffectBase() {};
	virtual~EffectBase() {};

protected:
	f32 _x, _y; //! 座標
	s16 _size; //! サイズ
};


class Correct
	:public EffectBase
{
public:
	Correct();
	~Correct();

	void draw(); //! 描画

private:
	s16 _size; //! サイズ
	

};

class unCorrect
	:public EffectBase
{
public:
	unCorrect();
	~unCorrect();

	void draw(); //! 描画
private:

};

class EffectManager
{
public:
	EffectManager();
	~EffectManager();

	//! 正解かどうかをとってくる
	void isCorrect(bool isCorect_) { _isCorrect = isCorect_; }
	void isStart() { _isStart = true; }

	//! エフェクトの時間調整用
	s16 Count(s16 timer_);

	void update(); //! 更新
	void draw();   //! 描画

	void reset();  //! ゲームごとの初期化


private:
	//! 正解エフェクトのインスタンス
	Correct *corIns;
	//! 不正解エフェクトのインスタンス
	unCorrect *unCorIns;
	//! 正解かどうか
	bool _isCorrect;
	//! エフェクトの時間調整用
	s16 _timer;

	//! エフェクトが始まっているかどうか
	bool _isStart;

};

