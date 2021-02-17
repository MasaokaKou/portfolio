#include"SceneManager.h"
#include"TaskManager.h"
#include"Main.h"
#include"SceneRanking.h"


//----------------------------------------------
//! シーンマネージャー
//----------------------------------------------

//------------------------------------
//! コンストラクタ
//------------------------------------
SceneManager::SceneManager()
{

	//! シーンの列挙
	_scene = new Scene;
	*_scene = Scene::TITLE;

	//! タスクマネージャー
	tMng = new TaskManager;

	//! タイトルのインスタンス
	_title = new Title;
	//! プレイのインスタンス
	_play = new Play;
	//! リザルトのインスタンス
	_result = new Result;

	//! ランキングのインスタンス
	_rank = new Ranking;

	//! マニュアルのインスタンス
	_manual = new Manual;


	//! 糸のインスタンス
	_thread = new Thread;

	_time_F = 480;
	_time_S = 4;

	_playTime = 0;

	_isStart = false;


	_fontHandle = CreateFontToHandle(NULL, 90, 3);
}

//------------------------------------
//! デストラクタ
//------------------------------------
SceneManager::~SceneManager()
{
}

//! ゲームごとの初期化
void SceneManager::reset()
{

	_time_F = 600;
	_time_S = 5;
	_title->initialize();
	_thread->reset();
	tMng->reset();
	_rank->exit();

}

//! ゲームスタート
void SceneManager::gsmeStart()
{
	//! ゲームが始まった瞬間だけとってきて
	//! _isStartを一度だけtrueにする
	if (_playTime == 0)
		_isStart = true;

	if (_isStart) {
		tMng->setGameState(true);
		_isStart = false;
	}
}

//------------------------------------
//! 更新
//------------------------------------
void SceneManager::update()
{

	switch (*_scene)
	{
	case Scene::TITLE:
		_result->reset();

		_title->update();
		//! 糸が図形にあたっていればTITLEのフラグを変える
		_title->isUp(_thread->getIsUp());
		_thread->update();

		_title->nextScene(*_scene);
		break;
	case Scene::PLAY:

		if (!wait()) return;
		gsmeStart();
		_play->nextScene(*_scene, tMng->getisEnd());
		tMng->update();

		_playTime++;
		break;
	case Scene::RESULT:
		_result->setScore(tMng->getScore());
		_result->update();

		reset();
		_result->nextScene(*_scene);
		break;

	case Scene::RANKING:
		_rank->initialize();
		if (PushHitKey(KEY_INPUT_0)) {
			reset();
			*_scene = Scene::TITLE;
		}
		break;
	case Scene::MANUAL:
		_manual->update();
		if (!_manual->timer())return;
		gsmeStart();
		tMng->update();

		break;
	default:
		break;
	}

}

//------------------------------------
//! 描画
//------------------------------------
void SceneManager::draw()
{
	switch (*_scene)
	{
	case Scene::TITLE:
		_title->draw();
		_thread->draw();
		break;
	case Scene::PLAY:
		if (!wait())
			chengeText2(_time_S, WINDOW_W / 2 - 25, WINDOW_H / 2 - 25, 0, 0, 0, _fontHandle);

		if (!wait()) return;
		tMng->draw();
		break;
	case Scene::RESULT:
		_result->draw();
		break;

	case Scene::RANKING:
		_rank->drawSceneRanking();
		break;

	case Scene::MANUAL:
		_manual->draw();
		tMng->draw();
		break;
	default:
		break;
	}
}

//! 指定した数秒間待機
bool SceneManager::wait()
{
	if (_time_F <= 120)
		return true;

	if (_time_F % 120 == 0)
		_time_S--;

	_time_F--;
	return false;
}



//----------------------------------------------
//! 糸
//----------------------------------------------

Thread::Thread()
{
	_pos.set(0.0f, 0.0f);//! 位置
	_size = 5.0f;        //! サイズ
	_isUp = false;       //! 引き上げているかどうか
	_isDown = false;	 //! 落ちてるかどうか
}

Thread::~Thread()
{
}

//------------------------------------
//! ゲームごとのリセット
//------------------------------------
void Thread::reset()
{
	_pos.set(0.0f, 0.0f);//! 位置
	_size = 5.0f;        //! サイズ
	_isUp = false;       //! 引き上げているかどうか
	_isDown = false;	 //! 落ちてるかどうか
}

//------------------------------------
//! 初期化
//------------------------------------
bool Thread::initialize()
{
	if (_size <= 0)
	{
		_pos.set(0.0f, -120.0f);//! 位置
		_size = 0.0f;        //! サイズ
		_isUp = false;       //! 引き上げているかどうか
		_isDown = false;	 //! 落ちてるかどうか
		return true;
	}

	return false;
}


//------------------------------------
//! 更新
//------------------------------------
bool Thread::update()
{
	initialize();
	set();
	setDown();
	down();
	up();
	return false;
}
//------------------------------------
//! 描画
//------------------------------------
void Thread::draw()
{

	DrawLine(_pos.x, _pos.y, _pos.x, _pos.y + _size, GetColor(255, 255, 255));
}

//------------------------------------
//! どこをっクリックしたかで初期位置設定
//------------------------------------
void Thread::set()
{
	if (_isUp) return;
	if (_isDown) return;

	if (cHit(GetMouseX(), GetMouseY())) {
		_pos.set(WINDOW_W / 2, -120);
	}
	else if (tHit(GetMouseX(), GetMouseY()))
	{
		_pos.set(WINDOW_W / 5, -120);
	}
	else if (bHit(GetMouseX(), GetMouseY()))
	{
		_pos.set(WINDOW_W / 2 + 130 + 60, -120);
	}
}

//------------------------------------
//! 図形にあたるまで下に降りる処理
//------------------------------------
bool Thread::down()
{

	if (isHit(_pos.x, _pos.y + _size - 10)) {
		_isUp = true;
		_isDown = false;
		return true;
	}

	if (_isUp) return true;

	if (_isDown)
		_size += 2;


	return false;
}

//------------------------------------
//! 図形に当たったら引き上げる
//------------------------------------
void Thread::up()
{
	if (down())
		_size -= 6;
}

//------------------------------------
//! クッリックしたら落とす
//------------------------------------
void Thread::setDown()
{
	if (PushMouseInput()) {
		if (isHit(GetMouseX(), GetMouseY()))
		{
			_isDown = true;
		}

	}
}
//------------------------------------
//! 当たってるかどうか
//------------------------------------
bool Thread::isHit(s16 x, s16 y)
{
	if (cHit(x, y) ||
		tHit(x, y) ||
		bHit(x, y))
	{
		return true;
	}

	return false;
}


//----------------------------------------------
//! タイトル
//----------------------------------------------

//------------------------------------
//! コンストラクタ
//------------------------------------
Title::Title()
{
	//! 円の位置
	_cPos_X = WINDOW_W * 0.5f;
	_cPos_Y = WINDOW_H * 0.75f;
	//! 三角の位置
	_tPos_X = WINDOW_W / 5;
	_tPos_Y = WINDOW_H - 250;
	//! 四角の位置
	_bPos_X = WINDOW_W / 2 + 130;
	_bPos_Y = WINDOW_H / 2 - 50;

	//!図形のサイズ
	_size = 60;

	//! 引き上げているかどうか
	_isUp = false;
	//! どの図形にあたっているか（円、三角、四角）
	_hitNum = 0;

	_figureAlpha = 0;
	//! 透過度
	_checkAlpha = false;
	for (s16 i = 0; i < 3; i++) {
		_alpha[i] = 0;
		_whichOne[i] = false;

	}
}

//------------------------------------
//! デストラクタ
//------------------------------------
Title::~Title()
{
}

//------------------------------------
//! 初期化
//------------------------------------
bool Title::initialize()
{
	//! 円の位置
	_cPos_X = WINDOW_W * 0.5f;
	_cPos_Y = WINDOW_H * 0.75f;
	//! 三角の位置
	_tPos_X = WINDOW_W / 5;
	_tPos_Y = WINDOW_H - 250;
	//! 四角の位置
	_bPos_X = WINDOW_W / 2 + 130;
	_bPos_Y = WINDOW_H / 2 - 50;

	//! 引き上げているかどうか
	_isUp = false;
	//! どの図形にあたっているか（円、三角、四角）
	_hitNum = 0;

	//! 透過度
	_checkAlpha = false;
	for (s16 i = 0; i < 3; i++) {
		_alpha[i] = 0;
		_whichOne[i] = false;

	}

	_figureAlpha = 0;
	return true;
}

//------------------------------------
//! 更新
//------------------------------------
void Title::update()
{
	mvoeAlpha();
	_figureAlpha += 2;



	if (!_isUp) return;
	switch (_hitNum)
	{
	case 0:
		_cPos_Y -= 6;
		break;
	case 1:
		_tPos_Y -= 6;
		break;
	case 2:
		_bPos_Y -= 6;
		break;
	default:
		break;
	}

}


//------------------------------------
//! 描画
//------------------------------------
void Title::draw()
{

	if (_moveScene) {
		_moveScene.get()->draw();

		if (!_moveScene.get()->isDown()) return;

	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _figureAlpha);
	
	//! 円の描画
	DrawCircle(_cPos_X, _cPos_Y, _size, GetColor(255, 255, 255), true);
	if (cHit(GetMouseX(), GetMouseY()))
		DrawCircle(_cPos_X, _cPos_Y, _size, GetColor(0, 255, 0), true);

	//! 三角形の描画
	DrawTriangle(_tPos_X, _tPos_Y - _size * (0.5f), _tPos_X - _size, _tPos_Y + _size, _tPos_X + _size, _tPos_Y + _size, GetColor(255, 255, 255), true);
	if (tHit(GetMouseX(), GetMouseY()))
		DrawTriangle(_tPos_X, _tPos_Y - _size * (0.5f), _tPos_X - _size, _tPos_Y + _size, _tPos_X + _size, _tPos_Y + _size, GetColor(255, 0, 0), true);


	//! 四角形の描画
	DrawBox(_bPos_X, _bPos_Y, _bPos_X + (_size * 2), _bPos_Y + (_size * 2), GetColor(255, 255, 255), true);
	if (bHit(GetMouseX(), GetMouseY()))
		DrawBox(_bPos_X, _bPos_Y, _bPos_X + (_size * 2), _bPos_Y + (_size * 2), GetColor(0, 106, 182), true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	//! 図形の中の文字
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha[0]);
	DrawString(_cPos_X - _size / 2, _cPos_Y - 5, " START", GetColor(0, 0, 0));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha[1]);
	DrawString(_tPos_X - _size / 2 - 5, _tPos_Y + 25, " MANUAL", GetColor(0, 0, 0));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha[2]);
	DrawString(_bPos_X + 17, _bPos_Y + 50, " RANKING", GetColor(0, 0, 0));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);


}

//------------------------------------
//! アクションがあれば次のシーンへ
//------------------------------------
void Title::nextScene(Scene &scene)
{
	if (_cPos_Y + _size <= 0)
	{

		//! しーんきりかえよう
		if (_moveScene == nullptr)
			_moveScene = std::make_unique<moveScene>();

		if (_moveScene) {
			if (_moveScene.get()->update()) {
				_moveScene = nullptr;
				scene = Scene::PLAY;
			}
		}
		//---------------------------------
	}
	if (_bPos_Y + _size <= 0)
	{
		//! しーんきりかえよう
		if (_moveScene == nullptr)
			_moveScene = std::make_unique<moveScene>();

		if (_moveScene) {
			if (_moveScene.get()->update()) {
				_moveScene = nullptr;
				scene = Scene::RANKING;
			}
		}
		//---------------------------------

	}


	if (cHit(GetMouseX(), GetMouseY())) {
		_whichOne[0] = true;
	}
	else if (tHit(GetMouseX(), GetMouseY()))
	{
		_whichOne[1] = true;
	}
	else if (bHit(GetMouseX(), GetMouseY())) {
		_whichOne[2] = true;
	}
	else {
		//! 透過度初期化
		for (s16 i = 0; i < 3; i++) {
			_whichOne[i] = false;

		}
	}


	if (_isUp) return;
	if (!PushMouseInput()) return;

	if (cHit(GetMouseX(), GetMouseY())) {
		_hitNum = 0;
	}
	else if (tHit(GetMouseX(), GetMouseY()))
	{
		_hitNum = 1;
	}
	else if (bHit(GetMouseX(), GetMouseY())) {
		_hitNum = 2;
	}

}


//! 選択肢の図形の当たり判定
s16 Title::cHit(s16 x, s16 y)
{

	Vector2 mouse;
	mouse.set(x, y);

	if (x <= _cPos_X + (_size * 0.8) && x >= _cPos_X - (_size * 0.8) &&
		y >= _cPos_Y - (_size * 0.8) && y <= _cPos_Y + (_size * 0.8))
	{

		return true;
	}


	return false;
}


s16 Title::tHit(s16 x, s16 y)
{

	Vector2 mouse;
	mouse.set(x, y);
	//! 三角用
	Vector2 tpos1;
	Vector2 tpos2;
	Vector2 tpos3;
	tpos1.set(_tPos_X, _tPos_Y - _size / 2);
	tpos2.set(_tPos_X - (_size), _tPos_Y + (_size));
	tpos3.set(_tPos_X + (_size), _tPos_Y + (_size));

	if (hittest_point_polygon_2d(tpos1, tpos2, tpos3, mouse))
	{
		return false;
	}


	return true;
}

s16 Title::bHit(s16 x, s16 y)
{


	if (_bPos_X <= x && _bPos_X + _size * 2 >= x
		&& _bPos_Y <= y && _bPos_Y + _size * 2 >= y)
	{
		return true;
	}

	return false;
}


//ベクトル引き算(a-b)
Vector2  Title::sub_vector(const Vector2& a, const Vector2& b)
{
	Vector2 ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	return ret;
}

// 三角形と点の当たり判定(2Dの場合)
// 戻り値    0:三角形の内側に点がある    1:三角形の外側に点がある
int Title::hittest_point_polygon_2d(Vector2 A, Vector2 B, Vector2 C, Vector2 P) {

	//線上は外とみなします。
	//ABCが三角形かどうかのチェックは省略...

	Vector2 AB = sub_vector(B, A);
	Vector2 BP = sub_vector(P, B);

	Vector2 BC = sub_vector(C, B);
	Vector2 CP = sub_vector(P, C);

	Vector2 CA = sub_vector(A, C);
	Vector2 AP = sub_vector(P, A);

	//外積    Z成分だけ計算すればよいです
	double c1 = AB.x * BP.y - AB.y * BP.x;
	double c2 = BC.x * CP.y - BC.y * CP.x;
	double c3 = CA.x * AP.y - CA.y * AP.x;

	if ((c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0)) {
		//三角形の内側に点がある
		return 0;
	}

	//三角形の外側に点がある
	return 1;

}

void Title::isUp(bool isUp_)
{
	if (isUp_) {
		_isUp = true;
	}
	if (!isUp_) {
		_isUp = false;
	}
}

//! 透過度変更
void Title::mvoeAlpha()
{
	for (s16 i = 0; i < 3; i++) {
		if (_whichOne[i])
			_alpha[i] += 4;
	}

	for (s16 i = 0; i < 3; i++) {
		if (!_whichOne[i])
			_alpha[i] -= 4;
	}

	for (s16 i = 0; i < 3; i++) {
		if (_alpha[i] <= 0) {
			_alpha[i] = 0;
		}
	}
}




//----------------------------------------------
//! プレイ
//----------------------------------------------

//------------------------------------
//! コンストラクタ
//------------------------------------
Play::Play()
{

}

//------------------------------------
//! デストラクタ
//------------------------------------
Play::~Play()
{
}


//------------------------------------
//! アクションがあれば次のシーンへ
//------------------------------------
void Play::nextScene(Scene &scene, bool isEnd_)
{
	if (isEnd_)
		scene = Scene::RESULT;
}



//----------------------------------------------
//! リザルト
//----------------------------------------------

//------------------------------------
//! コンストラクタ
//------------------------------------
Result::Result()
{
	_getScore = true;
	_getRanking = true;

	//!　ランキングのインスタンス
	_rankIns = new Ranking;
	_figure = new figure;
	_fontHandle = CreateFontToHandle(NULL, 50, 3);


	_blinkTimer = 0;
	_alpha = 0;

}

//------------------------------------
//! デストラクタ
//------------------------------------
Result::~Result()
{
}

//------------------------------------
//! アクションがあれば次のシーンへ
//------------------------------------
void Result::nextScene(Scene &scene)
{
	if (PushHitKey(KEY_INPUT_0)) {
		//! しーんきりかえよう
		if (_moveScene == nullptr)
			_moveScene = std::make_unique<moveScene>();

	}

	if (!_moveScene)return;


	if (_moveScene.get()->isEnd()) {
		_moveScene = nullptr;
		scene = Scene::TITLE;
	}



}

//------------------------------------
//! Scoreから持ってくる
//------------------------------------
void Result::setScore(s16 score_)
{
	if (_getScore) {
		_score = score_;
		_getScore = false;
	}
}


//!　リザルトのリセット
void Result::reset()
{

	_getScore = true;
	_getRanking = true;
}

//------------------------------------
//! 更新
//------------------------------------
void Result::update()
{
	if (_getRanking) {
		_rankIns->initialize();
		_rankIns->setScore(_score);
		_rankIns->update();
		_rankIns->Save();
		_getRanking = false;
	}
	_figure->update();
	blink();
	if(_moveScene)
	_moveScene.get()->update(); 

}


//------------------------------------
//! 描画
//------------------------------------
void Result::draw()
{
	if (_moveScene) {
		if (_moveScene.get()->isDown()) {

			DrawString(0, 0, "RESULT", GetColor(255, 255, 255));

			DrawStringToHandle(100, 150, "SCORE", GetColor(255, 255, 255), _fontHandle);
			chengeText2(_score, 180, 200, 255, 255, 255, _fontHandle);

			_rankIns->draw();
			_figure->draw();

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
			DrawStringToHandle(WINDOW_W / 2 + 100, 400, " PUSH 0", GetColor(0, 0, 0), _fontHandle);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
	}
	else
	{
		DrawString(0, 0, "RESULT", GetColor(255, 255, 255));

		DrawStringToHandle(100, 150, "SCORE", GetColor(255, 255, 255), _fontHandle);
		chengeText2(_score, 180, 200, 255, 255, 255, _fontHandle);

		_rankIns->draw();
		_figure->draw();


		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
		DrawStringToHandle(WINDOW_W / 2 + 100, 400, " PUSH 0", GetColor(0, 0, 0), _fontHandle);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	}


	if (_moveScene) {
		_moveScene.get()->draw();

	}


}

void Result::blink()
{
	s16 val = 60;
	s16 speed = 4;

	if (_blinkTimer <= val)
		_alpha += speed;

	if (_blinkTimer >= val)
		_alpha -= speed;

	if (_blinkTimer >= val * 2)
		_blinkTimer = 0;

	if (_alpha <= 0)_alpha = 0;
	if (_alpha >= 255)_alpha = 255;

	_blinkTimer++;
}


//! アニメーション演出用のミニ図形
figure::figure()
{

	_pos[0].set(400, 440);
	_pos[1].set(300, 440);
	_pos[2].set(200, 440);
	_size = 10;

	_speedX[0] = 5;
	_speedY[0] = 2;
	_speedX[1] = -4;
	_speedY[1] = 4;
	_speedX[2] = 2;
	_speedY[2] = 2;

	_flag = 0;
}




figure::~figure()
{
}


void figure::update()
{
	move();
	reflect();

}
void figure::draw()
{

	DrawCircle(_pos[0].x, _pos[0].y, _size, GetColor(255, 0, 0), true);
	DrawTriangle(_pos[1].x, _pos[1].y - _size / 2, _pos[1].x - _size, _pos[1].y + _size, _pos[1].x + _size, _pos[1].y + _size, GetColor(0, 255, 0), true);
	_size = 20;
	DrawBox(_pos[2].x, _pos[2].y, _pos[2].x + _size, _pos[2].y + _size, GetColor(0, 0, 255), true);
	_size = 10;
}

////! 動き回る範囲の指定

bool  figure::c_LimitX()
{
	if (_pos[0].x < 0 || _pos[0].x > 640) {
		return true;
	}
	return false;
}
bool  figure::c_LimitY()
{
	if (_pos[0].y < 350 || _pos[0].y > 480) {

		return true;
	}

	return false;
}

bool figure::t_LimitX()
{
	if (_pos[1].x < 0 || _pos[1].x > 640) {
		return true;
	}
	return false;
}

bool figure::t_LimitY()
{
	if (_pos[1].y < 350 || _pos[1].y > 480) {

		return true;
	}

	return false;
}
bool figure::b_LimitX()
{
	if (_pos[2].x < 0 || _pos[2].x > 640) {
		return true;
	}
	return false;
}

bool figure::b_LimitY()
{
	if (_pos[2].y < 350 || _pos[2].y > 480) {

		return true;
	}

	return false;
}



//! 跳ね返る
void figure::reflect()
{

	if (c_LimitX()) {
		_speedX[0] *= -1;
	}
	if (c_LimitY()) {
		_speedY[0] *= -1;
	}
	if (t_LimitX()) {
		_speedX[1] *= -1;
	}
	if (t_LimitY()) {
		_speedY[1] *= -1;
	}
	if (b_LimitX()) {
		_speedX[2] *= -1;
	}
	if (b_LimitY()) {
		_speedY[2] *= -1;
	}

}

void figure::move()
{
	_pos[0].x += _speedX[0];
	_pos[0].y += _speedY[0];
	_pos[1].x += _speedX[1];
	_pos[1].y += _speedY[1];
	_pos[2].x += _speedX[2];
	_pos[2].y += _speedY[2];


}



Manual::Manual()
{
	_timer = 0;
}

Manual::~Manual()
{
}

void Manual::reset()
{

}
void Manual::update()
{
	_timer++;
}
void Manual::draw()
{

}
