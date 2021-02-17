#pragma once

enum SCENE {
	TITLE,
	INPUT_NAME,
	SELECT,
	CHENGE2,
	GAME,
	RESULT,

	GAMEOVER,

	RANKING,
	SCENE_MAX
};

extern bool a;
extern bool is_easy;

extern SCENE scene;
void GameInit();
void GameExit();
void GameUpdate();
void GameRender();
void ReStart();
extern const int  ENEMY_MAX;
extern const int map_max;
extern int all_coin;
