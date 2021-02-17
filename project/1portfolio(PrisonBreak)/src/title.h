#pragma once

class Title {
public:
	//ドア開けるよう
	bool door_check;
	//ゲームスタートカウントダウン
	int start_counter;
	int True_Title;
	Title();
	virtual ~Title();
	void Load();
	void AddTitleCount();
	void AddDoorCount();
	void PlayDoorSound();
	void EndTitle();
	void RenderTitle();
	void RenderTitle2();
	void RenderTitleChara();
	void MoveTitleChara();
	void EndTitle2();
	void AddStartCounter();

	void StartCountDown();
	int door_counter;
private:

	//タイトル文字動かす用
	int chara_x;
	int chara_y;
	float chara_r[5];
	float chara_size;
	int chara_counter;
	int chara2_y;
	//タイトルが落ちてくる時間
	int counter;
	//タイトル画面でジャンプ用
	bool true_title_move;


	//読み込み用
	int title_image;
	int door_image[12];
	int title_r;
	int subtitle_chara_image;
	int title_chara_image[5];
	int count_image[5];
	int go;
	

};
extern Title title;
void TitleInit();
void TitleExit();
void TitleUpdate();
void TitleRender();
//extern bool title2;
//extern bool title;
//extern bool door_check;