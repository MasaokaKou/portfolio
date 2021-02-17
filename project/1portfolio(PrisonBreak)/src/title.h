#pragma once

class Title {
public:
	//�h�A�J����悤
	bool door_check;
	//�Q�[���X�^�[�g�J�E���g�_�E��
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

	//�^�C�g�������������p
	int chara_x;
	int chara_y;
	float chara_r[5];
	float chara_size;
	int chara_counter;
	int chara2_y;
	//�^�C�g���������Ă��鎞��
	int counter;
	//�^�C�g����ʂŃW�����v�p
	bool true_title_move;


	//�ǂݍ��ݗp
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