#include"main.h"
#include"Game.h"
#include"KEYINPUT.H"
#include"Coin.h"
#include"map.h"
#include"title.h"
#include"player.h"
#include"sound.h"
#define IP 3.14

Coin::Coin() :
	coin_max(3),
	coin_H(22),
	coin_W(22)
{
	coin_x = 0;
	coin_y = 0;

	score = false;

	collect_x = 490.0f;
	collect_y = 270.0f;

	orbit_gravity = -0.5f;
	orbit_alpha = 255;


	is_get = false;
	orbit_counter = 0;
	orbit_check = false;

	p_x;
	p_y;
	t = 0.0f;

	size = 1.8f;
	rota = 0.0f;
	counter_in_result = 0;

	coin_point = 0;
}

Coin::~Coin() {
	DeleteGraph(coin_image);
}

//コイン&&軌道画像読み込み
void Coin::Load() {
	coin_image = LoadGraph("data/coin.png");
	orbit_image= LoadGraph("data/orbit.png");

}

//コインの場所指定

void Coin::SetCoin(int x, int y) {
	coin_x = x;
	coin_y = y;
}

//コインの軌道設定
void Coin::SetOrbit() {
	orbit_x = (float)coin_x;
	orbit_y = (float)coin_y;
}

//コインの軌道設定2
void Coin::SetOrbit2() {
	p0_x = (int)orbit_x;
	p0_y = (int)orbit_y;
}

//コインの軌道設定3
void Coin::SetOrbit3(int i) {
	p2_x = (float)collect_x+ (float)(60*i);
	p2_y = (float)collect_y;
	p1_x = (float)player.wall_x + 100.0f;
	p1_y = -100;
}

//コイン描画
void Coin::DrawCoin() {
	if (scene == GAME || scene == GAMEOVER) {
		if (is_get == false) {
			map.ScrollDrawGraph((float)coin_x, (float)coin_y, 1, 0.0f, coin_image, true);
		}
	}
}

//コインの軌道描画
void Coin::DrawOrbit() {
	if (is_get == true) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, orbit_alpha);
		DrawRotaGraph((float)orbit_x - (float)map.scl, orbit_y, 1,0.0f,orbit_image, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

//コインのムーヴメントカウント増加
void Coin::AddOrbitCount() {
	if (is_get == true) {
		if(orbit_counter<=300)
		orbit_counter++;

		orbit_alpha -= 4  ;
	}
	if (is_get == false) {
		orbit_counter = 0;
		orbit_alpha = 255;
    }

}


//コインの枚数カウント
void Coin::AddCoinPoint() {
	if(orbit_counter==1)coin_point++;
}

//集めたコイン描画(枠)
void Coin::DrawCollect() {
	if (scene == GAME || scene == RESULT || scene == GAMEOVER) {
		DrawBox(0, 270, 640, 320, GetColor(0, 0, 0), true);
		//DrawLineBox(490, 270, 640, 320, GetColor(200, 0, 40));
		DrawLineBox((int)collect_x - (int)map.scl, (int)collect_y, (int)collect_x + 150, (int)collect_y + 50, GetColor(200, 0, 40));
		for (int i = 0; i < 3; i++) {
			DrawCircle(515 + (50 * i), 295, 25, GetColor(255, 255, 0), false);
		}
	}
}

//リセット時
void Coin::SetCollectBox() {
	collect_x = 490.0f;
	collect_y = 270.0f;

}

//枠移動
void Coin::ChengeCollectSpeed() {
	int s;
	if (scene == GAME) {
		s = (int)map.GetSpeed();
		collect_x += s;
	}
}

//集めたコイン描画
void Coin::DrawCollected(int i) {
	if (scene == GAME) {
		if (orbit_counter > 40) {
			if (coin_point >= 1) {
				DrawRotaGraph(516 + (50 * i), 295, 1.16, 0, coin_image, true);
			}
		}
	}
}

//リザルト画面で集めたコインの動き用カウンター
void Coin::AddMoveCounterInResult() {
	if (scene == RESULT) {
		counter_in_result++;
	}
}


//リザルト画面で集めたコイン描画
void Coin::DrawInResult(int i) {
	if (scene == RESULT) {

		if (coin_point >= 1) {
			DrawRotaGraph(50 + (80 * i), 150, size, rota, coin_image, true);
		}
	}
}

//リザルト画面で集めたコインの動き
void Coin::MoveInResult() {
	
	if (counter_in_result > 100) {
	
		size -= 0.01f;
		rota += 0.1f;
		if (size< 1.15f) {
			rota = 0.0f;
			size = 1.15f;
		}
	}
	

}



//集めたコインリセット
void Coin::ResetPoint() {
	coin_point = 0;
}


//当たり判定
void Coin::GettedCoin() {
	//if (IsKeyOn(KEY_INPUT_C)) {}
	if (player.GetX() + player.W / 2 > coin_x - coin_W - 1 / 2 &&
		player.GetX() - player.W / 2 < coin_x + coin_W / 2 &&
		player.GetY() + player.H / 2 > coin_y - coin_H / 2 &&
		player.GetY() - player.H / 2 < coin_y + coin_H / 2) {
		is_get = true;
		orbit_check = true;
		AddCoinPoint();
	}
}

bool Coin::GetScore() {
	return score;
}

void Coin::SetScore(bool sc) {
	score = sc;
}

void Coin::ChengeScore() {
	if (orbit_counter == 1) {
		score = true;
		//コイン取得時のSE
		sound.GetCoin();
	}
	
	
	
}

//当たり判定（結果)
//void Coin::CoinMove() {
//	if (is_get == true) {
//		if (orbit_counter > 0 && orbit_counter < 30) {
//			orbit_y -= sinf(-10+orbit_counter  * IP / 180) * 5;
//		}
//		else if (orbit_counter >= 30) {
//			orbit_x += cosf(320  * IP / 180) * 4.5f;
//			orbit_y += sinf(150+orbit_counter * IP / 180) * 2;
//		}
//	}
//}

//ベジェ曲線（コインの動き）
void Coin::CoinMove() {
	if (is_get == true) {
		if (orbit_check == true) {
			t += 0.02f;
			orbit_x = ((1 - t)*(1 - t) *p0_x + 2 * (1 - t)*t*p1_x + t * t*p2_x);
			orbit_y = ((1 - t)*(1 - t) *p0_y + 2 * (1 - t)*t*p1_y + t * t*p2_y);
			if (t > 1.0f) {
				t = 0.0f;
				//orbit_counter = 0;
				orbit_check = false;
			}
		}
	}
}


//集計用のポイント増加
void Coin::SumPoint() {
	if (coin_point > 0) {
		sum_point = 1;
	}
}

//リザルト画面のコインのSE
void Coin::SeInResult(int i) {
	if (coin_point == 1) {
		if (counter_in_result == 620 + (100 * i))
			sound.CollectCoin();
	}
}
