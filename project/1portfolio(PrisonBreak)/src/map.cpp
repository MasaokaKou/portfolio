#include"MainBase.h"
#include"Enemy.h"
#include"Game.h"
#include"Main.h"
#include"player.h"
#include"map.h"
#include"title.h"
#include"Keyinput.h"

#include <string>
#include <sstream>
#include <fstream>


//テキスト分割（vector 動的配列作ってるだけ）-----------------------------------
void StringSplit(const std::string &str, char sep, std::vector<char>& out)
{
	//配列（vector）
	out.clear();
	//ssにstrを代入
	std::stringstream ss(str);
	//一時的に保存する場所？
	std::string buffer;
	//行単位で管理(読み込み)
	while (std::getline(ss, buffer, sep)) {
		if (buffer.empty()) continue;

		out.push_back(buffer[0]);

		/*int  value = std::atoi( buffer.c_str() );
		char c     = static_cast<char>( value & 0xff );
		out.push_back( c );*/

	}
}

//------------------------------------------------------------------------------

Map::Map()
	: MAP_W(250)
	, MAP_H(12)
	, block_size(32)
	, MAP_SIZE(32)
	, block_h(32)
	, block_w(32)
	, SCL_COUNT_MAX(1500)
{
	scl = 0;
	scroll_couter = 0;
	speed = 1;
	check_pos_once = true;
	play_map1 = false;
	back_x = 0;
	back_x2 = 640;
	bane_counter = 0;
	move_bane = false;
	crystal_counter = 0;
}

Map::~Map()
{


}
//---------------------------------
//画像の読み込み
//---------------------------------
bool Map::Load(const char* filePath) {

	//マップファイル読み込み
	std::ifstream ifs(filePath);
	if (ifs.fail()) {
		return false;
	}

	std::string str;
	while (std::getline(ifs, str))
	{
		//文字列に入ってなかったら
		if (str.empty()) continue;
		//二次元配列ののりで（配列を追加）
		_map.push_back(std::vector<char>());
		//cellsにマップ一行分のデータを入れてる
		auto& cells = _map[_map.size() - 1];
		//分割したデータを登録
		StringSplit(str, ',', cells);

	}
	ifs.close();

	// 画像読み込み
	block_image1 = LoadGraph("data/blocks/stone.png");
	back_image = LoadGraph("data/picture/prison_back_image.png");
	limit_image = LoadGraph("data/blocks/limit.png");
	bane_image1 = LoadGraph("data/blocks/bane1.png");
	bane_image2 = LoadGraph("data/blocks/bane2.png");
	LoadDivGraph("data/blocks/!CRYSTAL.PNG",3,3,1,32,60,crystal_image,true);
	//char aa = _map[0][0];

	return true;
}
//------------------------------------
//ゲームスタート時の初期化
//------------------------------------
void Map::PlayerInit() {

	if (scene == GAME) {
		if (check_pos_once == true) {
			player.SetPlayerPos(100, 180);
			player.SetV(0.0f);
			player.SetSpeed(0.0f);
			scroll_couter = 0;
			check_pos_once = false;
			
		}
		player.SetDir(1);
	}
}
//-------------------------------
//背景描画
//-------------------------------
void Map::DrawBack() {
	if (scene == GAME||scene==RESULT||scene==GAMEOVER) {
		
		DrawGraph(back_x, 0, back_image, false);
		DrawGraph(back_x2, 0, back_image, false);
	}
}
void Map::BackMove() {
	if (scene == GAME) {
		back_x -= 0.3;
		back_x2 -= 0.3;
		if (back_x + 640 <= 0) {
			back_x = back_x2 + 640;
		}
		if (back_x2 + 640 <= 0) {
			back_x2 = back_x + 640;
		}
	}
}
//-------------------------------
//ばねカウンター増加
//-------------------------------
void Map::AddBaneCount() {
	if (move_bane == true) {
		if (bane_counter <= 15) {
			bane_counter++;
		}
		else {
			bane_counter = 0;
			move_bane = false;
		}
	}
}
void Map::ChangeMoveBane() {
	move_bane = true;
}

//-------------------------------
//アニメーションカウンター増加
//-------------------------------
void Map::AddAniCount() {
	if (ani_counter > 30) {
		ani_counter = 0;
		move_bane = false;
	}
	else if (move_bane = true) {
		ani_counter++;
	}
}

//-----------------------------------
//マップ作製
//----------------------------------
void Map::MakeMap1() {

	if (scene == GAME||scene==RESULT || scene == GAMEOVER) {
		for (int y = 0; y < _map.size(); y++) {
			for (int x = 0; x < _map[y].size(); x++) {
				if (_map[y][x] == '1') {
					ScrollDrawGraph(
						x*block_size,
						y*block_size,
						1, 0,
						block_image1,
						false
					);
				}
				if (_map[y][x] == '2') {
					ScrollDrawGraph(x*block_size, y*block_size, 1, 0, limit_image, true);
				}
				if (_map[y][x] == '3') {
					if (bane_counter <= 5) {
						ScrollDrawGraph(x*block_size, y*block_size, 1, 0, bane_image2, true);
					}
					else if (bane_counter >= 5 && ani_counter <= 15) {
						ScrollDrawGraph(x*block_size, y*block_size, 1, 0, bane_image1, true);
					}
				}
				
			
			
			}
		}
	}
}

//------------------------------------
//ポジション把握
//------------------------------------
char Map::GetMapID(int x, int y)
{
	int mx = x / block_w;
	int my = y / block_h;

	//マップ内にいるかどうか
	if (mx < 0 || mx >= MAP_W && my > 0 || my >= MAP_H) {
		return 0;
	}
	return _map[my][mx];
}

//---------------------------------------------
//経過時間によってスピードとアニメーションを🐸
//---------------------------------------------
void Map::ChengPlayerImage() {
	if (scene == GAME && player.is_hit == false||scene==RESULT) {
		if (map.scroll_couter >= 100 && map.scroll_couter <= 300)
		{
			player.RenderRight(4, 9, 14);
		}
		else if (map.scroll_couter > 300)

		{
			player.RenderRight(2, 5, 8);

		}
		else {
			player.RenderRight(10, 20, 30);
		}
	}
}

void Map::ChengPlayerSpeed() {
	if (scene == GAME) {
		if (map.scroll_couter > 100 && map.scroll_couter < 300)
		{
			player.SetSpeed(1.8);
			//マップの速さ
			speed = 2.0f;
		}
		else if (map.scroll_couter > 300)
		{
			player.SetSpeed(2.5);
			//speed = 2.5f;
			speed = 2.5f;
		}
		else {
			player.SetSpeed(1.3);
			speed = 1.6f;
		}
	}
}

//---------------------------------
//マップを流すよう
//--------------------------------
void Map::ScrollDrawGraph(float x, float y, int size, float rota, int handle, bool flag)
{
	DrawRotaGraph(x - scl, y, size, rota, handle, flag);
}

//-----------------------------------
//マップ流れるスピード
//-----------------------------------
void Map::MoveMap() {
	if (scene == GAME) {
		scl += speed;
		scroll_couter++;
	}
}

//スピード取得
float Map::GetSpeed() {
	return speed;
}


void Map::AddCrystalCount() {
	crystal_counter = (crystal_counter + 1) % 30;

}

void Map::DrawCrystal() {
	int c = crystal_counter;
	int x_ = 5550;
	if (scene == GAME) {
		if (c >= 0 && c < 10) {
			DrawGraph(x_ - scl, 190, crystal_image[0], true);
		}
		else if (c >= 10 && c < 20) {
			DrawGraph(x_ - scl, 190, crystal_image[1], true);
		}
		else if (c >= 20 && c < 30) {
			DrawGraph(x_ - scl, 190, crystal_image[2], true);
		}
	}
}



void MapInit() {


}
void MapUpdate() {

}
void MapRender() {


}