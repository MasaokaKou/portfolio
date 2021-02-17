#pragma once
class Score;

#include<array>
#include<string>

#define NumMax 100




class InputName{
public :
	InputName();

	virtual ~InputName();

	void Init();

	void Update();

	bool UpdateInput();

	void Draw();

	void DrawWindow();

	void Exit();

	void Anim();


	void SetInputFlag(){ _input_once = false; }

	int GetAni() { return _ani_counter; }
	int GetY() { return _window_y; }
private:
	float _window_y;
	int _window_blend;

	int _window_image[4];
	int _text_image[2];
	float _text_y;

	int _ani_counter;
	bool _counter_switch;

	int _chara_image[2];
	float _chara_1y;
	

	int _cur_image;
	int _cur_x;



	int _InputHandle;

	//名前を入れるよう(文字数)
	char _name[20];

	bool _input_once;

	bool _isShowName;

protected:
	std::string _name_in_rank[NumMax];
	const int name_max;
};



class Ranking 
{
public:
	Ranking();
	virtual ~Ranking();

	void Init();

	void Load();

	void Update(Score* score);



	void Draw(Score* score);
	void  DrawImage();

	void Exit();

	void Save();

	bool IsInitialized() const { return _initialized; }

	
	void Connect(Score* score);
	void DrawName(Score* score);

	void SetOutputFlag() { _output_once = false; }


	int GetLoop() {
		return _loop;
	}
private:
	int _image;
	int _frame_image;


	//txtに書き込むスコアを入れる用の配列(上位3位まで)
	std::array<int, 3> _ranking;

	std::string _now_player;

	std::string _player_buffer[NumMax];
	int _score[NumMax];



	//入力された名前の保存場所
	std::string  _name[3];

	//何週目か
	int _loop;

	bool _output_once;

	bool _initialized;
};
