#pragma once

class Sound {
	int door_open;
	int jump1;
	int jump2;
	int speed_up;
	int get_coin;

	int bane;

	int landing;
	bool is_landing;
	int landing_counter;
	int dead_enemy;
	
	int damage;
	
	int end_title;

	int meteorite;
	int sound_move;
	
	int warning;

	int colect_coin;

	int bgm_in_title;
	int bgm_in_select;
	int bgm_in_game;
	int bgm_in_result;

	int go;
	int score;

	int rank;

	int pause[3];



	
public:
	Sound() ;
	~Sound() ;
	void PlayDoor();
	void PlayJump1();
	void PlayJump2();
	void PlaySpeedUp();
	
	void  DeadEnemy();

	void GetCoin();
	
	void Landing();
	void AddLandingCounter();
	void ResetLandingCounter();

	void Damage();

	void Pause1();
	void Pause2();
	void Pause3();

	void EndTitle();

	void Meteorite();
	void SetPan();
	void ResetPan();
	void ChengeSoundLeft();

	void Warning();
	void SetPan2();
		
	void CollectCoin();

	void Bane();
	
	void GO();
	void Score();


	void Rank();

	void PlayBgmTitle();
	void PlayBgmSelect();
	void PlayBgmGame();
	void PlayBgmResult();

	int GetC() { return landing_counter; }
	
	
	void Init();
	
};

extern Sound sound;