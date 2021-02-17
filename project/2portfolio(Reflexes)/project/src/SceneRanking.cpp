#include"Main.h"
#include<iostream>
#include<string>
#include<fstream>

#include"SceneRanking.h"

//--------------------------
//! コンストラクタ
//--------------------------
Ranking::Ranking()
	:_initialized(false)
{
	_fontHandle = CreateFontToHandle(NULL, 50, 3);
	_blinkTimer = 0;
	_alpha = 0;

	_scoreAlpha = 0;
	_char_y = -30;
}

//--------------------------
//! デストラクタ
//--------------------------
Ranking::~Ranking()
{
}


//! 初期化
void Ranking::initialize()
{

	for (int i = 0; i < _ranking.size(); i++) {
		_ranking[i] = 0;
	}

	//テキストファイルをを開ける
	std::ifstream file("ranking.txt");

	if (file.is_open()) {
		std::string buffer;

		//ファイルから1行とってくる
		for (int i = 0; i < _ranking.size(); i++) {
			getline(file, buffer);
			_ranking[i] = std::atoi(buffer.c_str());
		}
		file.close();
	}
	
	_initialized = true;

}


//! 更新
void Ranking::update()
{

	//ランキングの更新
	int now = _score;

	for (int i = 0; i < _ranking.size(); ++i) {
		if (now < _ranking[i]) continue;

		int tmp = _ranking[i];
		_ranking[i] = now;
		now = tmp;
	}
	
}

//! 描画
void Ranking::draw()
{
	std::string text;
	std::string name;


	//ファイルから読み込んで描画
	for (int i = 0, j = 1; i < _ranking.size(), j <= _ranking.size(); i++, j++) {

		text = "No.";
		text += std::to_string(j);
		text += ": ";
		text += std::to_string(_ranking[i]);

		DrawStringToHandle(400, 150 + (50 * i), text.c_str(), GetColor(0, 0, 0), _fontHandle);
		if (_ranking[i] == _score) {
			DrawStringToHandle(400, 150 + (50 * i), text.c_str(), GetColor(255, 0, 0), _fontHandle);
		}

	}
	

}


//! 描画
void Ranking::drawSceneRanking()
{
	std::string text;
	std::string name;

	//ファイルから読み込んで描画
	for (int i = 0, j = 1; i < _ranking.size(), j <= _ranking.size(); i++, j++) {

		text = "No.";
		text += std::to_string(j);
		text += ": ";
		text += std::to_string(_ranking[i]);

		s16 x = WINDOW_W / 2 - 95;
		s16 y = 170 + (50 * i);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, _scoreAlpha);
		DrawStringToHandle(x, y, text.c_str(), GetColor(0, 0, 0), _fontHandle);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}


	s16 y = 110;
	if (_char_y <= y)
		_char_y+=2;

	DrawStringToHandle(WINDOW_W / 2 - 170, _char_y, " ～RANKING～", GetColor(0, 0, 0), _fontHandle);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
	DrawStringToHandle(WINDOW_W / 2 + 100, 400, " PUSH 0", GetColor(0, 0, 0), _fontHandle);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	_scoreAlpha += 2;
	blink();

}

//! 破棄
void Ranking::exit()
{
	_scoreAlpha = 0;
	_char_y = -30;
}


void Ranking::Save()
{
	//セーブ
	std::ofstream file("ranking.txt");

	file << _ranking[0] << std::endl;
	file << _ranking[1] << std::endl;
	file << _ranking[2] << std::endl;

	file.close();
}

void Ranking::blink()
{
	s16 val = 60;
	s16 speed = 4;

	if (_blinkTimer <= val)
		_alpha += speed;

	if (_blinkTimer >= val)
		_alpha -= speed;

	if (_blinkTimer >= val * 2)
		_blinkTimer = 0;

	if (_alpha <= 0)_alpha = 0;
	if (_alpha >= 255)_alpha = 255;

	_blinkTimer++;
}

