#pragma once
#include"Base.h"

//------------------------------------
//!�����o�����߂̃N���X
//------------------------------------

class Question
	:public Base
{
public:
	Question();
	~Question();

	bool initialize();  //! ������
	void update();		//! �X�V
	void draw();		//! �`��
	void exit();		//! �j��

	// ��������
	void setQue();
	//// �o�������ɂ���Ė��̔z�F�����߂�
	void setCol();

	// ���ɂȂ��Ă���F��Ԃ��i�������킹�p�j
	SELECT &getSelectColor() { return que_color; }
	// ���ɂȂ��Ă���F�ԍ���Ԃ��i�������킹�p�j
	s16 &getColorNum() { return _color[0]; }
	s16 &getFigureNum() { return _fig[0]; }
private:

	SELECT que_color;




};

