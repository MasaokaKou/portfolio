#pragma once
class Pause {
private:
	bool is_pause;
	int scroll_counter;
	int scroll_image[4];
	int text_image;
	int cursor_y;

public:
	 Pause();
	 ~Pause();
	bool GetPause();
	void SetPause(bool P);
	void ChengePause();
	void Load();
	void DrawScroll();
	void AddScrollCount();
	void DrawCursor();
	void MoveCursor();
	void SelectPause();
	void ScrollSound();



};