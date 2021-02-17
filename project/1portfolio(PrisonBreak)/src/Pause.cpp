#include"MAIN.H"
#include"Pause.h"
#include"KEYINPUT.H"
#include"title.h"
#include"Game.h"
#include"map.h"
#include"player.h"
#include"ENEMY.H"
#include"sound.h"
Pause::Pause() {
	is_pause = false;
	scroll_counter = 0;
	cursor_y = 200;
}

Pause::~Pause() {
	for (int i = 0; i < 4; i++) {
		DeleteGraph(scroll_image[i]);
	}
	DeleteGraph(text_image);
}

//�����摜�ǂݍ���
void Pause::Load() {
	scroll_image[0] = LoadGraph("data/scroll/scroll1.png");
	scroll_image[1] = LoadGraph("data/scroll/scroll2.png");
	scroll_image[2] = LoadGraph("data/scroll/scroll3.png");
	scroll_image[3] = LoadGraph("data/scroll/scroll4.png");
	text_image = LoadGraph("data/scroll/pause_text.png");
}

//�|�[�Y�擾�p
bool Pause::GetPause() {
	return is_pause;
}

void Pause::SetPause(bool P) {
	is_pause = P;
}

//P����������|�[�Y��ʂɈڍs
void Pause::ChengePause() {
	if (scene == GAME) {
		
		//�W���C�p�b�h
		if (GetJoypadInputState(DX_INPUT_PAD1) & (PAD_INPUT_4)) {

			if ((player._before_BIT & PAD_INPUT_4) == false) {

				if (is_pause == false) {
					is_pause = true;
				}
				else if (is_pause == true) {
					is_pause = false;
					scroll_counter = 0;
					//title.start_counter = 120;
				}

			}

		}

		if (GetJoypadNum() != 0)return;

		if (IsKeyOn(KEY_INPUT_P)) {
			if (is_pause == false) {
				is_pause = true;
			}
			else if (is_pause == true) {
				is_pause = false;
				scroll_counter = 0;
				//title.start_counter = 120;
			}
		}

	}
}

//�|�[�Y��ʂ̂Ƃ��J�E���^�[����
void Pause::AddScrollCount() {
	if (is_pause == true) {
		scroll_counter++;
	}
	if (scroll_counter > 80) {
		scroll_counter = 80;
	}


}

//�����`��
void Pause::DrawScroll() {
	if (is_pause == true) {
		if (scroll_counter > 0 && scroll_counter < 40) {
			DrawGraph(170, -10, scroll_image[0], true);
		}
		else if (scroll_counter >= 40 && scroll_counter < 50) {
			DrawGraph(170, -10, scroll_image[1], true);
		}
		else if (scroll_counter >= 50 && scroll_counter < 60) {
			DrawGraph(170, -10, scroll_image[2], true);
		}
		else if (scroll_counter >= 60) {
			DrawGraph(170, -10, scroll_image[3], true);
		}
		if (scroll_counter > 70) {
			DrawRotaGraph(310, 170, 0.8, 0, text_image, true);
		}
	}
}

//�|�[�Y��ʂ̃J�[�\���`��
void Pause::DrawCursor() {
	if (scroll_counter > 70) {
		DrawCircle(245, cursor_y, 5, GetColor(255, 0, 255), true);
	}
}

//�J�[�\���ړ�
void Pause::MoveCursor() {

	//�W���C�p�b�h
	if (GetJoypadInputState(DX_INPUT_PAD1) & (PAD_INPUT_UP)) {

		if ((player._before_BIT & PAD_INPUT_UP) == false) {
			cursor_y = 200;
			sound.Pause1();
		}
	}

	if (GetJoypadInputState(DX_INPUT_PAD1) & (PAD_INPUT_DOWN)) {

		if ((player._before_BIT & PAD_INPUT_DOWN) == false) {
			cursor_y = 230;
			sound.Pause1();
		}
	}



	if (GetJoypadNum() != 0)return;

	if (IsKeyOn(KEY_INPUT_UP)) {
		cursor_y = 200;
		sound.Pause1();
	}
	if (IsKeyOn(KEY_INPUT_DOWN)) {
		cursor_y = 230;
		sound.Pause1();
	}
}

//�|�[�Y��ʂőI��
void Pause::SelectPause() {
	
	
	if (scroll_counter > 70) {



		//�W���C�p�b�h
		if (GetJoypadInputState(DX_INPUT_PAD1) & (PAD_INPUT_2)) {

			if ((player._before_BIT & PAD_INPUT_2) == false) {
				
				sound.Pause2();
				is_pause = false;
				if (cursor_y == 200) {
					map.scl = 0;
					scroll_counter = 0;
					title.start_counter = 0;
					map.check_pos_once = true;
					player.wall_x = 100;


				}
				else if (cursor_y == 230) {
					scene = SELECT;
					map.scl = 0;
					scroll_counter = 0;
					title.start_counter = 0;
					map.check_pos_once = true;
					player.wall_x = 100;


				}


			}
		}


		if (GetJoypadNum() != 0)return;

		if (IsKeyOn(KEY_INPUT_SPACE))
		{
			sound.Pause2();
			is_pause = false;
			if (cursor_y == 200) {
				map.scl = 0;
				scroll_counter = 0;
				title.start_counter = 0;
				map.check_pos_once = true;
				player.wall_x = 100;


			}
			else if (cursor_y == 230) {
				scene = SELECT;
				map.scl = 0;
				scroll_counter = 0;
				title.start_counter = 0;
				map.check_pos_once = true;
				player.wall_x = 100;


			}


			
		}
	}
}

void Pause::ScrollSound() {
	if (scroll_counter == 40)sound.Pause3();
}
