#pragma once
#include"Typedef.h"
//------------------------------------
//! Effect�֘A�S�ʂ̊Ǘ�
//------------------------------------


//! �Q�[���J�n�̃G�t�F�N�g
//! �Q�[���I���̃G�t�F�N�g



//! �����ƕs�����̃G�t�F�N�g

class EffectBase
{
public:
	EffectBase() {};
	virtual~EffectBase() {};

protected:
	f32 _x, _y; //! ���W
	s16 _size; //! �T�C�Y
};


class Correct
	:public EffectBase
{
public:
	Correct();
	~Correct();

	void draw(); //! �`��

private:
	s16 _size; //! �T�C�Y
	

};

class unCorrect
	:public EffectBase
{
public:
	unCorrect();
	~unCorrect();

	void draw(); //! �`��
private:

};

class EffectManager
{
public:
	EffectManager();
	~EffectManager();

	//! �������ǂ������Ƃ��Ă���
	void isCorrect(bool isCorect_) { _isCorrect = isCorect_; }
	void isStart() { _isStart = true; }

	//! �G�t�F�N�g�̎��Ԓ����p
	s16 Count(s16 timer_);

	void update(); //! �X�V
	void draw();   //! �`��

	void reset();  //! �Q�[�����Ƃ̏�����


private:
	//! �����G�t�F�N�g�̃C���X�^���X
	Correct *corIns;
	//! �s�����G�t�F�N�g�̃C���X�^���X
	unCorrect *unCorIns;
	//! �������ǂ���
	bool _isCorrect;
	//! �G�t�F�N�g�̎��Ԓ����p
	s16 _timer;

	//! �G�t�F�N�g���n�܂��Ă��邩�ǂ���
	bool _isStart;

};

