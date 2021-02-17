
#pragma once
#include"Typedef.h"
//! シーンの管理全般
#include"Vector2.h"

//! シーン
enum class Scene
{
	TITLE,    //! タイトル
	PLAY,	  //! ゲーム
	RESULT,   //! リザルト
	RANKING,  //! ランキング
	MANUAL    //! マニュアル

};


class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	//! タイトルシーンをセット
	void SetTitle() { *_scene = Scene::TITLE; }

	//! ゲームのシーンをセット
	void SetGame() { *_scene = Scene::PLAY; }

	//! リザルトのシーンをセット
	void SetResult() { *_scene = Scene::RESULT; }

	//! 指定した数秒間待機
	bool wait();

	//! ゲームスタート
	void gsmeStart();

	void update(); //! 更新
	void draw();   //! 描画

	

	void reset(); //! ゲームごとの初期化


private:
	//! タスクマネージャー
	class TaskManager * tMng;

	Scene * _scene;       //! シーンの列挙

	class Title * _title;  //! タイトルのインスタンス
	class Play * _play;    //! プレイのインスタンス
	class Result * _result;//! リザルトのインスタンス
	class Ranking * _rank; //! ランキングのインスタンス
	class Manual *_manual; //! マニュアルのインスタンス

	class Thread * _thread; //! 糸のインスタンス

	s16 _time_F; //! ゲームが始まるまでをフレーム表記
	s16 _time_S; //! ゲームが始まるまでを秒数表記
	s16 _playTime; //! プレイ時間

	bool _isStart; //! ゲームスタート

	s64 _fontHandle;



};



class Title
{
public:
	Title();
	~Title();

	//! アクションがあれば次のシーンへ
	void nextScene(Scene &scene);

	//! 選択肢の図形の当たり判定
	s16 cHit(s16 x, s16 y); //! 円
	s16 tHit(s16 x,s16 y); //! 三角形
	s16 bHit(s16 x, s16 y); //! 四角

	bool initialize(); //! 初期化
	void update();	   //! 更新
	void draw();       //! 描画

	Vector2 sub_vector(const Vector2& a, const Vector2& b);
	int hittest_point_polygon_2d(Vector2 A, Vector2 B, Vector2 C, Vector2 P);
	
	void isUp(bool isUp_);

	//! 透過度変更
	void mvoeAlpha();

protected:

	s16 _cPos_X, _cPos_Y; //! 円の位置
	s16 _tPos_X, _tPos_Y; //! 三角の位置
	s16 _bPos_X, _bPos_Y; //! 四角の位置

	s16 _size;

	bool _isUp; //! 引き上げているかどうか

	//! どの図形にあたっているか（円、三角、四角）
	s16 _hitNum;
	
	//! 図形の中の文字
	s16 _alpha[3]; //! 透過度
	bool _checkAlpha; //! 透過度増減ON/OFF
	bool _whichOne[3]; //! どれがONか

	//! 図形の透過度
	s16 _figureAlpha;
	

	//! しーんきりかえよう
	std::unique_ptr< class moveScene > _moveScene;

};

//! 引き上げるモーションようの糸
class Thread:
	public Title
{
public:
	Thread();
	~Thread();

	bool initialize(); //! 初期化
	bool update();     //! 更新
	void draw();       //! 描画

	void reset();  //! ゲームごとのリセット

	//! どこをっクリックしたかで初期位置設定
	void set();
	//! 図形にあたるまで下に降りる処理
	bool down();
	//! 図形に当たったら引き上げる
	void up();

	//! 引き上げているかどうか
	bool getIsUp() { return _isUp; }
	//! クッリックしたら落とす
	void setDown();

	//! 当たってるかどうか
	bool isHit(s16 x, s16 y);

	
private:
	Vector2 _pos;  //! 位置
	f32     _size; //! サイズ

	bool _isUp; //! 引き上げているかどうか
	bool _isDown; //! 落ちてるかどうか

	
	
};


class Play
{
public:
	Play();
	~Play();

	//! アクションがあれば次のシーンへ
	void nextScene(Scene &scene, bool isEnd_);

private:

};

//! アニメーション演出用のミニ図形
class figure
{
public:
	figure();
	~figure();

	void update();
	void draw();

	//! 動き回る範囲の指定
	bool c_LimitX();
	bool c_LimitY();
	bool t_LimitX();
	bool t_LimitY();
	bool b_LimitX();
	bool b_LimitY();



	//! 跳ね返る
	void reflect();

	void move();

private:
	//! 三つの図形
	Vector2 _pos[3];
	s16 _size;

	s16 _speedX[3];
	s16 _speedY[3];

	s16 _flag;
};


class Result
{
public:
	Result();
	~Result();

	//! アクションがあれば次のシーンへ
	void nextScene(Scene &scene);
	void update(); //! 更新
	void draw();   //! 描画

	void reset(); //!　リザルトのリセット

	//! Scoreから持ってくる
	void setScore(s16 score_);

	void blink();
private:

	s16 _score; //! 描画するよう
	bool _getScore; //! 一度だけスコアを受けとる
	bool _getRanking;//! 一度だけランキングを回す

	//!　ランキングのインスタンス
	class Ranking * _rankIns;
	class figure * _figure;

	s16 _blinkTimer;
	s16 _alpha;

	s64 _fontHandle;
	//! しーんきりかえよう
	std::unique_ptr< class moveScene > _moveScene;

};

class Manual
{
public:
	Manual();
	~Manual();

	void update();
	void draw();
	void reset();

	bool timer() {
		if (_timer == 1)return true;

		return false;
	}

private:

	s16 _timer;
};

