#include"Main.h"
#include"Score.h"
#include"Ranking.h"
#include"player.h"
#include"KEYINPUT.H"
#include"Game.h"
#include<iostream>
#include<string>
#include<fstream>


Ranking::Ranking()
	: _initialized(false)
{
	_output_once = false;
	
}

Ranking::~Ranking() {

}

void Ranking::Load() {

	_image = LoadGraph("data/ranking.png");
	_frame_image = LoadGraph("data/rankingF.png");


}

void Ranking::Init()
{
	
	for (int i = 0; i < _ranking.size(); i++) {
		_ranking[i] = 0;
	}

	//テキストファイルをを開ける
	std::ifstream file("txt/ranking.txt");

	if (file.is_open()) {
		std::string buffer;

		//ファイルから1行とってくる
		for (int i = 0; i < _ranking.size(); i++) {
			getline(file, buffer);
			_ranking[i] = std::atoi(buffer.c_str());
		}
		file.close();
	}

	//std::ifstream Namefile("txt/name2.txt");

	//if (Namefile.is_open()) {
	//	std::string name_buffer;

	//	//ファイルから1行とってくる
	//	for (int i = 0; i < 3; i++) {
	//		getline(Namefile, name_buffer);
	//		_name[i] = std::atoi(name_buffer.c_str());
	//	}
	//	Namefile.close();
	//}


	
	_initialized = true;
}

void Ranking::Update(Score* score)
{

	//ランキングの更新
	int now = score->GetScore();

	for (int i = 0; i < _ranking.size(); ++i) {
		if (now < _ranking[i]) continue;

		int tmp = _ranking[i];
		_ranking[i] = now;
		now = tmp;
	}
}

void Ranking::Draw(Score* score)
{
	std::string text;
	std::string name; 


	//ファイルから読み込んで描画
	for (int i = 0, j = 1; i < _ranking.size(), j <= _ranking.size(); i++, j++) {

		//if (_ranking[i] == score->GetScore())
		{
			name = _now_player;
			name += " : ";
			
		}
		
		text = "No.";
		text += std::to_string(j);
		text += ": ";
		text += std::to_string(_ranking[i]);


		DrawString(400, 150 + (50 * i), text.c_str(), GetColor(0, 0, 0));
		
		if (_ranking[i] == score->GetScore()){
			DrawString(300, 150 + (50 * i), name.c_str(), GetColor(0, 0, 0));
	}
	}


	
	
}

void Ranking::DrawImage() {
	

	//ジョイパッドがつながっていなければ
	if (GetJoypadNum() == 0) {
		DrawString(60, 260, "PUSH R", GetColor(0, 0, 0));
	}
	else {
		DrawString(60, 260, "PUSH B", GetColor(0, 0, 0));
	}
	
	DrawGraph(170, 50, _image, true);
	DrawGraph(0, 0, _frame_image, true);


}

void Ranking::Exit()
{
	_initialized = false;

	{
		std::ofstream ofsLoop("txt/loop.txt");
		ofsLoop << _loop;
		ofsLoop.close();
	}

	
	{
		//const char* playerName = _inputName.GetName();

		
	}
	
	
	
}

void Ranking::Save()
{
	//セーブ
	std::ofstream file("txt/ranking.txt");

	file << _ranking[0] << std::endl;
	file << _ranking[1] << std::endl;
	file << _ranking[2] << std::endl;

	file.close();
}

//現在のプレイヤー名取得
void Ranking::Connect(Score* score)
{
	
	{
		std::string name_buffer;

		std::ifstream file("txt/name.txt");
		{
			getline(file, name_buffer);
		}
		file.close();

		_now_player = name_buffer.c_str();
	}

	//trueならreturn
	if (_output_once)return;

	// ファイルの末尾へ追加
	std::ofstream ofsNameList("txt/name2.txt", std::ios::app);
	ofsNameList << _now_player <<" : "<<score->GetScore()<< std::endl;

	_output_once = true;

	/*
	int L = GetLoop();

	std::string buffer;
	std::ifstream ifsNameScore("txt/name&score");
	if (ifsNameScore.is_open()) {

		// {playerName} : {score}
		file2 << _player_buffer[i] << " : " << _score[i] << std::endl;

		int index = 0;
		while (std::getline(ifsNameScore, buffer)) {

			//_player_buffer[index] = 
		}
	}

	std::ofstream file2("txt/name&score");


	_player_buffer[L] = _now_player;
	_score[L] = score->GetScore();

	for (int i = 0; i < NumMax; i++) {
		file2 << _player_buffer[i] << " : " << _score[i] << std::endl;
	}
	file2.close();
	*/
}



//ランキングでの名前描画
void Ranking::DrawName(Score* score) {

	std::string name;
	
	name = _now_player;


		DrawString(140, 160, name.c_str(), GetColor(0, 0, 0));
		
		char text[256];
		sprintf_s(text, "%d", score->GetScore());
		DrawString(140, 180, text, GetColor(0,0,0));


	
}

//--------------------------
//名前入力
//--------------------------


InputName::InputName()
: _InputHandle	(-1)
, _ani_counter	(0)
, name_max		(50)
{
	_window_y = -10.0f;
	_window_blend = 500;
	_cur_x = 210;

	_text_y = 50.0f;

	_chara_1y = 200;

	_input_once = false;
	_isShowName = false;
	{
		std::ifstream file("txt/name2.txt");
		std::string name_buffer;
		for (int i = 0; i < name_max; i++) {
			//ファイルから1行とってくる
			getline(file, name_buffer);
			_name_in_rank[i] = name_buffer;
		}
		file.close();
	}

	{
		std::ifstream file2("txt/loop.txt");
		std::string loop_buffer;
		getline(file2, loop_buffer);
		//_loop = std::atoi(loop_buffer.c_str());
		file2.close();
	}
}


InputName::~InputName() {
	
}

void InputName::Init() {
	_window_image[0] = LoadGraph("data/scroll/input/scroll1.png");
	_window_image[1] = LoadGraph("data/scroll/input/scroll2.png");
	_window_image[2] = LoadGraph("data/scroll/input/scroll3.png");
	_window_image[3] = LoadGraph("data/scroll/input/scroll4.png");

	_chara_image[0]= LoadGraph("data/scroll/nomal.png");
	_chara_image[1] = LoadGraph("data/scroll/hard.png");

	_cur_image= LoadGraph("data/scroll/cur.png");

	_text_image[0] = LoadGraph("data/scroll/input/txt.png");
	_text_image[1] = LoadGraph("data/scroll/input/txt_pad.png");

	int b = GetColor(0, 0, 0);
	int h = GetColor(255, 255, 255);
	SetKeyInputStringColor(b, h, h, h, h, h, h, h, h, h, h, h, h, h, h, h);

	// 文字列入力ハンドルを作成する
	//_InputHandle = MakeKeyInput(80, FALSE, FALSE, FALSE);

	// 作成した入力ハンドルをアクティブにする
	//SetActiveKeyInput(_InputHandle);

	_counter_switch = true;

}

void InputName::Update() {
	if (_ani_counter > 150)_ani_counter = 150;
	

	if (_counter_switch == true) {
		++_ani_counter;
	} 
	if (_counter_switch == false) {
		_window_blend -= (float)0.5f;
		--_ani_counter;
		if (_ani_counter < 70) {
			_window_y += 0.5f;
		
		}
	}

}

bool InputName::UpdateInput() {

	
		// 作成した入力ハンドルをアクティブにする
		if (_input_once == false) {
			_InputHandle = MakeKeyInput(80, FALSE, FALSE, FALSE);
			SetActiveKeyInput(_InputHandle);
			
			_window_blend = 320;
			_ani_counter = 0;
			_counter_switch = true;
			_isShowName = false;
			_input_once = true;
			_text_y = 50.0f;
			_window_y = -10.0f;
			_chara_1y = 200;

		}
	

	// 文字列の入力が終っている場合
	if (CheckKeyInput(_InputHandle) !=1) {
		return false;
	}



	// 入力された文字列を取得する
	GetKeyInputString(_name, _InputHandle);

	// 入力情報(文字列)をリセットする
	DeleteKeyInput(_InputHandle);
	_InputHandle = -1;

	{
		//ファイルをあける
		std::ofstream file("txt/name.txt");
		file << _name << std::endl;
		file.close();
	}


	
	_isShowName = true;
	
	return true;
}


void InputName::Draw() {

	// 文字列表示域を白で塗りつぶす
	//DrawBox(100, 120, 540, 200, GetColor(0, 0, 255), TRUE);

	//画像
	DrawWindow();

	// 画面に入力中の文字列を描画する
	if (_ani_counter > 70) {
		DrawKeyInputString(230, 150 + 2, _InputHandle);
		DrawKeyInputModeString(640, 480);
	}

	//DrawString(220, 250, "名前を入力してください", GetColor(0,0,0));

	if (_isShowName) {
		DrawString(230, 152, _name, GetColor(0,0,0));
     if(_ani_counter<65){
		 _isShowName = false;
	 }
	}


	/*
	if (_InputHandle != -1)
	{
		if (CheckKeyInput(_InputHandle) == 1) {
			// 入力した文字を描写する
			DrawString(0, 120, _name, GetColor(0, 255, 255));
		}
	}
	*/
}

//ウインドウアニメーション
void InputName::DrawWindow() {

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _window_blend);

//全体の描画
	if (_ani_counter > -150 && _ani_counter < 40) {
		DrawGraph(120, _window_y, _window_image[0], true);
	}
	else if (_ani_counter >= 40 && _ani_counter < 50) {
		DrawGraph(120, _window_y, _window_image[1], true);
	}
	else if (_ani_counter >= 50 && _ani_counter < 60) {
		DrawGraph(120, _window_y, _window_image[2], true);
	}
	else if (_ani_counter >= 60 ) {
		DrawGraph(120, _window_y, _window_image[3], true);
	}

	//ジョイパッドがつながっていなければ
	if (GetJoypadNum() == 0) {
		if (_ani_counter >= 70) {
			DrawGraph(210, _text_y, _text_image[0], true);
		}
	}
	else {
		if (_ani_counter >= 70) {
			DrawGraph(210, _text_y, _text_image[1], true);
		}
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


	if (_ani_counter >= 70) {
		//難易度選択画面
		DrawGraph(220, _chara_1y, _chara_image[0], true);
		DrawGraph(330, _chara_1y, _chara_image[1], true);
		//入力が終わっていたら
		if(_InputHandle == -1)
		{
			DrawGraph(_cur_x, 185, _cur_image, true);
			//難易度の説明描画
			if (_cur_x == 210) {

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 130);
				DrawBox(10,180,170,250,GetColor(255,255,255),true);
				DrawTriangle(170,200,170,230,220,215,GetColor(255,255,255),true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				
				DrawString(20, 190, "プレイヤーがHPを", GetColor(0, 0, 0));
				DrawString(20, 210, "持っていません。", GetColor(0, 0, 0));
			}
			if (_cur_x == 310) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 130);
				DrawBox(630, 180, 460, 280, GetColor(255, 255, 255), true);
				DrawTriangle(460, 200, 460, 230, 420, 215, GetColor(255, 255, 255), true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			DrawString(470, 190, "プレイヤーがHPを", GetColor(0, 0, 0));
			DrawString(470, 210, "持っていています。", GetColor(0, 0, 0));
			DrawString(470, 230, "HPが0になると", GetColor(0, 0, 0));
			DrawString(470, 250, "ゲームオーバーです。", GetColor(0, 0, 0));
		}
	}
}

void InputName::Anim()
{
	if (_ani_counter < -150) {
		scene = SELECT;
	}

	//ジョイパッド
	if (_InputHandle == -1) {

		if (GetJoypadInputState(DX_INPUT_PAD1) & (PAD_INPUT_RIGHT)) {

			if ((player._before_BIT & PAD_INPUT_RIGHT) == false) {
				if (_cur_x == 210)
					_cur_x += 100;
			}
		}


		if (GetJoypadInputState(DX_INPUT_PAD1) & (PAD_INPUT_LEFT)) {

			if ((player._before_BIT & PAD_INPUT_LEFT) == false) {
				if (_cur_x == 310)
					_cur_x -= 100;
			}
		}

		if (GetJoypadInputState(DX_INPUT_PAD1) & (PAD_INPUT_2)) {

			if ((player._before_BIT & PAD_INPUT_2) == false) {
				if (_cur_x == 210) {
					is_easy = true;

				}
				else if (_cur_x == 310) {
					is_easy = false;
				}

				_counter_switch = false;

			}
		}
	}


	if (GetJoypadNum() != 0)return;

	//難易度選択
	//if (_counter_switch==false)
	if (_InputHandle == -1)
	{
		if (IsKeyOn(KEY_INPUT_RIGHT)) {
			if (_cur_x == 210)
				_cur_x += 100;

		}if (IsKeyOn(KEY_INPUT_LEFT)) {
			if (_cur_x == 310)
				_cur_x -= 100;
		}
	
		if (IsKeyOn(KEY_INPUT_RETURN)) {
			if (_cur_x == 210) {
				is_easy = true;
				
			}
			else if (_cur_x == 310) {
				is_easy = false;
			}
		

			_counter_switch = false;
		}
	}

}


void InputName::Exit() {
	
}
