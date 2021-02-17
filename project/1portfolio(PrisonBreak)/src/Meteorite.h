#pragma once
#include"MainBase.h"
class Meteorite :
	public MainBase{
protected:
	int speed;
	bool is_dead;
	bool attention_reset;
	bool end_reset;
	int meteorite_state;
	bool attention_state;
	int meteorite_image;
	int attention_image;
	int end_counter;
	int attention_counter;
	const int end_max;
	const int attention_max;
	const int image_w;
	const int image_h;

public:
Meteorite();
~Meteorite();
void Load();
void Render();
void Appear(int line);
void Move();
void Set();
void Hit();
void ChangeMeteoriteState(int state);

void AddEndCounter();
void AddAttentionCounter();
void ChangeAttetionState();
void AttentionRender();
void AttentionReset();
void EndReset();

void SoundMove();

bool GetIsDead() { return is_dead; }
void SetIsDead() { is_dead = true; }
int GetCounter() { return end_counter; }

int GetC() { return attention_counter; }


};
