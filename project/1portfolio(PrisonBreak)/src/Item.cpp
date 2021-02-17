#include"Item.h"
#include"Main.h"
#include"player.h"
#include"Game.h"
#include"map.h"
#include"hit.h"

Block::Block() {
	_x = 0;
	_y = 0;
	_x2 = 0;
	_y2 = 0;
}

Block::~Block() {

}

void Block::Set(int x,int y,int num) {
	_x = x;
	_y = y;
	_x2 = x+(32*num);
	_y2 = y + 32;


}


void Block::Draw() {
	int x = _x - map.scl;
	int x2 = _x2 - map.scl;
	if (scene == GAME) {

	/*	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		DrawBox(x, _y, x2, _y2, GetColor(255, 2552, 255), true);
		
		for (int i = 0; i < 3; i++) {
			DrawTriangle(x, _y+(10*i), x, _y + (10 * i) + 10 , x - 10, _y + (10 * i) + 5 , GetColor(255, 255, 255), true);
		}
		for (int i = 0; i < 3; i++) {
			DrawTriangle(x+(10 * i), _y2,x+ (10 * i) +10,_y2,x+ (10 * i) +5,_y2+10, GetColor(255, 255, 255),true);

		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);*/
	
	}
}


void Block::Hit(Player*player) {
	if (player->is_hit == false) {

		if (player->GetX() > _x&&player->GetX() < _x2&&
			player->GetY() + 14 > _y&&player->GetY() + 14 < _y2)
		{

			player->SetY(_y - 16);


		}
		if (player->GetX() + 14 > _x&&player->GetX() < _x2&&
			player->GetY() + 14 > _y&&player->GetY() - 14 < _y2)
		{
			player->SetX(player->GetX()-20);
		}
	}

}