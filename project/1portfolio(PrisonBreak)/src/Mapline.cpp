#include"MAIN.H"
#include"GAME.H"
#include"player.h"
#include"Mapline.h"


Mapline::Mapline()
{
	line_x = 0;
	line_y = 0;
	MAP_X = 5550;
	color = GetColor(255, 255, 255);
	color2 = GetColor(255, 255, 255);
	flag_counter = 0;
}

Mapline::~Mapline() {

}

//�}�b�v���C���̍��W�ݒ�
void Mapline::SetLinePos() {
	line_x = 20;
	line_y = 300;
	line_x2 = MAP_X / 17;
    line_y2 = 300;
	player_y = line_y;
}
//�摜�ǂݍ���

void Mapline::Load()
{
	for(int i = 0; i < 10; i++) {
		char file_str[256];
		sprintfDx(file_str, "data/flag/flag%01d.png", (i + 1));
		flag_image[i] = LoadGraph(file_str);
	}
}

//���`��
void Mapline::DrawFlag() {
	if (scene == GAME || scene == RESULT || scene == GAMEOVER) {
		for (int i = 0; i <= 9; i++) {
			if (flag_counter > 10 + (5 * i) && flag_counter < 15 + (5 * i)) {
				DrawGraph(line_x2 / 2, 260, flag_image[i], true);
			}
			else if (flag_counter >= 55) {
				DrawGraph(line_x2 / 2, 260, flag_image[9], true);
			}
		}
	}
}


//�}�b�v���C���`��
void Mapline::DrawMapLine() {

	if (scene == GAME || scene == RESULT || scene == GAMEOVER) {
		DrawLine(line_x, line_y, line_x2+5, line_y2, color, true);
		for (int i = 0; i < 21; i++) {
			DrawLine(25+(15*i), 291, 25+(15*i), 310, color, true);
		}
	}
}

//�v���C���[�ʒu�ݒ�
void Mapline::SetPlayerCirclePos() {
	int x = player.GetX();
	player_x = x/17;
}

//�v���C���[�ʒu�`��
void Mapline::DrawPlayerCircle(){
	if (scene == GAME || scene == RESULT || scene == GAMEOVER) {
		DrawCircle(player_x, player_y, 10, color2, true);
	}
}


//�����܂ŗ�����ʒm
void Mapline::CheckHalfPoint() {
	if (player_x > (MAP_X/17) / 2) {
		flag_counter+=3;
	}
	else {
		flag_counter = 0;
	}
}

//�F�w��
void Mapline::SelectColor() {
	if (player.is_hit == true) {
		color2 = GetColor(255, 0, 0);
	}
	else {
		color2 = GetColor(255, 255, 255);
	}
}
