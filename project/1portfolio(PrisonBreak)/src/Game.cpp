#include"MainBase.h"
#include"SetEnemy.h"
#include"Game.h"
#include "Keyinput.h"
#include"Pause.h"
#include"player.h"
#include"title.h"
#include"sound.h"
#include"map.h"
#include"hit.h"
#include"Enemy.h"
#include"Meteorite.h"
#include"Coin.h"
#include"Mapline.h"
#include"Score.h"
#include"Result.h"
#include"Effect.h"
#include"chenge2.h"
#include"Ranking.h"
#include"Gameover.h"
#include"Item.h"

SCENE scene;
const int  ENEMY1_MAX = 26;
const int  ENEMY2_MAX = 29 ;
const int METEORITE_MAX = 6;
const int map_max = 5550;//5550;
const int block_max = 6;
MainBase mainbase;
Enemy enemy1[ENEMY1_MAX];
Enemy enemy2[ENEMY2_MAX];
Map map;
Meteorite meteorite[METEORITE_MAX];
Pause pause;Coin coin[3];
Mapline mapline;
Score score;
Result result;
Effect effect;
Chenge2 chenge2;
Ranking ranking;
InputName name;
GameOver over;
Block block[block_max];

int all_coin = 0;

int skip = 5000;

int select_counter = 0;
int game_counter = 0;

bool ranking_flag=false;

bool is_easy=true;


#if _DEBUG
bool a=false;
#endif	


void DebugInit() {
	//skip OP^---------------------------------------------------------skip OP
	{
#if _DEBUG

	//	scene = GAME;
		//scene = SELECT;
		//scene = RESULT;
	    //scene = INPUT_NAME;
		//scene = GAMEOVER;
		//scene = RANKING;

		is_easy = false;
#endif	
	}
	//------------------------------------------------------------------------
	//scene = RESULT;
	scene = INPUT_NAME;
}

void DebugUpdate() {
#if _DEBUG
	//�X�L�b�v�f�o�b�N
#if 1
	if (player.GetX() < skip) {
		player.wall_x += 7;
		player.wall0_x += 7;
		map.scl += 7;


	}
#endif
	if (scene == GAME) {
		if (CheckHitKey(KEY_INPUT_RIGHT)) {
			//map.scl += 7;


		}if (CheckHitKey(KEY_INPUT_LEFT)) {
			//map.scl -= 7;

		}
		if (CheckHitKey(KEY_INPUT_S))player.DebugMove();
		if (CheckHitKey(KEY_INPUT_A))player.DebugMove2();
		if (IsKeyOn(KEY_INPUT_Q))player.is_hit = true;

}

#endif	
}

//�G�l�~�[�̔z�u
void SetEnemy() {

	int* enemy1X = Get1X();
	int* enemy2X = Get2X();
	int* enemy2Y = Get2Y();

	for (int i = 0; i < ENEMY1_MAX; i++) {
		enemy1[i].SetX((float)enemy1X[i]);
	}
	for (int i = 0; i < ENEMY1_MAX; i++) {
        enemy1[i].SetY(224.0f);
		enemy1[18].SetY(128.5f);
		enemy1[19].SetY(128.5f);
		enemy1[20].SetY(128.5f);
		enemy1[21].SetY(128.5f);
		enemy1[22].SetY(128.5f);
	}
	for (int i = 0; i < ENEMY2_MAX; i++) {
		enemy2[i].SetX((float)enemy2X[i]);
	}
	for (int i = 0; i < ENEMY2_MAX; i++) {
		enemy2[i].SetY((float)enemy2Y[i]);
	}

}

//覐΂̔z�u
void SetMeteorite() {
	//覐΂��ォ����
	int meteo[] = {
		1,1,1,1,0,1,
	};

	for (int i = 0; i < METEORITE_MAX; i++) {
		meteorite[i].Load();
		meteorite[i].ChangeMeteoriteState(meteo[i]);
		meteorite[i].Set();
		meteorite[i].SetIsDead();




	}

}

void DrawMeteo() {
	//覐΂̃X�^�[�g�n�_
	int meteo[] = {
		500,1500,2700,4600,4650,4700,

	};

	for (int i = 0; i < METEORITE_MAX; i++) {
		if (meteorite[i].GetIsDead() == false&& meteorite[i].GetCounter()>120) {
			effect.DrawSmoke(meteorite[i].GetX(), meteorite[i].GetY());
		}

	}

	for (int i = 0; i < METEORITE_MAX; i++) {
		meteorite[i].AttentionRender();
		meteorite[i].Appear(meteo[i]);
	}

}

void SetBlock() {
	//for (int i = 0; i < block_max; i++) 
	{
		block[0].Set(1700, 80, 7);
		block[1].Set(1934, 112, 1);
		block[2].Set(1966, 144, 1);
		block[3].Set(3185, 145, 11);
		block[4].Set(4460, 80, 2);
		block[5].Set(4460, 112, 1);

	}
}


//�Q�[���̏�����
void ReStart() {
	map.scl = 0;
	title.start_counter = 0;
	map.check_pos_once = true;
	player.wall_x = 100;
	SetMeteorite();
	name.SetInputFlag();
	if (is_easy == false) {
		player._hitpoint = 3;
	}
}

void GameInit() {

	DebugInit();


	name.Init();

	TitleInit();

	map.Load("data/Map1.csv");

	PlayerInit();

	sound.Init();

	KeyInputInit();

	pause.Load();

	result.Load();

	effect.ImageLoad();

	chenge2.SetCirclePos();
	chenge2.SetFlag();
	
	ranking.Load();

	over.Load();

	//-----------------------------------------------------
	for (int i = 0; i < ENEMY1_MAX; i++) {
		enemy1[i].Load();
	}

	for (int i = 0; i < ENEMY2_MAX; i++) {
		enemy2[i].Load();
	}


	SetEnemy();

	SetMeteorite();



	//---------------------------------------------------

	for (int i = 0; i < 3; i++) {
		coin[i].Load();
		//------------------------------------
			//�R�C���ʒu�ݒ�
		coin[0].SetCoin(1900, 50);
		coin[1].SetCoin(3400, 210);
		coin[2].SetCoin(4500, 50);
		coin[i].SetOrbit();
		coin[i].SetOrbit2();
	}

	mapline.SetLinePos();
	mapline.Load();

	SetBlock();

}

void GameExit() {
	TitleExit();
	KeyInputExit();
	name.Exit();
}

void GameUpdate() {

	if (title.start_counter == 305)sound.GO();
	
	DebugUpdate();
	if (is_easy == false) {
		if (scene == GAMEOVER) {
			over.Update();
		}
	}
	player.DecHitPoint();



	//�V�[���؂�ւ�
	//�W���C�p�b�h
	if (GetJoypadInputState(DX_INPUT_PAD1) & (PAD_INPUT_2)) {

		if ((player._before_BIT & PAD_INPUT_2) == false) {
			if (scene == RANKING){
				scene = INPUT_NAME;
			}

		}
	}
	
	if (GetJoypadNum() == 0) {

		if (scene == RANKING && IsKeyOn(KEY_INPUT_R)) {
			scene = INPUT_NAME;
		}
	}



	//BGM
	if (select_counter == 1)sound.PlayBgmSelect();
	if (game_counter == 1)sound.PlayBgmGame();


	//�V�[�����̃J�E���^�[
	if (scene == SELECT && select_counter < 10)select_counter++;
	if (scene != SELECT)select_counter = 0;

	if (scene == GAME && game_counter < 70)game_counter++;
	if (scene != GAME)game_counter = 0;

	//if(IsKeyOn(KEY_INPUT_Q))player.is_hit = true;
	pause.ChengePause();
	pause.AddScrollCount();
	pause.MoveCursor();
	pause.SelectPause();

	score.AddTime();
	map.AddCrystalCount();




	//�X�R�A����
	//if (scene == GAME) 
	{
		if (pause.GetPause() == false) {

			if (title.start_counter > 360) {
				score.AddCount();
				score.Add();
			}
		}
		//�G�l�~�[�̃X�R�A�t���O���Z�b�g
		for (int i = 0; i < ENEMY1_MAX; i++) {
			enemy1[i].score = false;
		}
		for (int i = 0; i < ENEMY2_MAX; i++) {
			enemy2[i].score = false;
		}

		//�R�C���̃X�R�A�t���O���Z�b�g
		for (int i = 0; i < 3; i++) {
			coin[i].SetScore(false);
			coin[i].ChengeScore();
		}
		//-----------------------------------------------------------debug(�}�b�v�ȗ�)
		for (int i = 0; i < 10; i++)
		{
			//enemy1[i].is_dead = true;
		}

		for (int i = 0; i < 10; i++)
		{
			//enemy2[i].is_dead = true;
		}
		//----------------------------------------------------------------------------
		//-----------------------------------------------------------
		//�|�[�Y��ʂɂ�������G�l�~�[�������R�C�����X�R�A���Z�b�g
		//-----------------------------------------------------------

		if (map.check_pos_once == true || scene == SELECT) {

			for (int i = 0; i < ENEMY1_MAX; i++) {
				enemy1[i].is_dead = false;
				enemy1[i].ResetAlpha();
			}
			for (int i = 0; i < ENEMY2_MAX; i++) {
				enemy2[i].is_dead = false;
				enemy2[i].ResetAlpha();
			}
			SetEnemy();

			for (int i = 0; i < 3; i++) {
				coin[i].is_get = false;
				coin[i].ResetPoint();
				coin[i].SetCollectBox();
				coin[i].ResetAlpha();
				coin[i].ResetInResult();
				coin[i].ResetSum();
			}

			score.Reset();
			all_coin = 0;
			map.scl = 0;
			map.check_pos_once = true;
			player.wall_x = 100;
			player.ani_count_max = 30;
			if (select_counter == 1)check2Pos = true;
			SetMeteorite();
			title.start_counter = 0;
			ranking.Exit();


		}

		if (scene == SELECT) {
			chenge2.SetFlag();
		}

		//-----------------------------------------------------------
		//map.MoveMap();
		//�|�[�Y���ɒ�~�������

		if (pause.GetPause() == false) {
			
			if (title.start_counter > 310) {
#if 0
				if (player.GetX() < skip)
#endif
				{
					map.AddBaneCount();
					map.ChengPlayerSpeed();

					player.SetWall();
					player.AddWallX();
					player.LimitWall();
				}

				//�G�l�~�[�������蔻��ƃA�j���[�V����

				for (int i = 0; i < ENEMY1_MAX; i++) {
					if (enemy1[i].is_dead == false) {
						enemy1[i].Update();
						enemy1[i].Hit();
					}
				}
				for (int i = 0; i < ENEMY2_MAX; i++) {
					if (enemy2[i].is_dead == false) {
						enemy2[i].Update();
						enemy2[i].Hit();
					}
				}
				if (player.GetX() < map_max - 200) {
					map.MoveMap();
					map.BackMove();
				}
			}


			if (game_counter > 50)
				title.AddStartCounter();

			map.PlayerInit();

			TitleUpdate();

			PlayerUpdate();

			player.Jump();

			//player._before_A = false;
			//if ((GetJoypadInputState(DX_INPUT_PAD1) & (PAD_INPUT_1))) {
			//	player._before_A = true;
			//}
			



			if (scene == GAME) {
				//覐Ώ���
				for (int i = 0; i < METEORITE_MAX; i++) {

					meteorite[i].Move();
					meteorite[i].Hit();
					meteorite[i].AddEndCounter();
					meteorite[i].AddAttentionCounter();
					meteorite[i].ChangeAttetionState();
					meteorite[i].AttentionReset();
					meteorite[i].EndReset();
				}
			}
			//�R�C�����O��
			for (int i = 0; i < 3; i++) {
				coin[i].GettedCoin();
				coin[i].SetOrbit3(i);
				coin[i].AddOrbitCount();
				coin[i].CoinMove();
				coin[i].AddMoveCounterInResult();

				if (title.start_counter > 310) {
					coin[i].ChengeCollectSpeed();
				}
			}
		

	    }

		//�G��|������X�R�A����
		for (int i = 0; i < ENEMY1_MAX; i++) {
			if (enemy1[i].score == true)
				score.AddEnemyScore();

		}
		for (int i = 0; i < ENEMY2_MAX; i++) {
			if (enemy2[i].score == true)
				score.AddEnemyScore();

		}

		//�R�C�����������X�R�A����
		for (int i = 0; i < 3; i++) {
			if (coin[i].GetScore() == true) {
				score.AddCoinScore();
			}
		}
		mapline.SetPlayerCirclePos();
		mapline.CheckHalfPoint();
		mapline.SelectColor();

		//���U���g��ʂł̃R�C���̓���
		if (coin[0].GetResultCounter() > 550 && coin[0].GetResultCounter() < 650) {
			coin[0].MoveInResult();
		}
		else if (coin[0].GetResultCounter() > 650 && coin[0].GetResultCounter() < 750) {
			coin[1].MoveInResult();
		}
		else if (coin[0].GetResultCounter() > 750) {
			coin[2].MoveInResult();
		}


		//�W�v�p�̃|�C���g
		for (int i = 0; i < 3; i++) {
			coin[i].SumPoint();
		}
		all_coin = coin[0].GetSum() + coin[1].GetSum() + coin[2].GetSum();

		HitCheck_PlayerVsBlock();
		KeyInputUpdate();
	}

	switch (scene) {
		//---------------------------------------------------------
	case GAME: // �Q�[��
	//---------------------------------------------------------
	{
		
		// �v���C���[���K��̈ʒu�ɒB���Ă��邩
		if (player.GetX() > map_max) {
			// ���U���g��ʂɈړ�
			scene = RESULT;
		}
	}
	break;
	//---------------------------------------------------------
	case RESULT: // ���U���g
	//---------------------------------------------------------
	{
		//score.SetScore(13360);
		name.SetInputFlag();
		result.Update();
		SetMeteorite();
		player._hitpoint = 3;

		// �X�R�A�A�j���[�V�����J�n
		if (result.IsFinishAnimation()) {
			score.GiveData1();
		}
	}
	break;
	}

	//-----------------------------------------------------------------
	//�G�t�F�N�g�ienemy�j
	//-----------------------------------------------------------------


	if (map.scroll_couter > 100 && map.scroll_couter < 150) {
		effect.AddLineAlpha();
	}
	else if (map.scroll_couter > 300 && map.scroll_couter < 350) {
		effect.AddLineAlpha();
	}


	effect.ChengePearlAlpha();
	effect.ResetPearlAlpha();

	//------------------------------------------------------
	//覐�
	//------------------------------------------------------
	

	//effect.LandingMove();
	for (int i = 0; i < METEORITE_MAX; i++) {
		if (meteorite[i].GetIsDead() == false) {
			effect.SmokeMove();
		}
	}


	//�G��|������̃X�R�A�̃A�j���[�V����
	for (int i = 0; i < ENEMY1_MAX; i++) {
		if (enemy1[i].is_dead == true) {
			enemy1[i].MoveScore();
		}
	}
	for (int i = 0; i < ENEMY2_MAX; i++) {

		if (enemy2[i].is_dead == true) {
			enemy2[i].MoveScore();
		}

	}

	//�X�s�[�h�A�b�v���̌��ʉ�
	if (map.scroll_couter == 100)sound.PlaySpeedUp();
	if (map.scroll_couter == 300)sound.PlaySpeedUp();

	//�_���[�W���ʉ�
	if (player.hit_counter == 1) {
		sound.Damage();
	}

	sound.SetPan();
	sound.SetPan2();



	//覐΂̌��ʉ�
	for (int i = 0; i < METEORITE_MAX; i++)
	{
		meteorite[i].SoundMove();

		if (meteorite[i].GetCounter() == 120) {
			sound.Meteorite();
		}
	}

	//�|�[�Y���SE
	pause.ScrollSound();

	for (int i = 0; i < 3; i++) {
		coin[i].SeInResult(i);
	}


	result.EndGame();
	result.ReSetGame();
	score.ResetData();
	chenge2.MoveCircle();
	chenge2.ChengeScene();

	


	if (scene == RANKING) {
		

		if (!ranking.IsInitialized()) {
			ranking.Connect(&score);
			ranking.Init();
			ranking.Update(&score);
			ranking.Save();
		
			name.Exit();
		}
		
	}	
	
	if (scene == RANKING) {
		SetBackgroundColor(5000,5000,5000);
	}
	else {
		SetBackgroundColor(0, 0, 0);

	}
	

	for (int i = 0; i < block_max; i++) 
	block[i].Hit(&player);

	
	if (scene == INPUT_NAME) {
		name.Update();
		name.Anim();
		name.UpdateInput();

		{
			ranking.SetOutputFlag();
		

			if (name.GetAni() < -600) {
				name.SetInputFlag();
				scene = SELECT;
			}
		}
	}

	player._before_BIT = GetJoypadInputState(DX_INPUT_PAD1);
}

void GameRender() {

	TitleRender();
	map.DrawBack();
	map.MakeMap1();
	player.Hit_Render();

	for (int i = 0; i < 3; i++) {
		coin[i].DrawOrbit();
		coin[i].DrawCoin();
	}

	//-----------------------------------------------------------------
	//�G�t�F�N�g�i�v���C���[�j
	//-----------------------------------------------------------------

	//�X�s�[�h�A�b�v
	if (map.scroll_couter > 100 && map.scroll_couter < 150)
	{
		float p_x = player.GetX() - map.scl;
		float p_y = player.GetY();
		for (int i = 0; i < 4; i++) {
			effect.PlayerSpeedUp(p_x + 10, p_y + 5 + (3 * i), p_x - 15, p_y + 5 + (3 * i));
		}

	}
	else if (map.scroll_couter > 300 && map.scroll_couter < 350)
	{
		float p_x = player.GetX() - map.scl;
		float p_y = player.GetY();
		for (int i = 0; i < 4; i++) {
			effect.PlayerSpeedUp(p_x + 10, p_y + 5 + (3 * i), p_x - 20, p_y + 5 + (3 * i));
		}
	}

	//�S�[���`��
	map.DrawCrystal();

	map.ChengPlayerImage();

	//�G�l�~�[&&�X�R�A�`��
	for (int i = 0; i < ENEMY1_MAX; i++) {
		if (enemy1[i].is_dead == false) {
			enemy1[i].Render1();
		}
		else if (enemy1[i].is_dead == true) {
			enemy1[i].ShowScore();
		}
	}
	for (int i = 0; i < ENEMY2_MAX; i++) {
		if (enemy2[i].is_dead == false) {
			enemy2[i].Render2();
		}
		else if (enemy2[i].is_dead == true) {
			enemy2[i].ShowScore();
		}

	}
	
	if (scene == GAME) {
		DrawMeteo();
	}
	for (int i = 0; i < 3; i++) {
		coin[i].DrawCollect();
	}
	for (int i = 0; i < 3; i++) {
		coin[i].DrawCollected(i);
	}

	mapline.DrawMapLine();
	mapline.DrawPlayerCircle();
	mapline.DrawFlag();

	score.Show();

	title.StartCountDown();
	pause.DrawScroll();
	pause.DrawCursor();

	PlayerRender();

	
	//---- ���U���g�`��
	if (scene == RESULT) {
		result.PreDraw();

		if (result.IsShowScore()) {
			score.ShowResult();
		}

		result.PostDraw();
	}

	//���U���g��ʂł̃R�C���̕`��
	if (coin[0].GetResultCounter() > 550) {
		coin[0].DrawInResult(0);
	}
	if (coin[0].GetResultCounter() > 650) {
		coin[1].DrawInResult(1);
	}
	if (coin[0].GetResultCounter() > 750) {
		coin[2].DrawInResult(2);
	}

	result.ShowRank(&score);

	chenge2.CircleRender();

	for (int i = 0; i < block_max; i++) 
	block[i].Draw();





	//�����L���O���
	if (scene == RANKING) {
		ranking.DrawName(&score);
		ranking.Draw(&score);
		ranking.DrawImage();
	
	}
	if (scene == RANKING)
	ranking.DrawImage();

	//���O���͉��
	if (scene == INPUT_NAME) {
		name.Draw();
	}
	if (is_easy == false) {
		if (scene == GAMEOVER) {
			over.Draw();
		}
	}
	//-----------------------------------------------------------------
	//�G�t�F�N�g�i�v���C���[�j
	//-----------------------------------------------------------------



		 //���n
	effect.DrawPearl();

	

#if _DEBUG
	if (scene == INPUT_NAME) {
		DrawString(600, 44, "INPUT", GetColor(255, 255, 255));
	}if (scene == SELECT) {
		DrawString(600, 44, "SELECT", GetColor(255, 255, 255));
	}if (scene == GAME) {
		DrawString(600, 44, "GAME", GetColor(255, 255, 255));
	}if (scene == RESULT) {
		DrawString(600, 44, "RESULT", GetColor(255, 255, 255));
	}
	if (scene == RANKING) {
		DrawString(600, 44, "RANKING", GetColor(255, 255, 255));
	}
	
	
	
	//���W�`��
	char text[256];
	sprintf_s(text, "%d",meteorite[0].GetC());
	DrawString(580, 2, text, GetColor(255, 255, 255));
	char text2[256];
	sprintf_s(text2, "%d", meteorite[0].GetCounter());
	DrawString(600, 16, text2, GetColor(255, 255, 255));
	
	if(a==true)DrawString(600, 30, "TRUE", GetColor(255, 255, 255));
	if (a == false)DrawString(16, 30, "TRUE", GetColor(255, 255, 255));
#endif
}





