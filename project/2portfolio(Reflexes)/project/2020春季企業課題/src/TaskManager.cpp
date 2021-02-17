#include"Game.h"

#include"TaskManager.h"
#include"Question.h"
#include"Selecter.h"
#include"Effect.h"
#include"TimeLimit.h"
#include"Score.h"



TaskManager::TaskManager()
{
	// 問題が始まったらtrue、終わったらfalse 
	// 始まる前はfalse
	_setGame = false;

	// questionのインスタンス
	_queIns = new Question;
	// selecterのインスタンス
	_selIns = new Selecter;

	// effectMngのインスタンス
	_eMngIns = new EffectManager;

	// Timeのインスタンス
	_tLimIns = new TimeLimit;

	// Scoreのインスタンス
	 _score = new Score;

}

TaskManager::~TaskManager()
{
}

void TaskManager::reset()
{
	_tLimIns->reset();
	_eMngIns->reset();
	_score->reset();

}


// debug-----------------------------------------
//!　特定のボタンを押したら開始
//-----------------------------------------------
void TaskManager::DebugPlay() {
	if (PushHitKey(KEY_INPUT_0)) {
		setGameState(true);
	}
}

//------------------------------------
//! 正解したら次へ
//------------------------------------
void TaskManager::nextQue() {
	if (hitChecker()) {
		setGameState(true);
	}
}


//------------------------------------
//! 選択した色を返す（答え合わせ用）
//------------------------------------

s16 TaskManager::hitChecker()
{

	//! 当たり判定用
	if (!_selIns->hit())return false;

	if (PushMouseInput())
	{

		//! 問題用の配色番号
		s16 que_color = _queIns->getColorNum();
		//! 選択した配色番号
		s16 sel_color = _selIns->getColorNum();
		//! 問題用の図形番号
		s16 que_figure = _queIns->getFigureNum();
		//! 選択した配色番号
		s16 sel_figure = _selIns->getFigureNum();


		if (que_color == sel_color && que_figure == sel_figure) {
			_eMngIns->isCorrect(true);
			//! スコアUP
			_score->isUp();
			//! エフェクトスタート
			_eMngIns->isStart();
			return true;
		}
		else if (que_color != sel_color || que_figure != sel_figure)
		{
			_eMngIns->isCorrect(false);
			
			//! エフェクトスタート
			_eMngIns->isStart();
			_tLimIns->gameEnd();

		}
	}

	return false;
}

//! TimeLimitnにスコアを渡す
void TaskManager::giveScore()
{
	_tLimIns->setScore(_score->getScore());
}

//! SceneManagerにスコアを渡す
s16 TaskManager::getScore()
{
	return _score->getScore();
}


//! ゲームオーバーかどうか渡す
bool TaskManager::getisEnd()
{
	return _tLimIns->isEnd(); 
}


//------------------------------------
//! 初期化
//------------------------------------
bool TaskManager::initialize()
{
	// setGameがtrueなら初期化してスタート
	// 毎ゲームごとの初期化


	if (_setGame) {
		_queIns->initialize();
		_selIns->initialize();
		_tLimIns->initialize();
		return true;
	}

	return false;
}

//------------------------------------
//! 更新
//------------------------------------
void TaskManager::update()
{

	DebugPlay();
	nextQue();
	//! エフェクトの更新
	_eMngIns->update();
	//! 制限時間の更新
	_tLimIns->update();
	//! スコアの更新
	_score->update();
	//! スコアをTimeLimitに渡す
	giveScore();


	if (!initialize()) return;

	//! Questionのk更新
	_queIns->update();
	//! Selecterのk更新
	_selIns->update(_queIns->getColorNum() ,_queIns->getFigureNum() );


	setGameState(false);

}

//------------------------------------
//! 描画
//------------------------------------
void TaskManager::draw()
{
	//! Questionの描画
	_queIns->draw();
	//! Selecterの描画
	_selIns->draw();
	//! effectの描画
	_eMngIns->draw();
	//! Timeの描画
	_tLimIns->draw();
	//! scoreの描画
	_score->draw();
}

//------------------------------------
//! 破棄
//------------------------------------
void TaskManager::exit()
{
}

