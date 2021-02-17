#include"Meteorite.h"
#include"Main.h"
#include"player.h"
#include"map.h"
#include"sound.h"
Meteorite::Meteorite() :
	image_w(32),
	image_h(32),
	end_max(300),
	attention_max(60)

{
	x, y = 0;

	speed = 5;
	is_dead = true;
	end_counter = 0;
	meteorite_state = 1;//(0)なら上（1）なら下

	attention_counter = 0;
	attention_state = false;//(true)なら上（false）なら下
	attention_reset = true;
	end_reset = true;
}

Meteorite::~Meteorite() {

}

//画像の読み込み
void Meteorite::Load() {
	meteorite_image = LoadGraph("data/meteorite.png");
	attention_image = LoadGraph("data/attention.png");
}

//画像描画
void Meteorite::Render() {
	map.ScrollDrawGraph(x + map.scl, y, 1, 0, meteorite_image, true);
}

//注意喚起アイコンのステータス変更
void Meteorite::ChangeAttetionState() {
	if (y > 200) attention_state = false;
	else attention_state = true;
}

//メテオが上か下か
void Meteorite::ChangeMeteoriteState(int  state) {
	meteorite_state = state;
}

//隕石が来る少し前に隕石のルートを知らせてくれるアイコンを表示する
void Meteorite::AttentionRender() {

	if (attention_counter != 0) {
		if (attention_counter % 20 != 0
			&& attention_counter % 20 != 1) {

			if (attention_state == true) {
				DrawGraph(600, 170, attention_image, true);
			}
			else if (attention_state == false) {
				DrawGraph(600, 205, attention_image, true);
			}
		}
	}
}


//隕石の場所をセット
void Meteorite::Set() {

	switch (meteorite_state) {
	case 0:
		x = 640;
		y = 170;
		break;

	case 1:
		x = 640;
		y = 220;
		break;
	}
}

//ある一定のlineを超えたら右から隕石 
void Meteorite::Appear(int line) {
	auto p = player.GetX();
	if (player.GetX() > line&&player.GetX() < line + 600) {

		if (player.GetX() > line&&player.GetX() < line + 300) {
			end_reset = false;
		}

		if(end_counter==1)attention_reset = false;
		if (end_counter > 120) {
			Render();
			is_dead = false;
		}
	}
}

//隕石の動き
void Meteorite::Move() {
	if (is_dead == false) {
		x -= speed;
	}
}

//隕石のあたり判定
void Meteorite::Hit() {
	if (is_dead == false) {
		if (player.GetX() + player.W / 2 > x + map.scl &&
			player.GetX() + player.W / 2 < x + map.scl + image_w / 2 &&
			player.GetY() + (player.H / 2) > y&&
			player.GetY() - player.H / 2 < y + image_h) {
			player.is_hit = true;
			map.scroll_couter = 0;
		}
	}
}

//隕石が飛んできてから消えるまでのカウンター増加
void Meteorite::AddEndCounter() {
	if (end_reset == false) {
		if (end_counter <= end_max) {
			end_counter++;

		}
		else if (end_counter > end_max) {
			end_reset = true;
			is_dead = true;
			sound.ResetPan();
		}
	}
}

//隕石の注意喚起用のカウンター増加
void Meteorite::AddAttentionCounter() {
	if (attention_reset == false) {
		if (attention_counter < attention_max) {
			attention_counter++;
			if (attention_counter == 1) {
				sound.Warning();
			}

		}
		else if (attention_counter >= attention_max)
		{
			attention_reset = true;
		}
	}
}

//隕石リセット
void Meteorite::EndReset() {
	if (end_reset == true)
	{
		end_counter = 0;
		
	}
}

//注意喚起リセット
void Meteorite::AttentionReset() {
	if (attention_reset == true)
	{
		attention_counter = 0;
	}
}

//サウンド関係
void Meteorite::SoundMove() {
	if (is_dead == false) {
		//隕石のサウンド移動
		sound.ChengeSoundLeft();
	}
}

