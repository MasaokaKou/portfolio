#pragma once

class Vector2
{
public:
	float	x;
	float	y;

	Vector2();									//	�R���X�g���N�^
	void clear();								//	�[��������
	void set( float x, float y );				//	�l�̃Z�b�g
	void set( Vector2 &v );
	void add( Vector2 &v );						//	�����Z
	void add( Vector2 &v0, Vector2 &v1 );
	void subtract( Vector2 &v );				//	�����Z
	void subtract( Vector2 &v0, Vector2 &v1 );
	void scale( float scale );					//	�|���Z
	float length();								//	�����擾
	void normalize();							//	���K��
	void length( float len );					//	�����ݒ�
};
