#pragma once

class Vector2
{
public:
	float	x;
	float	y;

	Vector2();									//	コンストラクタ
	void clear();								//	ゼロ初期化
	void set( float x, float y );				//	値のセット
	void set( Vector2 &v );
	void add( Vector2 &v );						//	足し算
	void add( Vector2 &v0, Vector2 &v1 );
	void subtract( Vector2 &v );				//	引き算
	void subtract( Vector2 &v0, Vector2 &v1 );
	void scale( float scale );					//	掛け算
	float length();								//	長さ取得
	void normalize();							//	正規化
	void length( float len );					//	長さ設定
};
