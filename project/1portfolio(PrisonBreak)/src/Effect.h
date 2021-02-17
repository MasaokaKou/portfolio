#pragma once

class Effect {
public:
	Effect();
	~Effect();

	void ImageLoad();
	void PlayerSpeedUp(float x,float y,float x2,float y2);
	void AddLineAlpha();
	
	//{
		////ífîO----------------------------
		//void DrawLanding();
		//void LandingMove();
		//void LandingGravity();
		//void ReSetLanding();
		//void LandingJump();
		//void ChengeLandingFlag();
		//void AddLandingCounter();
		//void SetLandingtPos0();
		//---------------------------------
	//}


	float GetX() { return (float)_enemy_anim_counter; }


	void AddSmokeCounter();
	void DrawSmoke(float x_,float y_);
	void SmokeMove();

	void AddEnemyAnimCount();
	/*{
	void DrawEnemyEffect(float x, float y);
	void SetEnemyPos(float x, float y);
	void MoveEnemyEffect();
	void DeadEneny();
	}*/
	
	void DrawPearl();
	void ChengePearlAlpha();
	void ResetPearlAlpha();

	void SrtCurtain();
	void DrawCurtain();
	void MoveCurtain();
	
private:

	float _v;
	float _gravity;

	int _line_alpha;
//ífîOÅBÅBÅBÅB
	//-------------------------------
		float _cx, _cy;
		bool _c_is_move;
		int _c_effect_counter;
		float _t;
		//ÉxÉWÉFã»ê¸óp
		float p0_x, p0_y;
		float p1_x, p1_y;
		float p2_x, p2_y;
	//-------------------------------
		int _enemy_anim_counter;
		float _ex, _ey;
		float _e_color;
		

	int White;

	int _smoke_image[10];
	int _smoke_counter;

	int _black_pearl;
	int _pearl_alpha;

	int _curtain_x;
	int _curtain_x2;
	int _curtain_y;
	int _curtain_y2;

	int _curtain_alpha;


};