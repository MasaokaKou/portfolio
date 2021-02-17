#pragma once
class MainBase
{
protected:
	float x;//座標用
	float y;
	int dir;  //方向用
	float v; //重力用
	float size;//サイズ用
public:
	MainBase();
	~MainBase();
	void Update();
	void Render();
	float GetX();
	float GetY();
	int GetDir();

	float GetSize();
	float GetV();
	void SetX(float num);
	void SetY(float num);
	void SetDir(int num);
	void SetSize(float num);
	void SetV(float num);

};

