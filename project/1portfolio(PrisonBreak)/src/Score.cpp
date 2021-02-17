#include"MAIN.H"
#include"GAME.H"
#include"Score.h""
#include"map.h"
#include"player.h"
Score::Score() {
	_score = 0;
	_counter = 0;
	_time = 0;

	_re_score = 0;
	_re_time=0;
}

Score::~Score() {


}

//��ɃJ�E���g����
void Score::AddCount() {
	if (scene == GAME) {
		_counter++;
	}
}

//��b���A�}�b�v�X�s�[�h�̑����ɂ��X�R�A����
void Score::Add() {
	if (_counter % 60 == 0) {
		if (map.GetSpeed() == 1.6f) {
			_score += 20;
		}
		else if (map.GetSpeed() == 2.0f) {
			_score += 40;
		}
		else if (map.GetSpeed() == 2.5f) {
			_score += 60;
		}
	}
}

//���ԉ��Z
void Score::AddTime() {
	if (scene == GAME) {
		if (_counter != 0&&_counter % 60 == 0) {
			_time++;
		}
	}
}



//�G�l�~�[��|�����Ƃ�
void Score::AddEnemyScore() {
	if (player.GetConbo() ==1) {
		_score += 100;
	}
	else if (player.GetConbo() ==2)
	{
		_score += 150;
	}
	else if (player.GetConbo() == 3)
	{
		_score += 200;
	}
	else if (player.GetConbo() == 4)
	{
		_score += 250;
	}
	else if (player.GetConbo() >= 5) {
		_score += 300;
	}

}

//�R�C�����������
void Score::AddCoinScore() {
	
	_score +=500;

}

//���Z�b�g��
void Score::Reset() {
	_score = 0;
	_time = 0;
}

//�X�R�A�`��
void Score::Show() {
	if (scene == GAME || scene == RESULT || scene == GAMEOVER) {
		char text[256];
		sprintf_s(text, "%d", _score);
		char text2[256];
		sprintf_s(text2, "%d", _time);
		DrawString(350, 275, "score", GetColor(255, 255, 255));
		DrawString(400, 275, text, GetColor(255, 255, 255));
		DrawString(350, 290, "time", GetColor(255, 255, 255));
		DrawString(400, 290, text2, GetColor(255, 255, 255));

	}
}

//�X�R�A�Ǝ��Ԃ̎󂯓n��
void Score::GiveData1() {
	if (_re_score <= _score) {
		_re_score+=50;
	}

	if (_re_score > _score) {
		_re_score = _score;
	}

	if (_re_time < _time&&_re_score == _score) {
		_re_time++;
	}
}

//���U���g��ʂŕ`��
void Score::ShowResult(){
	char text[256];
	sprintf_s(text, "%d", _re_score);
	char text2[256];
	sprintf_s(text2, "%d", _re_time);
	
	if (scene == RESULT) {
		DrawString(290, 130, "score", GetColor(255, 255, 255));
		DrawString(290, 150, text, GetColor(255, 255, 255));
		DrawString(290, 170, "time", GetColor(255, 255, 255));
		DrawString(290, 190, text2, GetColor(255, 255, 255));

	}
}

//�Q�[���I�����̃f�[�^���Z�b�g
void Score::ResetData() {
	if (scene == GAME) {
		_re_score = 0;
		_re_time = 0;
	}
}