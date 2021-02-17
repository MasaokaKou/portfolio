#pragma once
#include "MainBase.h"
class Enemy :
	public MainBase
{

public:
	Enemy();
	~Enemy();
	void Load();
	void Update();
	void Render1();
	void Render2();
	void Hit();
	void ShowScore();
	void MoveScore();
	void ResetAlpha() { _blend = 255; };
	int _blend;
	int enemy_image[100];
    int ani_counter;
	bool is_dead;
	bool score;

};




