
#pragma once
#include"Typedef.h"
//! �V�[���̊Ǘ��S��
#include"Vector2.h"

//! �V�[��
enum class Scene
{
	TITLE,    //! �^�C�g��
	PLAY,	  //! �Q�[��
	RESULT,   //! ���U���g
	RANKING,  //! �����L���O
	MANUAL    //! �}�j���A��

};


class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	//! �^�C�g���V�[�����Z�b�g
	void SetTitle() { *_scene = Scene::TITLE; }

	//! �Q�[���̃V�[�����Z�b�g
	void SetGame() { *_scene = Scene::PLAY; }

	//! ���U���g�̃V�[�����Z�b�g
	void SetResult() { *_scene = Scene::RESULT; }

	//! �w�肵�����b�ԑҋ@
	bool wait();

	//! �Q�[���X�^�[�g
	void gsmeStart();

	void update(); //! �X�V
	void draw();   //! �`��

	

	void reset(); //! �Q�[�����Ƃ̏�����


private:
	//! �^�X�N�}�l�[�W���[
	class TaskManager * tMng;

	Scene * _scene;       //! �V�[���̗�

	class Title * _title;  //! �^�C�g���̃C���X�^���X
	class Play * _play;    //! �v���C�̃C���X�^���X
	class Result * _result;//! ���U���g�̃C���X�^���X
	class Ranking * _rank; //! �����L���O�̃C���X�^���X
	class Manual *_manual; //! �}�j���A���̃C���X�^���X

	class Thread * _thread; //! ���̃C���X�^���X

	s16 _time_F; //! �Q�[�����n�܂�܂ł��t���[���\�L
	s16 _time_S; //! �Q�[�����n�܂�܂ł�b���\�L
	s16 _playTime; //! �v���C����

	bool _isStart; //! �Q�[���X�^�[�g

	s64 _fontHandle;



};



class Title
{
public:
	Title();
	~Title();

	//! �A�N�V����������Ύ��̃V�[����
	void nextScene(Scene &scene);

	//! �I�����̐}�`�̓����蔻��
	s16 cHit(s16 x, s16 y); //! �~
	s16 tHit(s16 x,s16 y); //! �O�p�`
	s16 bHit(s16 x, s16 y); //! �l�p

	bool initialize(); //! ������
	void update();	   //! �X�V
	void draw();       //! �`��

	Vector2 sub_vector(const Vector2& a, const Vector2& b);
	int hittest_point_polygon_2d(Vector2 A, Vector2 B, Vector2 C, Vector2 P);
	
	void isUp(bool isUp_);

	//! ���ߓx�ύX
	void mvoeAlpha();

protected:

	s16 _cPos_X, _cPos_Y; //! �~�̈ʒu
	s16 _tPos_X, _tPos_Y; //! �O�p�̈ʒu
	s16 _bPos_X, _bPos_Y; //! �l�p�̈ʒu

	s16 _size;

	bool _isUp; //! �����グ�Ă��邩�ǂ���

	//! �ǂ̐}�`�ɂ������Ă��邩�i�~�A�O�p�A�l�p�j
	s16 _hitNum;
	
	//! �}�`�̒��̕���
	s16 _alpha[3]; //! ���ߓx
	bool _checkAlpha; //! ���ߓx����ON/OFF
	bool _whichOne[3]; //! �ǂꂪON��

	//! �}�`�̓��ߓx
	s16 _figureAlpha;
	

	//! ���[�񂫂肩���悤
	std::unique_ptr< class moveScene > _moveScene;

};

//! �����グ�郂�[�V�����悤�̎�
class Thread:
	public Title
{
public:
	Thread();
	~Thread();

	bool initialize(); //! ������
	bool update();     //! �X�V
	void draw();       //! �`��

	void reset();  //! �Q�[�����Ƃ̃��Z�b�g

	//! �ǂ������N���b�N�������ŏ����ʒu�ݒ�
	void set();
	//! �}�`�ɂ�����܂ŉ��ɍ~��鏈��
	bool down();
	//! �}�`�ɓ�������������グ��
	void up();

	//! �����グ�Ă��邩�ǂ���
	bool getIsUp() { return _isUp; }
	//! �N�b���b�N�����痎�Ƃ�
	void setDown();

	//! �������Ă邩�ǂ���
	bool isHit(s16 x, s16 y);

	
private:
	Vector2 _pos;  //! �ʒu
	f32     _size; //! �T�C�Y

	bool _isUp; //! �����グ�Ă��邩�ǂ���
	bool _isDown; //! �����Ă邩�ǂ���

	
	
};


class Play
{
public:
	Play();
	~Play();

	//! �A�N�V����������Ύ��̃V�[����
	void nextScene(Scene &scene, bool isEnd_);

private:

};

//! �A�j���[�V�������o�p�̃~�j�}�`
class figure
{
public:
	figure();
	~figure();

	void update();
	void draw();

	//! �������͈͂̎w��
	bool c_LimitX();
	bool c_LimitY();
	bool t_LimitX();
	bool t_LimitY();
	bool b_LimitX();
	bool b_LimitY();



	//! ���˕Ԃ�
	void reflect();

	void move();

private:
	//! �O�̐}�`
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

	//! �A�N�V����������Ύ��̃V�[����
	void nextScene(Scene &scene);
	void update(); //! �X�V
	void draw();   //! �`��

	void reset(); //!�@���U���g�̃��Z�b�g

	//! Score���玝���Ă���
	void setScore(s16 score_);

	void blink();
private:

	s16 _score; //! �`�悷��悤
	bool _getScore; //! ��x�����X�R�A���󂯂Ƃ�
	bool _getRanking;//! ��x���������L���O����

	//!�@�����L���O�̃C���X�^���X
	class Ranking * _rankIns;
	class figure * _figure;

	s16 _blinkTimer;
	s16 _alpha;

	s64 _fontHandle;
	//! ���[�񂫂肩���悤
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

