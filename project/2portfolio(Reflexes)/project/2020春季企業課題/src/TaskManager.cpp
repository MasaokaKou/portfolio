#include"Game.h"

#include"TaskManager.h"
#include"Question.h"
#include"Selecter.h"
#include"Effect.h"
#include"TimeLimit.h"
#include"Score.h"



TaskManager::TaskManager()
{
	// ��肪�n�܂�����true�A�I�������false 
	// �n�܂�O��false
	_setGame = false;

	// question�̃C���X�^���X
	_queIns = new Question;
	// selecter�̃C���X�^���X
	_selIns = new Selecter;

	// effectMng�̃C���X�^���X
	_eMngIns = new EffectManager;

	// Time�̃C���X�^���X
	_tLimIns = new TimeLimit;

	// Score�̃C���X�^���X
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
//!�@����̃{�^������������J�n
//-----------------------------------------------
void TaskManager::DebugPlay() {
	if (PushHitKey(KEY_INPUT_0)) {
		setGameState(true);
	}
}

//------------------------------------
//! ���������玟��
//------------------------------------
void TaskManager::nextQue() {
	if (hitChecker()) {
		setGameState(true);
	}
}


//------------------------------------
//! �I�������F��Ԃ��i�������킹�p�j
//------------------------------------

s16 TaskManager::hitChecker()
{

	//! �����蔻��p
	if (!_selIns->hit())return false;

	if (PushMouseInput())
	{

		//! ���p�̔z�F�ԍ�
		s16 que_color = _queIns->getColorNum();
		//! �I�������z�F�ԍ�
		s16 sel_color = _selIns->getColorNum();
		//! ���p�̐}�`�ԍ�
		s16 que_figure = _queIns->getFigureNum();
		//! �I�������z�F�ԍ�
		s16 sel_figure = _selIns->getFigureNum();


		if (que_color == sel_color && que_figure == sel_figure) {
			_eMngIns->isCorrect(true);
			//! �X�R�AUP
			_score->isUp();
			//! �G�t�F�N�g�X�^�[�g
			_eMngIns->isStart();
			return true;
		}
		else if (que_color != sel_color || que_figure != sel_figure)
		{
			_eMngIns->isCorrect(false);
			
			//! �G�t�F�N�g�X�^�[�g
			_eMngIns->isStart();
			_tLimIns->gameEnd();

		}
	}

	return false;
}

//! TimeLimitn�ɃX�R�A��n��
void TaskManager::giveScore()
{
	_tLimIns->setScore(_score->getScore());
}

//! SceneManager�ɃX�R�A��n��
s16 TaskManager::getScore()
{
	return _score->getScore();
}


//! �Q�[���I�[�o�[���ǂ����n��
bool TaskManager::getisEnd()
{
	return _tLimIns->isEnd(); 
}


//------------------------------------
//! ������
//------------------------------------
bool TaskManager::initialize()
{
	// setGame��true�Ȃ珉�������ăX�^�[�g
	// ���Q�[�����Ƃ̏�����


	if (_setGame) {
		_queIns->initialize();
		_selIns->initialize();
		_tLimIns->initialize();
		return true;
	}

	return false;
}

//------------------------------------
//! �X�V
//------------------------------------
void TaskManager::update()
{

	DebugPlay();
	nextQue();
	//! �G�t�F�N�g�̍X�V
	_eMngIns->update();
	//! �������Ԃ̍X�V
	_tLimIns->update();
	//! �X�R�A�̍X�V
	_score->update();
	//! �X�R�A��TimeLimit�ɓn��
	giveScore();


	if (!initialize()) return;

	//! Question��k�X�V
	_queIns->update();
	//! Selecter��k�X�V
	_selIns->update(_queIns->getColorNum() ,_queIns->getFigureNum() );


	setGameState(false);

}

//------------------------------------
//! �`��
//------------------------------------
void TaskManager::draw()
{
	//! Question�̕`��
	_queIns->draw();
	//! Selecter�̕`��
	_selIns->draw();
	//! effect�̕`��
	_eMngIns->draw();
	//! Time�̕`��
	_tLimIns->draw();
	//! score�̕`��
	_score->draw();
}

//------------------------------------
//! �j��
//------------------------------------
void TaskManager::exit()
{
}

