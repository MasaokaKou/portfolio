#include"MainBase.h"
#include"Game.h"
#include"map.h"
#include"Main.h"
#include"Enemy.h"
#include"player.h"
#include"hit.h"
#include"title.h"
#include"sound.h"
//--------------------------
//"1"==地面ブロック
//"2"==上に乗ったら減速
//"3"==バネ
//--------------------------

//当たり判定
void HitCheck_PlayerVsBlock() {
	
	if (scene == GAME||scene==RESULT) {
		
		//------------------------------------------------------------------------------
			//ブロックNO１
				//右
		if (map.GetMapID((int)player.GetX() + (int)player.W, (int)player.GetY()) == '1' ||
			map.GetMapID((int)player.GetX() + (int)player.W, (int)player.GetY() + (int)player.H / 2) == '1' ) {
			player.SetX(player.old_x);
			//map.scroll_couter = 0;
			player.SetV(0.0f);
		}
		//下
		if (map.GetMapID((int)player.GetX() + (int)player.W/2, (int)player.GetY() + (int)player.H/2) == '1' ||
			map.GetMapID(((int)player.GetX() + (int)player.W), (int)player.GetY() + (int)player.H) == '1') {
			player.jump = false;
			player.is_landing = true;
			sound.Landing();
 			sound.AddLandingCounter();
			player.SetY(player.old_y);
		}
		else if(player.jump==true) {
			sound.ResetLandingCounter();
		}


		//------------------------------------------------------------------------------

		//------------------------------------------------------------------------------
		//ブロックNO２
		//右

		if (map.GetMapID((int)player.GetX() + (int)player.W, (int)player.GetY()) == '2' ||
			map.GetMapID((int)player.GetX() + (int)player.W, (int)player.GetY() + (int)player.H / 2) == '2') {
			player.SetX(player.GetX());
			player.SetV(0.0f);
		}
     	//下
		if(map.GetMapID((int)player.GetX() + (int)player.W / 2, (int)player.GetY() + (int)player.H / 2) == '2' ||
			map.GetMapID(((int)player.GetX() + (int)player.W), (int)player.GetY() + (int)player.H) == '2') {
			
			player.SetY(player.GetY());
			
			//player.SetSpeed(0.0f);
		}
		//------------------------------------------------------------------------------
		//------------------------------------------------------------------------------
		//ブロックNO３
		//下
		if (map.GetMapID((int)player.GetX() + (int)player.W/2, (int)player.GetY() + (int)player.H) == '3' ||
			map.GetMapID(((int)player.GetX() + (int)player.SPACE) + (int)player.W - (int)player.SPACE, (int)player.GetY() + player.H) == '3') {
			map.ChangeMoveBane();
			sound.Bane();
			player.SetV(12.0f);
		}
		//------------------------------------------------------------------------------
		 //ブロックNO４

		


		//------------------------------------------------------------------------------
		
		//常にold更新
		player.old_x = player.GetX();
		player.old_y = player.GetY();
		
	
	}
	
}