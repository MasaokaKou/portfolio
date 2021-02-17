#pragma once
#include"Typedef.h"
#include"Vector2.h"
//--------------------------------
//! 駒の基礎
//--------------------------------
class BasePiece
{
public:
	BasePiece();
	~BasePiece();

	// 耐久力の増減(増か減か、その数値)
	void moveHp(bool IncOrDec , int atack);

	// 当たった敵にダメージを与える
	void giveDamage();

	// スピードの増減
	// 敵にあてた時は「_speed * 0.7」壁にあてた時は「_speed * 0.3」の減速
	// _speedが0以下になるととまる
	void decSpeed();

	// 駒の初期配置設定(X座標とY座標)
	void setPos(s64 x_, s64 y_);

	// 何も割り振っていないこまを描画
	virtual void draw();

	// debugの移動
	void debugController();

	// Getter
	Vector2 getPos() { return _pos; }
	s64 getRadius() { return _r; }
protected:

 s64 _hitPoint;  //! 耐久力
 s64 _attack;    //! 攻撃力
 s64 _weight;    //! 重さ
 f32 _speed;     //! 速度

 f32 _dir;       //! どこを向いているか

 s64 _r;  //! 半径
 Vector2 _pos;  //! x座標、ｙ座標


};





