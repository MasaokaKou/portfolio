#pragma once
#include"Main.h"
//---------------------------------------------
// !quiz全体の管理
//---------------------------------------------

class TaskManager
{
public:
	TaskManager();
	~TaskManager();

	bool initialize();  //! 初期化
	void update();		//! 更新
	void draw();		//! 描画
	void exit();		//! 破棄

	void reset(); //! ゲームごとの初期化

	//! 選択した色を返す（答え合わせ用）
	s16 hitChecker();

	//! 正解したら次へ
	void nextQue();

	//! TimeLimitnにスコアを渡す
	void giveScore();
	s16 getScore();
	void setGameState(bool flag) { _setGame = flag; }

	bool getisEnd();

	// debug-----------------------------------------
	void DebugPlay();
	//-----------------------------------------------
private:
	// 問題が始まったらtrue、終わったらfalse 
	bool _setGame;

	// questionのインスタンス
	class Question *_queIns;
	// selecterのインスタンス
	class Selecter *_selIns;
	// effectMngのインスタンス
	class EffectManager * _eMngIns;
	// Timeのインスタンス
	class TimeLimit * _tLimIns;
	// Scoreのインスタンス
	class Score * _score;

	


};

