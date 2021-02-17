#include"MAIN.H"
#include"Game.h"
#include"Effect.h"
#include"player.h"
#include"map.h"
#include"sound.h"
Effect::Effect() {
	White = GetColor(255, 255, 255);
	_v = 0.0;
	_gravity = -0.5;
	_c_is_move = false;
	_c_effect_counter = 0;

	_line_alpha = 255;

	_smoke_counter = 0;
	_enemy_anim_counter = 0;

	_pearl_alpha = 255;
}

Effect::~Effect() {


}


//画像読み込み
void Effect::ImageLoad() {
	LoadDivGraph("data/smoke.png", 3, 3, 1, 54, 79, _smoke_image);
	_black_pearl = LoadGraph("data/black_pearl.png", true);
}

//プレイヤーのスピードアップ時のエフェクト
void Effect::PlayerSpeedUp(float x, float y, float x2, float y2) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA,_line_alpha);
	if (scene == GAME) DrawLine((int)x, (int)y, (int)x2, (int)y2, White, (int)1.0f);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void Effect::AddLineAlpha() {
	
	if (_line_alpha >= 0) {
		_line_alpha -= 5;
	}
	else {
		_line_alpha =255;
	}

}



	////-------------------------------
	////プレイヤーの着地時のエフェクト
	////-------------------------------
	//
	//
	//void Effect::DrawLanding() {
	//	DrawCircle(_cx, _cy, 2, White);
	//}
	//
	////エフェクトのカウンター増加
	//void Effect::AddLandingCounter() {
	//	if (_c_is_move==true) {
	//    _c_effect_counter++;
	//	}
	//
	//}
	//
	//
	//
	////エフェクトの重力設定
	//void Effect::LandingGravity() {
	//	_v += _gravity;
	//	_cy -= _v;
	//}
	//
	////位置リセット
	//void Effect::ReSetLanding() {
	//	int count = _c_effect_counter;
	//
	//	if (count >30) {
	//		_cx = player.GetX() - map.scl;
	//		_cy= player.GetY() + 20;
	//	}
	//	
	//	if (_cy > player.GetY() + 20) {
	//		_cy = player.GetY() +20;
	//	}
	//
	//}

	//
	////跳ねる用のフラグ切り替え
	//void Effect::ChengeLandingFlag() {
	//	if (player.is_landing==true) {
	//		_c_is_move = true;
	//	}
	//	}
	//
	////ベジェ曲線用の座標セット
	//void Effect::SetLandingtPos0() {
	//	p0_x = 0;
	//	p0_y = 320;
	//	p1_x =  320;
	//	p1_y = 0;
	//	p2_x = 640;
	//	p2_y = 320;
	//}
	//
	//
	////エフェクトが跳ねる
	//void Effect::LandingJump() {
	//	int count = _c_effect_counter;
	//	
	//	//if (count>0)
	//	{
	//		_t += 0.025;
	//		_cx = ((1 - _t)*(1 - _t)*p0_x + 2 * (1 - _t)*_t*p1_x + _t * _t*p2_x);
	//		_cy = ((1 - _t)*(1 - _t)*p0_y + 2 * (1 - _t)*_t*p1_y + _t * _t*p2_y);
	//	}
	//	
	//	if (_t > 1.0f) {
	//		_t = 0.0f;
	//		//_c_is_move = false;
	//		//_c_effect_counter = 0;
	//		//player.is_landing = false;
	//	}
	//}
	//
	//
	//void Effect::LandingMove() {
	//	
	//	ChengeLandingFlag();
	//	LandingJump();
	//	LandingGravity();
	//	AddLandingCounter();
	//	ReSetLanding();
	//	SetLandingtPos0();
	//
	//
	//	
	//}


//煙アニメーション用カウンター
void Effect::AddSmokeCounter() {
	if (scene == GAME) {
		_smoke_counter = (_smoke_counter + 1) % 30;
	}
}

void Effect::DrawSmoke(float x_, float y_) {
	
	if (_smoke_counter > 0 && _smoke_counter < 10) {
		DrawRotaGraph((float)x_ + (float)30.0, (float)y_, (float)0.7f, (float)1.75f, _smoke_image[0], true);
	}
	else if (_smoke_counter >= 10 && _smoke_counter < 20) {
		DrawRotaGraph((float)x_ + (float)30.0f, (float)y_ , (float)0.7f, (float)1.75f, _smoke_image[1], true);
	}																			   
	else if (_smoke_counter >= 20 && _smoke_counter < 30) {						   
		DrawRotaGraph((float)x_ + (float)30.0f, (float)y_ , (float)0.7f, (float)1.75f, _smoke_image[2], true);
	}



}

void Effect::SmokeMove() {
	AddSmokeCounter();
}


//エネミー死亡時のエフェクト
void Effect::AddEnemyAnimCount() {
	_enemy_anim_counter++;
	if (_enemy_anim_counter > 60) _enemy_anim_counter = 0;
}


void Effect::DrawPearl() {
	if (sound.GetC() >= 5 && sound.GetC() <= 30) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _pearl_alpha);
		DrawGraph((int)player.GetX() - (int)map.scl - (int)15.0f , (int)player.GetY() - (int)10.0f, _black_pearl, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

void Effect::ChengePearlAlpha() {
	if (sound.GetC() >= 5 && sound.GetC() <= 30) {
		if (_pearl_alpha >= 0) {
			_pearl_alpha -= 10;
		}
	}
}

void Effect::ResetPearlAlpha() {
	if (sound.GetC() > 30) {
		_pearl_alpha=255;
	}

}


//シーン切り替えSelect->Game

void Effect::SrtCurtain() {

}

void Effect::DrawCurtain() {

}

void Effect::MoveCurtain() {


}