#pragma once
#include"main.h"

class Mapline {
public:
	Mapline();
	~Mapline();
	void Load();
	void DrawFlag();
	void DrawMapLine();
	void SetLinePos();
	void DrawPlayerCircle();
	void SetPlayerCirclePos();
	void CheckHalfPoint();
	void SelectColor();
private:
    int MAP_X;
	int flag_image[10];
	int flag_counter;
	float line_x;
	float line_y;
	float line_x2;
	float line_y2;
	float player_x;
	float player_y;
	int color;
	int color2;
};

