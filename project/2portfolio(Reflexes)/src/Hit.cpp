#include "Main.h"
#include "Hit.h"

//---------------------------------------------------------------------------------
//	�����蔻��֐�
//---------------------------------------------------------------------------------
bool CheckCircleHit( Vector2 &p0, float r0, Vector2 &p1, float r1 )
{
	Vector2 v;
	// p0����p1�������ĉ~���m�̋������o��
	v.subtract( p0, p1 );
	
	// ����p
	float length = v.length();

	//  �ŏ��ɏo���������Ɠ�̔��a�𑫂������̂��ׂ�
	if( length < r0 + r1 ){
		//�@p0����p1�������ĉ~���m�̋������̂ق������������true
		return true;
	}

	return false;
}
