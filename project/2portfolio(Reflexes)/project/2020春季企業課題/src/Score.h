#pragma once
#include"Typedef.h"

//-------------------------------
//! �X�R�A
//-------------------------------
class Score
{
public:
	Score();
	~Score();
	void update(); //! �X�V
	void draw();   //! �`��

	void reset();  //! �Q�[�����Ƃ̏�����

	//! ���_
	void add();
	
	//! �������Ԃւ̎󂯓n��
	s16 getScore() { return _score; }

	//! �^�X�N�}�l�[�W���[�ő���
	void isUp() { _isUp = true; }

private:
	s16 _score; //! �X�R�A
	bool _isUp; //! ���_����Ă邩�ǂ���
};

