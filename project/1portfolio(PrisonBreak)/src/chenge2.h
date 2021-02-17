#pragma once

//セレクトからゲームへのシーン切り替え
class Chenge2 {
public:
	Chenge2();
	~Chenge2();

	void ChengeScene();

	void SetCirclePos();
	void MoveCircle();
	void CircleRender();

	void SetFlag();
private:
	int _image[2];
	int _x, _y;
	int _r;
	int _color;
	int _blend;

	bool start;
	bool _once;

};