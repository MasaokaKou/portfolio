#pragma once

class Score;

class GameOver {
public:
	GameOver();
	~GameOver();


	void Load();
	void Draw();
	void Update();


	void BoxRender();
	void DrawCursor();
	void MoveCursor();

	void ChengeScene();

	void GetScore();
	void ShowScore();

	void AddSceneCount() ;
	int GetCount() { return _scene_counter; }

private:
	int _continue_image;
	int _no_image;
	int _yes_image;
	int _gameover_image;
	int _text_image[2];

	bool _show;

	int _cx;

	int _scene_counter;


};
