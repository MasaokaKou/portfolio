#pragma once
class MainBase
{
protected:
	float x;//���W�p
	float y;
	int dir;  //�����p
	float v; //�d�͗p
	float size;//�T�C�Y�p
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

