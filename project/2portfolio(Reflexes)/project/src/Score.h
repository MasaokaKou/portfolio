#pragma once
#include"Typedef.h"

//-------------------------------
//! スコア
//-------------------------------
class Score
{
public:
	Score();
	~Score();
	void update(); //! 更新
	void draw();   //! 描画

	void reset();  //! ゲームごとの初期化

	//! 加点
	void add();
	
	//! 制限時間への受け渡し
	s16 getScore() { return _score; }

	//! タスクマネージャーで操作
	void isUp() { _isUp = true; }

private:
	s16 _score; //! スコア
	bool _isUp; //! 加点されてるかどうか
};

