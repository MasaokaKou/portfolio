#pragma once
#include"Main.h"
//---------------------------------------------
// !quiz�S�̂̊Ǘ�
//---------------------------------------------

class TaskManager
{
public:
	TaskManager();
	~TaskManager();

	bool initialize();  //! ������
	void update();		//! �X�V
	void draw();		//! �`��
	void exit();		//! �j��

	void reset(); //! �Q�[�����Ƃ̏�����

	//! �I�������F��Ԃ��i�������킹�p�j
	s16 hitChecker();

	//! ���������玟��
	void nextQue();

	//! TimeLimitn�ɃX�R�A��n��
	void giveScore();
	s16 getScore();
	void setGameState(bool flag) { _setGame = flag; }

	bool getisEnd();

	// debug-----------------------------------------
	void DebugPlay();
	//-----------------------------------------------
private:
	// ��肪�n�܂�����true�A�I�������false 
	bool _setGame;

	// question�̃C���X�^���X
	class Question *_queIns;
	// selecter�̃C���X�^���X
	class Selecter *_selIns;
	// effectMng�̃C���X�^���X
	class EffectManager * _eMngIns;
	// Time�̃C���X�^���X
	class TimeLimit * _tLimIns;
	// Score�̃C���X�^���X
	class Score * _score;

	


};

