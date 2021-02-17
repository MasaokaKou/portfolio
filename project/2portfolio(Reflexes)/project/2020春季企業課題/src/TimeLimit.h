#pragma once
#include"Typedef.h"
//-----------------------------
//! 制限時間
//! 一門ごとの制限時間
//! 全体の経過時間
//----------------------------


class TimeLimit
{
public:
	TimeLimit();
	~TimeLimit();

	bool initialize();  //! 初期化
	void update();		//! 更新
	void draw();		//! 描画
	void exit();		//! 破棄

	void reset(); //! ゲームごとの初期化


	//! 秒数変換
	void time();

	//! 制限時間
	void limit();

	//! ウェーブ切り替え	
	void setWave();
	//!スコアを取ってくる
	void setScore(s16 score_) { _score = score_; }

	//! ゲームオーバーかどうか
	bool isEnd() { return _end; }
	//! 一回ミスしたらゲームオーバー
	void gameEnd() { _end = true; }

private:

	//! 一門ごとの制限時間
	s16        _limitMax[4];
	s16        _limit;
	
	//! 全体の経過時間
	s16 _time;
	s16 _timeCounter;



	//! 時間切れかどうか
	//! trueになったらゲームオーバー
	bool _end;
	//! 制限時間開始
	bool _startLimiter;
	//! 残り三割切ったら赤にする
	u64 color;

	//!Scoreからとってきたものをいれる
	s16 _score;
	//! なんウェーブ目か
	s16 _wave;
	f32 _par[3]; //! 割合の計算
};




