#include"Meteorite.h"
#include"Main.h"
#include"player.h"
#include"map.h"
#include"sound.h"
Meteorite::Meteorite() :
	image_w(32),
	image_h(32),
	end_max(300),
	attention_max(60)

{
	x, y = 0;

	speed = 5;
	is_dead = true;
	end_counter = 0;
	meteorite_state = 1;//(0)�Ȃ��i1�j�Ȃ牺

	attention_counter = 0;
	attention_state = false;//(true)�Ȃ��ifalse�j�Ȃ牺
	attention_reset = true;
	end_reset = true;
}

Meteorite::~Meteorite() {

}

//�摜�̓ǂݍ���
void Meteorite::Load() {
	meteorite_image = LoadGraph("data/meteorite.png");
	attention_image = LoadGraph("data/attention.png");
}

//�摜�`��
void Meteorite::Render() {
	map.ScrollDrawGraph(x + map.scl, y, 1, 0, meteorite_image, true);
}

//���ӊ��N�A�C�R���̃X�e�[�^�X�ύX
void Meteorite::ChangeAttetionState() {
	if (y > 200) attention_state = false;
	else attention_state = true;
}

//���e�I���ォ����
void Meteorite::ChangeMeteoriteState(int  state) {
	meteorite_state = state;
}

//覐΂����鏭���O��覐΂̃��[�g��m�点�Ă����A�C�R����\������
void Meteorite::AttentionRender() {

	if (attention_counter != 0) {
		if (attention_counter % 20 != 0
			&& attention_counter % 20 != 1) {

			if (attention_state == true) {
				DrawGraph(600, 170, attention_image, true);
			}
			else if (attention_state == false) {
				DrawGraph(600, 205, attention_image, true);
			}
		}
	}
}


//覐΂̏ꏊ���Z�b�g
void Meteorite::Set() {

	switch (meteorite_state) {
	case 0:
		x = 640;
		y = 170;
		break;

	case 1:
		x = 640;
		y = 220;
		break;
	}
}

//�������line�𒴂�����E����覐� 
void Meteorite::Appear(int line) {
	auto p = player.GetX();
	if (player.GetX() > line&&player.GetX() < line + 600) {

		if (player.GetX() > line&&player.GetX() < line + 300) {
			end_reset = false;
		}

		if(end_counter==1)attention_reset = false;
		if (end_counter > 120) {
			Render();
			is_dead = false;
		}
	}
}

//覐΂̓���
void Meteorite::Move() {
	if (is_dead == false) {
		x -= speed;
	}
}

//覐΂̂����蔻��
void Meteorite::Hit() {
	if (is_dead == false) {
		if (player.GetX() + player.W / 2 > x + map.scl &&
			player.GetX() + player.W / 2 < x + map.scl + image_w / 2 &&
			player.GetY() + (player.H / 2) > y&&
			player.GetY() - player.H / 2 < y + image_h) {
			player.is_hit = true;
			map.scroll_couter = 0;
		}
	}
}

//覐΂����ł��Ă��������܂ł̃J�E���^�[����
void Meteorite::AddEndCounter() {
	if (end_reset == false) {
		if (end_counter <= end_max) {
			end_counter++;

		}
		else if (end_counter > end_max) {
			end_reset = true;
			is_dead = true;
			sound.ResetPan();
		}
	}
}

//覐΂̒��ӊ��N�p�̃J�E���^�[����
void Meteorite::AddAttentionCounter() {
	if (attention_reset == false) {
		if (attention_counter < attention_max) {
			attention_counter++;
			if (attention_counter == 1) {
				sound.Warning();
			}

		}
		else if (attention_counter >= attention_max)
		{
			attention_reset = true;
		}
	}
}

//覐΃��Z�b�g
void Meteorite::EndReset() {
	if (end_reset == true)
	{
		end_counter = 0;
		
	}
}

//���ӊ��N���Z�b�g
void Meteorite::AttentionReset() {
	if (attention_reset == true)
	{
		attention_counter = 0;
	}
}

//�T�E���h�֌W
void Meteorite::SoundMove() {
	if (is_dead == false) {
		//覐΂̃T�E���h�ړ�
		sound.ChengeSoundLeft();
	}
}

