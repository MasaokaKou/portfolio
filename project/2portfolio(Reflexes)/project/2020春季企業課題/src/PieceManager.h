#pragma once
//--------------------------------------------
//!��̃}�l�[�W���[
//!�x�[�X�̋�ɎO��ނ�U�蓖�Ă�
//--------------------------------------------
#include"BasePiece.h"
#include<vector>


class PieceManager
{
public:
	PieceManager();
	~PieceManager();
	
	// �x�[�X�s�[�X���T����
	void createEmpty();

	// ��̏������W�ݒ�
	void setPos();

	// �O��ނ̖������T�̋�ɐU�肠�Ă�
	void setRole(int pieceNum, int role);
	void applyRole();

	// �����蔻��
	void hitCheck();

	// ��̕`��
	void DrawPiece();

	// �S�̂̍X�V
	void update();
private:
	// �x�[�X�̃s�[�X�A������ق��̃s�[�X��new����
	std::vector<BasePiece*> _pieces;

	bool _initialize; // �������t���O

};

