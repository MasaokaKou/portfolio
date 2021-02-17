#include"SceneManager.h"
#include"TaskManager.h"
#include"Main.h"
#include"SceneRanking.h"


//----------------------------------------------
//! �V�[���}�l�[�W���[
//----------------------------------------------

//------------------------------------
//! �R���X�g���N�^
//------------------------------------
SceneManager::SceneManager()
{

	//! �V�[���̗�
	_scene = new Scene;
	*_scene = Scene::TITLE;

	//! �^�X�N�}�l�[�W���[
	tMng = new TaskManager;

	//! �^�C�g���̃C���X�^���X
	_title = new Title;
	//! �v���C�̃C���X�^���X
	_play = new Play;
	//! ���U���g�̃C���X�^���X
	_result = new Result;

	//! �����L���O�̃C���X�^���X
	_rank = new Ranking;

	//! �}�j���A���̃C���X�^���X
	_manual = new Manual;


	//! ���̃C���X�^���X
	_thread = new Thread;

	_time_F = 480;
	_time_S = 4;

	_playTime = 0;

	_isStart = false;


	_fontHandle = CreateFontToHandle(NULL, 90, 3);
}

//------------------------------------
//! �f�X�g���N�^
//------------------------------------
SceneManager::~SceneManager()
{
}

//! �Q�[�����Ƃ̏�����
void SceneManager::reset()
{

	_time_F = 600;
	_time_S = 5;
	_title->initialize();
	_thread->reset();
	tMng->reset();
	_rank->exit();

}

//! �Q�[���X�^�[�g
void SceneManager::gsmeStart()
{
	//! �Q�[�����n�܂����u�Ԃ����Ƃ��Ă���
	//! _isStart����x����true�ɂ���
	if (_playTime == 0)
		_isStart = true;

	if (_isStart) {
		tMng->setGameState(true);
		_isStart = false;
	}
}

//------------------------------------
//! �X�V
//------------------------------------
void SceneManager::update()
{

	switch (*_scene)
	{
	case Scene::TITLE:
		_result->reset();

		_title->update();
		//! �����}�`�ɂ������Ă����TITLE�̃t���O��ς���
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
//! �`��
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

//! �w�肵�����b�ԑҋ@
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
//! ��
//----------------------------------------------

Thread::Thread()
{
	_pos.set(0.0f, 0.0f);//! �ʒu
	_size = 5.0f;        //! �T�C�Y
	_isUp = false;       //! �����グ�Ă��邩�ǂ���
	_isDown = false;	 //! �����Ă邩�ǂ���
}

Thread::~Thread()
{
}

//------------------------------------
//! �Q�[�����Ƃ̃��Z�b�g
//------------------------------------
void Thread::reset()
{
	_pos.set(0.0f, 0.0f);//! �ʒu
	_size = 5.0f;        //! �T�C�Y
	_isUp = false;       //! �����グ�Ă��邩�ǂ���
	_isDown = false;	 //! �����Ă邩�ǂ���
}

//------------------------------------
//! ������
//------------------------------------
bool Thread::initialize()
{
	if (_size <= 0)
	{
		_pos.set(0.0f, -120.0f);//! �ʒu
		_size = 0.0f;        //! �T�C�Y
		_isUp = false;       //! �����グ�Ă��邩�ǂ���
		_isDown = false;	 //! �����Ă邩�ǂ���
		return true;
	}

	return false;
}


//------------------------------------
//! �X�V
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
//! �`��
//------------------------------------
void Thread::draw()
{

	DrawLine(_pos.x, _pos.y, _pos.x, _pos.y + _size, GetColor(255, 255, 255));
}

//------------------------------------
//! �ǂ������N���b�N�������ŏ����ʒu�ݒ�
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
//! �}�`�ɂ�����܂ŉ��ɍ~��鏈��
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
//! �}�`�ɓ�������������グ��
//------------------------------------
void Thread::up()
{
	if (down())
		_size -= 6;
}

//------------------------------------
//! �N�b���b�N�����痎�Ƃ�
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
//! �������Ă邩�ǂ���
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
//! �^�C�g��
//----------------------------------------------

//------------------------------------
//! �R���X�g���N�^
//------------------------------------
Title::Title()
{
	//! �~�̈ʒu
	_cPos_X = WINDOW_W * 0.5f;
	_cPos_Y = WINDOW_H * 0.75f;
	//! �O�p�̈ʒu
	_tPos_X = WINDOW_W / 5;
	_tPos_Y = WINDOW_H - 250;
	//! �l�p�̈ʒu
	_bPos_X = WINDOW_W / 2 + 130;
	_bPos_Y = WINDOW_H / 2 - 50;

	//!�}�`�̃T�C�Y
	_size = 60;

	//! �����グ�Ă��邩�ǂ���
	_isUp = false;
	//! �ǂ̐}�`�ɂ������Ă��邩�i�~�A�O�p�A�l�p�j
	_hitNum = 0;

	_figureAlpha = 0;
	//! ���ߓx
	_checkAlpha = false;
	for (s16 i = 0; i < 3; i++) {
		_alpha[i] = 0;
		_whichOne[i] = false;

	}
}

//------------------------------------
//! �f�X�g���N�^
//------------------------------------
Title::~Title()
{
}

//------------------------------------
//! ������
//------------------------------------
bool Title::initialize()
{
	//! �~�̈ʒu
	_cPos_X = WINDOW_W * 0.5f;
	_cPos_Y = WINDOW_H * 0.75f;
	//! �O�p�̈ʒu
	_tPos_X = WINDOW_W / 5;
	_tPos_Y = WINDOW_H - 250;
	//! �l�p�̈ʒu
	_bPos_X = WINDOW_W / 2 + 130;
	_bPos_Y = WINDOW_H / 2 - 50;

	//! �����グ�Ă��邩�ǂ���
	_isUp = false;
	//! �ǂ̐}�`�ɂ������Ă��邩�i�~�A�O�p�A�l�p�j
	_hitNum = 0;

	//! ���ߓx
	_checkAlpha = false;
	for (s16 i = 0; i < 3; i++) {
		_alpha[i] = 0;
		_whichOne[i] = false;

	}

	_figureAlpha = 0;
	return true;
}

//------------------------------------
//! �X�V
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
//! �`��
//------------------------------------
void Title::draw()
{

	if (_moveScene) {
		_moveScene.get()->draw();

		if (!_moveScene.get()->isDown()) return;

	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _figureAlpha);
	
	//! �~�̕`��
	DrawCircle(_cPos_X, _cPos_Y, _size, GetColor(255, 255, 255), true);
	if (cHit(GetMouseX(), GetMouseY()))
		DrawCircle(_cPos_X, _cPos_Y, _size, GetColor(0, 255, 0), true);

	//! �O�p�`�̕`��
	DrawTriangle(_tPos_X, _tPos_Y - _size * (0.5f), _tPos_X - _size, _tPos_Y + _size, _tPos_X + _size, _tPos_Y + _size, GetColor(255, 255, 255), true);
	if (tHit(GetMouseX(), GetMouseY()))
		DrawTriangle(_tPos_X, _tPos_Y - _size * (0.5f), _tPos_X - _size, _tPos_Y + _size, _tPos_X + _size, _tPos_Y + _size, GetColor(255, 0, 0), true);


	//! �l�p�`�̕`��
	DrawBox(_bPos_X, _bPos_Y, _bPos_X + (_size * 2), _bPos_Y + (_size * 2), GetColor(255, 255, 255), true);
	if (bHit(GetMouseX(), GetMouseY()))
		DrawBox(_bPos_X, _bPos_Y, _bPos_X + (_size * 2), _bPos_Y + (_size * 2), GetColor(0, 106, 182), true);

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	//! �}�`�̒��̕���
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
//! �A�N�V����������Ύ��̃V�[����
//------------------------------------
void Title::nextScene(Scene &scene)
{
	if (_cPos_Y + _size <= 0)
	{

		//! ���[�񂫂肩���悤
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
		//! ���[�񂫂肩���悤
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
		//! ���ߓx������
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


//! �I�����̐}�`�̓����蔻��
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
	//! �O�p�p
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


//�x�N�g�������Z(a-b)
Vector2  Title::sub_vector(const Vector2& a, const Vector2& b)
{
	Vector2 ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	return ret;
}

// �O�p�`�Ɠ_�̓����蔻��(2D�̏ꍇ)
// �߂�l    0:�O�p�`�̓����ɓ_������    1:�O�p�`�̊O���ɓ_������
int Title::hittest_point_polygon_2d(Vector2 A, Vector2 B, Vector2 C, Vector2 P) {

	//����͊O�Ƃ݂Ȃ��܂��B
	//ABC���O�p�`���ǂ����̃`�F�b�N�͏ȗ�...

	Vector2 AB = sub_vector(B, A);
	Vector2 BP = sub_vector(P, B);

	Vector2 BC = sub_vector(C, B);
	Vector2 CP = sub_vector(P, C);

	Vector2 CA = sub_vector(A, C);
	Vector2 AP = sub_vector(P, A);

	//�O��    Z���������v�Z����΂悢�ł�
	double c1 = AB.x * BP.y - AB.y * BP.x;
	double c2 = BC.x * CP.y - BC.y * CP.x;
	double c3 = CA.x * AP.y - CA.y * AP.x;

	if ((c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0)) {
		//�O�p�`�̓����ɓ_������
		return 0;
	}

	//�O�p�`�̊O���ɓ_������
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

//! ���ߓx�ύX
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
//! �v���C
//----------------------------------------------

//------------------------------------
//! �R���X�g���N�^
//------------------------------------
Play::Play()
{

}

//------------------------------------
//! �f�X�g���N�^
//------------------------------------
Play::~Play()
{
}


//------------------------------------
//! �A�N�V����������Ύ��̃V�[����
//------------------------------------
void Play::nextScene(Scene &scene, bool isEnd_)
{
	if (isEnd_)
		scene = Scene::RESULT;
}



//----------------------------------------------
//! ���U���g
//----------------------------------------------

//------------------------------------
//! �R���X�g���N�^
//------------------------------------
Result::Result()
{
	_getScore = true;
	_getRanking = true;

	//!�@�����L���O�̃C���X�^���X
	_rankIns = new Ranking;
	_figure = new figure;
	_fontHandle = CreateFontToHandle(NULL, 50, 3);


	_blinkTimer = 0;
	_alpha = 0;

}

//------------------------------------
//! �f�X�g���N�^
//------------------------------------
Result::~Result()
{
}

//------------------------------------
//! �A�N�V����������Ύ��̃V�[����
//------------------------------------
void Result::nextScene(Scene &scene)
{
	if (PushHitKey(KEY_INPUT_0)) {
		//! ���[�񂫂肩���悤
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
//! Score���玝���Ă���
//------------------------------------
void Result::setScore(s16 score_)
{
	if (_getScore) {
		_score = score_;
		_getScore = false;
	}
}


//!�@���U���g�̃��Z�b�g
void Result::reset()
{

	_getScore = true;
	_getRanking = true;
}

//------------------------------------
//! �X�V
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
//! �`��
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


//! �A�j���[�V�������o�p�̃~�j�}�`
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

////! �������͈͂̎w��

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



//! ���˕Ԃ�
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
