#pragma once
#include"Typedef.h"
#include"Vector2.h"
//--------------------------------
//! ��̊�b
//--------------------------------
class BasePiece
{
public:
	BasePiece();
	~BasePiece();

	// �ϋv�͂̑���(���������A���̐��l)
	void moveHp(bool IncOrDec , int atack);

	// ���������G�Ƀ_���[�W��^����
	void giveDamage();

	// �X�s�[�h�̑���
	// �G�ɂ��Ă����́u_speed * 0.7�v�ǂɂ��Ă����́u_speed * 0.3�v�̌���
	// _speed��0�ȉ��ɂȂ�ƂƂ܂�
	void decSpeed();

	// ��̏����z�u�ݒ�(X���W��Y���W)
	void setPos(s64 x_, s64 y_);

	// ��������U���Ă��Ȃ����܂�`��
	virtual void draw();

	// debug�̈ړ�
	void debugController();

	// Getter
	Vector2 getPos() { return _pos; }
	s64 getRadius() { return _r; }
protected:

 s64 _hitPoint;  //! �ϋv��
 s64 _attack;    //! �U����
 s64 _weight;    //! �d��
 f32 _speed;     //! ���x

 f32 _dir;       //! �ǂ��������Ă��邩

 s64 _r;  //! ���a
 Vector2 _pos;  //! x���W�A�����W


};





