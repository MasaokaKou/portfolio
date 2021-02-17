#pragma once

class Circle
{
public:
	Circle()
	: _x(0)
	, _y(0)
	, _radius(0)
	, _color(0)
	, _alpha(255)
	{
	}

	~Circle()
	{
	}

	void SetPosition(int x, int y)
	{
		_x = x;
		_y = y;
	}

	void Draw()
	{
		if (_alpha == 255) {
			DrawCircle(_x, _y, _radius, _color, true);
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
			DrawCircle(_x, _y, _radius, _color, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}

public:
	int _x;
	int _y;
	int _radius;
	int _color;
	int _alpha;
};

class Score;

class Result {
public:
	Result();
	~Result();

	void Load();
	void Update();

	void PreDraw();
	void PostDraw();

	bool IsShowScore() const;

	bool IsFinishAnimation() const;

	void EndGame();
	void ReSetGame();

	int GetCount() { return _counter; }

	void ShowRank( Score *score);
private:
	void UpdateMoveWindow();
	void UpdateFadeOutColor();
	//void UpdateMovaPlayer();

	void DrawText();
	void MovePlayer();
	void DrawCube();
	void DrawPlayer();
	void SetGravity();
private:
	int _image;
	int _player_image[12];
	int _txt_image[2];
	int _rank_image[4];

	Circle _circle;
	
	int _px;
	int _py;
	int _p_anim_counter;
	bool _is_jump;
	float _gravity;
	float _v;

	int _box_x;
	int _box2_x;
	int _box_color;

	int _image_alpha;

	int _cube1_x;
	int _cube1_y;
	int _cube2_x;
	int _cube2_y;
	int _cube3_x;
	int _cube3_y;
	int _cube4_x;
	int _cube4_y;
	int _cube_color;

	int color;

	int _counter;

	int _waitCounter;

	int _diffusionCounter;

	int _score;
	int _rank;

	//Ç¢Å[Ç∂ÇÒÇÆóp
	float _t;

	bool _isShowScore;
	bool _isFinishAnimation;
};