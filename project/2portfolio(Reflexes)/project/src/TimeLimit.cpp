#include"TimeLimit.h"
#include"Main.h"


//-----------------------
//!�R���X�g���N�^
//-----------------------
TimeLimit::TimeLimit()
{
	//! ��傲�Ƃ̐�������
	_limit = 300;
	//! �S�̂̌o�ߎ���
	_time = 0;
	_timeCounter = 0;

	//! ���Ԑ؂ꂩ�ǂ���
    _end = false;

	//! �������ԊJ�n
	_startLimiter = false;

	color = GetColor(255, 255, 255);

	_limitMax[0] = 300;
	_limitMax[1] = 180;
	_limitMax[2] = 120;
	_limitMax[3] = 60;
	//! �����̌v�Z
	_par[0] = 120.0f; 
	
	//! �Ȃ�E�F�[�u�ڂ�
	_wave = 0;
}

//-----------------------
//!�f�X�g���N�^
//-----------------------
TimeLimit::~TimeLimit()
{
}


//! �Q�[�����Ƃ̏�����
void TimeLimit::reset()
{//! ��傲�Ƃ̐�������
	_limit = 300;
	//! �S�̂̌o�ߎ���
	_time = 0;
	_timeCounter = 0;

	//! ���Ԑ؂ꂩ�ǂ���
	_end = false;

	//! �������ԊJ�n
	_startLimiter = true;

	//! �Ȃ�E�F�[�u�ڂ�
	_wave = 0;

	color = GetColor(255, 255, 255);

}

//! �b���ϊ�
void TimeLimit::time()
{

	_timeCounter++;
	if (_timeCounter % 60 == 0)
	{
		_time++;
	}
}


//! ��������
void TimeLimit::limit()
{
	if (_limit <= 0) {
		_limit = 0;
		_end = true;

	}
}

//! �E�F�[�u�؂�ւ�	
void TimeLimit::setWave()
{
	
	if (_score == 400) {
		_wave = 3;
	}else	
	if (_score == 300) {
		_wave = 2;
	}else
	if (_score == 150) {
		_wave = 1;
	}
	
}

//! ������
bool TimeLimit::initialize()
{
	_end = false;

	//! ��傲�Ƃ̐�������
	setWave();
	_limit = _limitMax[0 +_wave];
	color = GetColor(255, 255, 255);
	_startLimiter = true;
	return false;
}

//! �X�V
void TimeLimit::update() 
{
	time();
	limit();
	

	if (_startLimiter) {
		_limit--;
	}


if (_limit <= _limitMax[0 + _wave] * 0.4)
		color = GetColor(255, 0, 0);


}

//! �`��
void TimeLimit::draw()
{
	//! �E�C���h�E�T�C�Y

	s16 size = 60;
	

	//checgeText(_time, 640 / 2 - 10 , 0, 255, 255, 255);
	//checgeText(_limit, 640 / 2 , 0, 255, 255, 255);
	//checgeText(_wave, 640 / 2, 20, 255, 255, 255);

	if (_wave == 1) {
		int a = 0;
	}
	
	DrawBox(WINDOW_W / 2 + size -(_limit  / (_limitMax[0 + _wave] / (_par[0]))), 20, WINDOW_W / 2 + size, 40, color, true);
	DrawBox(WINDOW_W / 2 - size, 20, WINDOW_W / 2 + size, 40,GetColor(255, 255, 255), false);



}
