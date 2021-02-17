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

	//�e�L�X�g�t�@�C�������J����
	std::ifstream file("txt/ranking.txt");

	if (file.is_open()) {
		std::string buffer;

		//�t�@�C������1�s�Ƃ��Ă���
		for (int i = 0; i < _ranking.size(); i++) {
			getline(file, buffer);
			_ranking[i] = std::atoi(buffer.c_str());
		}
		file.close();
	}

	//std::ifstream Namefile("txt/name2.txt");

	//if (Namefile.is_open()) {
	//	std::string name_buffer;

	//	//�t�@�C������1�s�Ƃ��Ă���
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

	//�����L���O�̍X�V
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


	//�t�@�C������ǂݍ���ŕ`��
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
	

	//�W���C�p�b�h���Ȃ����Ă��Ȃ����
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
	//�Z�[�u
	std::ofstream file("txt/ranking.txt");

	file << _ranking[0] << std::endl;
	file << _ranking[1] << std::endl;
	file << _ranking[2] << std::endl;

	file.close();
}

//���݂̃v���C���[���擾
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

	//true�Ȃ�return
	if (_output_once)return;

	// �t�@�C���̖����֒ǉ�
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



//�����L���O�ł̖��O�`��
void Ranking::DrawName(Score* score) {

	std::string name;
	
	name = _now_player;


		DrawString(140, 160, name.c_str(), GetColor(0, 0, 0));
		
		char text[256];
		sprintf_s(text, "%d", score->GetScore());
		DrawString(140, 180, text, GetColor(0,0,0));


	
}

//--------------------------
//���O����
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
			//�t�@�C������1�s�Ƃ��Ă���
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

	// ��������̓n���h�����쐬����
	//_InputHandle = MakeKeyInput(80, FALSE, FALSE, FALSE);

	// �쐬�������̓n���h�����A�N�e�B�u�ɂ���
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

	
		// �쐬�������̓n���h�����A�N�e�B�u�ɂ���
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
	

	// ������̓��͂��I���Ă���ꍇ
	if (CheckKeyInput(_InputHandle) !=1) {
		return false;
	}



	// ���͂��ꂽ��������擾����
	GetKeyInputString(_name, _InputHandle);

	// ���͏��(������)�����Z�b�g����
	DeleteKeyInput(_InputHandle);
	_InputHandle = -1;

	{
		//�t�@�C����������
		std::ofstream file("txt/name.txt");
		file << _name << std::endl;
		file.close();
	}


	
	_isShowName = true;
	
	return true;
}


void InputName::Draw() {

	// ������\����𔒂œh��Ԃ�
	//DrawBox(100, 120, 540, 200, GetColor(0, 0, 255), TRUE);

	//�摜
	DrawWindow();

	// ��ʂɓ��͒��̕������`�悷��
	if (_ani_counter > 70) {
		DrawKeyInputString(230, 150 + 2, _InputHandle);
		DrawKeyInputModeString(640, 480);
	}

	//DrawString(220, 250, "���O����͂��Ă�������", GetColor(0,0,0));

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
			// ���͂���������`�ʂ���
			DrawString(0, 120, _name, GetColor(0, 255, 255));
		}
	}
	*/
}

//�E�C���h�E�A�j���[�V����
void InputName::DrawWindow() {

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _window_blend);

//�S�̂̕`��
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

	//�W���C�p�b�h���Ȃ����Ă��Ȃ����
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
		//��Փx�I�����
		DrawGraph(220, _chara_1y, _chara_image[0], true);
		DrawGraph(330, _chara_1y, _chara_image[1], true);
		//���͂��I����Ă�����
		if(_InputHandle == -1)
		{
			DrawGraph(_cur_x, 185, _cur_image, true);
			//��Փx�̐����`��
			if (_cur_x == 210) {

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 130);
				DrawBox(10,180,170,250,GetColor(255,255,255),true);
				DrawTriangle(170,200,170,230,220,215,GetColor(255,255,255),true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
				
				DrawString(20, 190, "�v���C���[��HP��", GetColor(0, 0, 0));
				DrawString(20, 210, "�����Ă��܂���B", GetColor(0, 0, 0));
			}
			if (_cur_x == 310) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 130);
				DrawBox(630, 180, 460, 280, GetColor(255, 255, 255), true);
				DrawTriangle(460, 200, 460, 230, 420, 215, GetColor(255, 255, 255), true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			}
			DrawString(470, 190, "�v���C���[��HP��", GetColor(0, 0, 0));
			DrawString(470, 210, "�����Ă��Ă��܂��B", GetColor(0, 0, 0));
			DrawString(470, 230, "HP��0�ɂȂ��", GetColor(0, 0, 0));
			DrawString(470, 250, "�Q�[���I�[�o�[�ł��B", GetColor(0, 0, 0));
		}
	}
}

void InputName::Anim()
{
	if (_ani_counter < -150) {
		scene = SELECT;
	}

	//�W���C�p�b�h
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

	//��Փx�I��
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
