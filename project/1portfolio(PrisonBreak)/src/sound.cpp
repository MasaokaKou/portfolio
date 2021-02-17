#include"Main.h"
#include"Game.h"
#include"player.h"
#include"sound.h"
#include"Keyinput.h"
#include"title.h"
Sound sound;
//音源読み込み用
Sound::Sound() {
	is_landing = false;
	landing_counter = 0;
	sound_move =4000;
	
}
Sound::~Sound() {
	DeleteSoundMem(door_open);
	DeleteSoundMem(jump1);
	DeleteSoundMem(speed_up);
	DeleteSoundMem(get_coin);
	DeleteSoundMem(landing);
	DeleteSoundMem(dead_enemy);
	DeleteSoundMem(damage);
	DeleteSoundMem(pause[0]);
	DeleteSoundMem(pause[1]);
	DeleteSoundMem(end_title);
	DeleteSoundMem(bgm_in_select);
	DeleteSoundMem(bgm_in_select);


}

void Sound::Init() {
	
	bgm_in_select = LoadSoundMem("data/sound/SION_BGM.MP3");
	
	door_open = LoadSoundMem("data/sound/door_open1.mp3");
	jump1 = LoadSoundMem("data/sound/jump01.mp3");
	jump2 = LoadSoundMem("data/sound/jump02.mp3");
	speed_up = LoadSoundMem("data/sound/speed-up1.mp3");
	get_coin = LoadSoundMem("data/sound/coin08.mp3");
	landing = LoadSoundMem("data/sound/landing1.mp3");
	dead_enemy = LoadSoundMem("data/sound/dead,enemy.mp3");
	damage = LoadSoundMem("data/sound/damage.mp3");
	pause[0] = LoadSoundMem("data/sound/pause1.mp3");
	pause[1] = LoadSoundMem("data/sound/pause2.mp3");
	pause[2] = LoadSoundMem("data/sound/pause3.mp3");
	end_title = LoadSoundMem("data/sound/end_title.mp3");
	meteorite= LoadSoundMem("data/sound/meteorite.mp3");
	warning= LoadSoundMem("data/sound/warning.mp3");
	colect_coin= LoadSoundMem("data/sound/check_coin2.mp3");
	bane= LoadSoundMem("data/sound/OCLL8607.MOV");
	go= LoadSoundMem("data/sound/GAM001.wav");
	score= LoadSoundMem("data/sound/MIM003.wav");
	rank= LoadSoundMem("data/sound/LIF010.wav");

	ChangeVolumeSoundMem(200, speed_up);


	
	


}

//ドアに入るときのSE
void Sound::PlayDoor() {
	PlaySoundMem(door_open, DX_PLAYTYPE_BACK);	
}

//ジャンプするときのSE
void Sound::PlayJump1() {
	PlaySoundMem(jump1, DX_PLAYTYPE_BACK);
}

//スピードアップ時のSE
void Sound::PlaySpeedUp() {
	PlaySoundMem(speed_up, DX_PLAYTYPE_BACK);
}

//コインを取った時のSE
void Sound::GetCoin() {
	PlaySoundMem(get_coin, DX_PLAYTYPE_BACK);
}

//着地音
void Sound::Landing() {
	if (landing_counter == 1) {
		PlaySoundMem(landing, DX_PLAYTYPE_BACK);
	}
}

void Sound::AddLandingCounter() {
	landing_counter++;
	if (landing_counter > 30) {
		landing_counter = 3;
	}
}

void Sound::ResetLandingCounter() {
	landing_counter = 0;
}

//敵消滅時のSE
void Sound::DeadEnemy() {
	PlaySoundMem(dead_enemy, DX_PLAYTYPE_BACK);
}

//プレイヤーがダメージを受けた時のSE
void Sound::Damage() {
	PlaySoundMem(damage, DX_PLAYTYPE_BACK);
}

//ポーズ画面
void Sound::Pause1() {
	if (scene == GAME) {
		PlaySoundMem(pause[0], DX_PLAYTYPE_BACK);
	}
}

void Sound::Pause2() {
	if (scene == GAME) {
		PlaySoundMem(pause[1], DX_PLAYTYPE_BACK);
	}
}

//タイトル画面切り替え
void Sound::EndTitle() {
	PlaySoundMem(end_title, DX_PLAYTYPE_BACK);
}

//隕石
void Sound::Meteorite() {
	if (scene == GAME) {
		PlaySoundMem(meteorite, DX_PLAYTYPE_BACK);
	}
}

void Sound::SetPan() {
	SetPanSoundMem(sound_move, meteorite);
}

void Sound::ResetPan() {
	sound_move = 4000;

}

void Sound::ChengeSoundLeft() {
		sound_move -= 50;
}

void Sound::Warning() {
	PlaySoundMem(warning, DX_PLAYTYPE_BACK);
}

void Sound::SetPan2() {
	SetPanSoundMem(4000, warning);
}


//ポーズ画面
void Sound::Pause3() {
	PlaySoundMem(pause[2], DX_PLAYTYPE_BACK);
}

//リザルト画面のコイン
void Sound::CollectCoin() {
	PlaySoundMem(colect_coin, DX_PLAYTYPE_BACK);
}


void Sound::Bane() {
	PlaySoundMem(bane, DX_PLAYTYPE_BACK);
}


void Sound::PlayBgmSelect() {
	//PlaySoundFile("data/sound/SION_BGM.MP3", DX_PLAYTYPE_LOOP);

	PlayMusic("data/sound/L41.wav", DX_PLAYTYPE_LOOP);
	SetVolumeMusic(100);
}

void Sound::PlayBgmGame() {
	PlayMusic("data/sound/MAIN_BGM.MP3", DX_PLAYTYPE_LOOP);
	SetVolumeMusic(150);

}

void Sound::GO() {
	PlaySoundMem(go, DX_PLAYTYPE_BACK);
}


void Sound::Rank() {
	PlaySoundMem(rank, DX_PLAYTYPE_BACK);
}