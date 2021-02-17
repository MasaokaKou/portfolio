#pragma once
#include "MainBase.h"


//プレイヤーのclass
class Player :public  MainBase {
public:
	Player();
	virtual ~Player();
	void SetPlayerDir();
	void SetPlayerPos(float x, float y);
	void SetGravity();
	void SetOverWindow();
	void Jump();
	void ResetAniCounter();
	void MoveAction();
	void ForInDoor();
	void ResetDoor();
	void PlayerRender();
	void SetSpeed(float speed);
	void RenderRight(int a, int b, int c);//ani_count
	void AddHitCount();
	void SetWall();
	void AddWallX();
	void LimitWall();
	void Spin();

	void  AddCombo();
	void ResetCombo();

	int GetConbo() { return _combo; }
	int GetAniC() { return ani_counter; }

	int rota_image;
	int ani_count_max;//アニメーションカウントMAX
	
	void DebugMove() { x += 2; }
	void DebugMove2() { x -= 2; }

	int GetHitPoint() { return _hitpoint; }
	void DecHitPoint();
	void DrawHP();

	void GameOver();


 //現在の場所を記録する用
	float old_x;
	float old_y;
	const int  H;
	const int  W;
	//プレイヤー画像の空白部分
	const int SPACE;
	//重力
	bool jump;
	int jump_count;
	//ダメージ受けてるか否か
	bool is_hit;
	void Hit_Render();
	int hit_counter;
	float wall_x;
	float wall0_x;
	//ジャンプ時プレイヤーの回転用
	float rota;
	int ani_counter;//アニメーション用
	

	bool is_landing;

	int _combo;
	int _HP_image;

	int _hitpoint;

	bool	_before_A;
	int		_before_BIT;
private:
	
	
					

};
extern Player player;
extern bool jump;
extern bool check2Pos;

void PlayerInit();
void PlayerUpdate();
void PlayerRender();
