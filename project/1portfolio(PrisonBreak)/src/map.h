#pragma once
#include <vector>

class Map {
public:
	Map();
	virtual ~Map();
	bool Load(const char* filePath);
	void PlayerInit();
	void DrawBack();
	void MakeMap1();
	void MoveMap();
	void ChengPlayerImage();
	void ChengPlayerSpeed();
	void BackMove();
	char GetMapID(int x, int y);
	void AddBaneCount();
	void AddAniCount();
	void AddCrystalCount();
	void ScrollDrawGraph(float x, float y, int size, float rota, int handle, bool flag);
	void AnimationBlocks(char block_num,int image_num1, int image_num2, int image_num3);
	void DrawShieldGage();
	void  ChangeMoveBane();
	float GetSpeed();

	void DrawCrystal();
public:
	int scroll_couter;
	const int SCL_COUNT_MAX;
	int scl;
	const int block_size;
	//const char MAP1;
	//ゲームが始まってるかどうか(クリア画面の時に多分使うかも)
	bool play_map1;
	//ゲーム開始時一度だけポジションリセット
	bool check_pos_once;
private:
	std::vector<std::vector<char>> _map;
	//マップを流す用
	int block_image1;
	int back_image;
	int limit_image;
	int bane_image1;
	int bane_image2; 
	
	int crystal_image[3];
	float x;
	float speed;
	float back_x;
	float back_x2;

	const int MAP_H;
	const int MAP_W;
	const int MAP_SIZE;
	
	const int block_w;
	const int block_h;
	int ani_counter;
	int bane_counter;
	int crystal_counter;
	bool move_bane;
	

	
};
extern Map map;
void MapInit();
void MapUpdate();
void MapRender();

