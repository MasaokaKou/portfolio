#pragma once
#include"Typedef.h"
#include<array>




class Ranking
{
public:
	Ranking();
	~Ranking();

	void initialize();  //! ������
	void update();		//! �X�V
	void draw();		//! �`��
	void exit();		//! �j��
	void Save();        

	void drawSceneRanking();		//! �`��
	


	void setScore(s16 score_) { _score = score_; }


	void blink();
private:

	//txt�ɏ������ރX�R�A������p�̔z��(���3�ʂ܂�)
	std::array<s16, 3> _ranking;

	//! ������
	bool _initialized;

	//! ���݃X�R�A
	s16 _score;
	s16 _scoreAlpha;

	//! �����g��p
	s64 _fontHandle;

	//! �����L���O�`���ʂł̓_�ŗp�ϐ�
	s16 _blinkTimer;
	s16 _alpha;

	s16 _char_y;
	
};

