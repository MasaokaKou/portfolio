#pragma once
#include"Typedef.h"
//-----------------------------
//! ��������
//! ��傲�Ƃ̐�������
//! �S�̂̌o�ߎ���
//----------------------------


class TimeLimit
{
public:
	TimeLimit();
	~TimeLimit();

	bool initialize();  //! ������
	void update();		//! �X�V
	void draw();		//! �`��
	void exit();		//! �j��

	void reset(); //! �Q�[�����Ƃ̏�����


	//! �b���ϊ�
	void time();

	//! ��������
	void limit();

	//! �E�F�[�u�؂�ւ�	
	void setWave();
	//!�X�R�A������Ă���
	void setScore(s16 score_) { _score = score_; }

	//! �Q�[���I�[�o�[���ǂ���
	bool isEnd() { return _end; }
	//! ���~�X������Q�[���I�[�o�[
	void gameEnd() { _end = true; }

private:

	//! ��傲�Ƃ̐�������
	s16        _limitMax[4];
	s16        _limit;
	
	//! �S�̂̌o�ߎ���
	s16 _time;
	s16 _timeCounter;



	//! ���Ԑ؂ꂩ�ǂ���
	//! true�ɂȂ�����Q�[���I�[�o�[
	bool _end;
	//! �������ԊJ�n
	bool _startLimiter;
	//! �c��O���؂�����Ԃɂ���
	u64 color;

	//!Score����Ƃ��Ă������̂������
	s16 _score;
	//! �Ȃ�E�F�[�u�ڂ�
	s16 _wave;
	f32 _par[3]; //! �����̌v�Z
};




