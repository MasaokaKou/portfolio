#include"Effect.h"
#include"Main.h"

//------------------------------------
//! Effect�֘A�S�ʂ̊Ǘ�
//------------------------------------
EffectManager::EffectManager()
{

	//! �������ǂ���
	_isCorrect = false;
	
	//! �G�t�F�N�g�̎��Ԓ����p
	_timer = 0;

	//! �����G�t�F�N�g�̃C���X�^���X
	corIns = new Correct;

	//! �s�����G�t�F�N�g�̃C���X�^���X
	unCorIns = new unCorrect;

	//! �G�t�F�N�g���n�܂��Ă��邩�ǂ���
	_isStart = false;


}

EffectManager::~EffectManager()
{
}

//! �Q�[�����Ƃ̏�����
void EffectManager::reset()
{
	//! �������ǂ���
	_isCorrect = false;

	//! �G�t�F�N�g�̎��Ԓ����p
	_timer = 0;

	//! �����G�t�F�N�g�̃C���X�^���X
	corIns = new Correct;

	//! �s�����G�t�F�N�g�̃C���X�^���X
	unCorIns = new unCorrect;

	//! �G�t�F�N�g���n�܂��Ă��邩�ǂ���
	_isStart = false;
}


void EffectManager::update()
{
	
	Count(15);
	
}


void EffectManager::draw()
{
	if (!_isStart)return;

	if (_isCorrect) {
		corIns->draw();
	}

	if (!_isCorrect) {
		unCorIns->draw();
	}


}

//------------------------------------
//! �G�t�F�N�g�̎��Ԓ����p
//------------------------------------
s16 EffectManager::Count(s16 timer_)
{

	if(!_isStart)
	_timer = timer_;


	if(_timer <=0)
	{
		_isStart = false;
		_timer = 0;
		return true;
	}
	else
	{
		_timer--;
	}


	return false;
}

//------------------------------------
//! �����ƕs�����̃G�t�F�N�g
//------------------------------------
Correct::Correct()
{
	_x = 640.0f / 2.0f;
	_y = 480.0f / 2.0f;
	_size = 150;
}

Correct::~Correct()
{
}


//------------------------------------
//! �`��
//------------------------------------
void Correct::draw()
{
	for(f32 i = 0;i < 15.0f ; i+=0.5f)
	DrawCircle(_x, _y, _size - i, GetColor(255, 0, 0), false);
	
}

unCorrect::unCorrect()
{
	_x = 640.0f / 2.0f - 100.0f;
	_y = 480.0f / 2.0f - 100.0f;
	_size = 250;
}

unCorrect::~unCorrect()
{
}

//------------------------------------
//! �`��
//------------------------------------

void unCorrect::draw()
{
	s16 x1 = _x;
	s16 y1 = _y;
	s16 x2 = _x + _size;
	s16 y2 = _y + _size;


	DrawLine(x1, y1, x2, y2, GetColor(255, 0, 0), 10);

	DrawLine(x2, y1, x1, y2, GetColor(255, 0, 0), 10);

}
