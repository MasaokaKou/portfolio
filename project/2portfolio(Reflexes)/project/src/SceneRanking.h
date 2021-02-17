#pragma once
#include"Typedef.h"
#include<array>




class Ranking
{
public:
	Ranking();
	~Ranking();

	void initialize();  //! 初期化
	void update();		//! 更新
	void draw();		//! 描画
	void exit();		//! 破棄
	void Save();        

	void drawSceneRanking();		//! 描画
	


	void setScore(s16 score_) { _score = score_; }


	void blink();
private:

	//txtに書き込むスコアを入れる用の配列(上位3位まで)
	std::array<s16, 3> _ranking;

	//! 初期化
	bool _initialized;

	//! 現在スコア
	s16 _score;
	s16 _scoreAlpha;

	//! 文字拡大用
	s64 _fontHandle;

	//! ランキング描画画面での点滅用変数
	s16 _blinkTimer;
	s16 _alpha;

	s16 _char_y;
	
};

