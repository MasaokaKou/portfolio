#include "Main.h"
#include "Hit.h"

//---------------------------------------------------------------------------------
//	当たり判定関数
//---------------------------------------------------------------------------------
bool CheckCircleHit( Vector2 &p0, float r0, Vector2 &p1, float r1 )
{
	Vector2 v;
	// p0からp1を引いて円同士の距離を出す
	v.subtract( p0, p1 );
	
	// 判定用
	float length = v.length();

	//  最初に出した距離と二つの半径を足したものを比べる
	if( length < r0 + r1 ){
		//　p0からp1を引いて円同士の距離をのほうが小さければtrue
		return true;
	}

	return false;
}
