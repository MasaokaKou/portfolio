#include "Enemy.h"
#include"player.h"
#include"MainBase.h"
#include"Game.h"
#include"Main.h"
#include"title.h"
#include"map.h"
#include"sound.h"


Enemy::Enemy()
{
	//for (int i = 0; i < ENEMY_MAX; i++)
	{
		//enemy_image[5];
	}
	x = 0;
	y = 0;
	ani_counter = 0;
	is_dead = false;
	score = false;
	_blend = 255;
}

Enemy::~Enemy()
{

}

void Enemy::Load() {
	LoadDivGraph("data/Monster1.png", 96, 12, 8, 32, 32, enemy_image);
}

void Enemy::Update() {
	ani_counter = (ani_counter + 1) % 30;
}

void Enemy::ShowScore() {
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _blend);

	if (player.GetConbo() <= 1) {
		DrawString((int)x - (int)15 - (int)map.scl, (int)y, "100", GetColor(255, 255, 255));
	}
	else if (player.GetConbo() == 2)
	{
		DrawString((int)x - (int)15 - (int)map.scl, (int)y, "150", GetColor(255, 255, 255));
	}
	else if (player.GetConbo() == 3)
	{
		DrawString((int)x - (int)15 - (int)map.scl, (int)y, "200", GetColor(255, 255, 255));
	}
	else if (player.GetConbo() == 4)
	{
		DrawString((int)x - (int)15 - (int)map.scl, (int)y, "250", GetColor(255, 255, 255));
	}
	else if (player.GetConbo() >= 5) {
		DrawString((int)x - (int)15 - (int)map.scl, (int)y, "300", GetColor(255, 255, 255));
	}
	else {
	//	DrawString((int)x - (int)15 - (int)map.scl, (int)y, "miss", GetColor(255, 255, 255));
    }


	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

void Enemy::MoveScore() {
	if (y > 0)y -= 2;
	_blend -= 5;
}


//-------------------------------
//エネミー描画
//-------------------------------
void Enemy::Render1() {
	if (scene == GAME || scene == RESULT) {
		if (ani_counter <= 10) {
			map.ScrollDrawGraph(x, y, 1, 0, enemy_image[15], true);
		}
		else if (ani_counter >= 10 && ani_counter <= 20) {
			map.ScrollDrawGraph(x, y, 1, 0, enemy_image[16], true);
		}
		else if (ani_counter >= 20 && ani_counter <= 30) {
			map.ScrollDrawGraph(x, y, 1, 0, enemy_image[17], true);
		}

	}
}
void Enemy::Render2() {
	if (scene == GAME || scene == RESULT) {
		if (ani_counter <= 10) {
			map.ScrollDrawGraph(x, y, 1, 0, enemy_image[12], true);
		}
		else if (ani_counter >= 10 && ani_counter <= 20) {
			map.ScrollDrawGraph(x, y, 1, 0, enemy_image[13], true);
		}
		else if (ani_counter >= 20 && ani_counter <= 30) {
			map.ScrollDrawGraph(x, y, 1, 0, enemy_image[14], true);
		}
	}
}

//-------------------------------
//エネミーとプレイヤーの当たり判定
//-------------------------------
void Enemy::Hit() {
	//if (player.jump == false)
	if (scene == GAME)
	{
		if (player.GetX() + player.W / 2 > x - player.W / 2 &&
			player.GetX() + player.W / 2 < x + player.W / 2 &&
			player.GetY() + (player.H / 2)-10 > y - player.H / 2 &&
			player.GetY() - player.H / 2 < y + player.H / 2) {
			player.is_hit = true;
			map.scroll_couter = 0;
		}

	//	if (player.is_hit == false)
		
		{

			if (player.GetY() + player.H / 2 >= y - player.H / 2 &&
				player.GetY() + player.H / 2 < y + player.H / 2 &&
				player.GetX() + player.W / 2 > x - player.W / 2 &&
				player.GetX() - player.W / 2 < x + player.W / 2

				) {
				player.SetV(6.0f);
				player.AddCombo();
				player.jump = false;
				sound.DeadEnemy();
				is_dead = true;
				score = true;
			}
		}
	}
}

