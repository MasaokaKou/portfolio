#include"MainBase.h"
#include"Main.h"
#include"Game.h"
#include"player.h"
#include"Keyinput.h"
#include"title.h"
#include"sound.h"
#include"map.h"
#include"hit.h"
//---------------------------
//�v���C���[�T�C�Y
//--------------------------
#define PLAYER_IMAGE_MAX 12
#define PLAYER_SPEED 2
//--------------------------------------------
//�O���[�o���ϐ�
//---------------------------------------------
//�摜�ǂݍ��ݗp�ϐ�					  
int player_image[PLAYER_IMAGE_MAX];
int player_image_map[3];
float gravity = -0.45f;
//check2�̏����ʒu
bool check2Pos = true;
//---------------------------------------------
//�N���X�̃I�u�W�F�N�g����
//---------------------------------------------
Player player;

Player::Player() :
	H(32),
	W(32),
	SPACE(13)
{
	x = 50;
	y = 200;
	dir = 0;
	size = 1.0f;
	ani_counter = 0;
 	ani_count_max = 30;
	//�d��
	jump = false;
	hit_counter = 0;
	is_hit = false;

	wall_x = 100;
	wall0_x = 0.0f;
	rota = 0.0f;
	is_landing = false;

	_hitpoint = 3;

	_combo = 0;
}

Player::~Player() {
	for (int i = 0; i < PLAYER_IMAGE_MAX; i++) {

		DeleteGraph(player_image[i]);
	}

}
//---------------------------------
//�L�����ʒu�ݒ�
//----------------------------------
void Player::SetPlayerPos(float x, float y) {
	player.x = x;
	player.y = y;
}
//--------------------------------
//�d�͐ݒ�
//--------------------------------
void Player::SetGravity() {
	//�d��	
	v += gravity;
	y -= v;
}
//-------------------------------
//�ǂƓV��Ə�
//-------------------------------
void Player::SetOverWindow() {

	//�n��
	if (y >= 200) y = 200;
	//�V��
	if (y < 0)y = 0;
	//��
	if (x <= 30)x = 30;
	if (x >= 610)x = 610;

}
//-------------------------------
//�W�����v
//--------------------------------
void Player::Jump() {
	
	if (scene == GAME) {
		if (GetJoypadNum() == 0) {
			if (IsKeyOn(KEY_INPUT_SPACE)) {
				if (jump == false)
				{
					//v=6.0f;
					v = 7.5f;
					sound.PlayJump1();
					jump = true;
				}
			}
		}

		//�W���C�p�b�h
		if (GetJoypadInputState(DX_INPUT_PAD1) & (PAD_INPUT_1)){
			//if (_before_A == false) {
			if ((_before_BIT & PAD_INPUT_1) == false) {
				if (jump == false)
				{
					v = 7.5f;
					sound.PlayJump1();
					jump = true;
				}
			}

		}
		
		


	}
}



//------------------------------------------------------
//�W�����v���ɉ�]
//------------------------------------------------------
void Player::Spin() {
	if (jump == true) {
		if (rota <6.25f) {
			rota +=0.25f;
		}
		if (rota <12.5f) {
			//rota += 0.5f;
		}
	}
	else {
		rota = 0;
	}
}
//--------------------------------------------------
//������ʂƃh�A���J���Ă��Ȃ����̂ݑO������
//--------------------------------------------------
void Player::SetPlayerDir() {
	if (title.door_check == false && scene == SELECT) dir = 0;
}
//---------------------------------------------------
//�A�j���[�V�����p�̃J�E���^�[��30�ɂȂ�܂�++
//30�ɂȂ����烊�Z�b�g
//-----------------------------------------------------
void Player::ResetAniCounter() {
	if (scene == GAME||scene==SELECT) {
		ani_counter = (ani_counter + 1) % ani_count_max;
	}
}
//----------------------------------------------
//�v���C���[�ړ�
//---------------------------------------------
void Player::MoveAction() {

	if (scene == SELECT) {
		if (title.door_check == false) {

			//�W���C�p�b�h
			if (GetJoypadInputState(DX_INPUT_PAD1) & (PAD_INPUT_RIGHT)) {

				x += PLAYER_SPEED;
				dir = 1;
			}
			if (GetJoypadInputState(DX_INPUT_PAD1) & (PAD_INPUT_LEFT)) {

				x -= PLAYER_SPEED;
				dir = 2;
			}


			if (GetJoypadNum() != 0)return;


			if (CheckHitKey(KEY_INPUT_RIGHT))
			{
				x += PLAYER_SPEED;
				dir = 1;
			}
			if (CheckHitKey(KEY_INPUT_LEFT))
			{
				x -= PLAYER_SPEED;
				dir = 2;
			}
		}
	}
}
//----------------------------------
//�h�A�ɓ���
//-----------------------------------
void Player::ForInDoor() {

	//�W���C�p�b�h
	if (GetJoypadInputState(DX_INPUT_PAD1) & (PAD_INPUT_UP)) {
		if ((player._before_BIT & PAD_INPUT_DOWN) == false) {
			dir = 3;

		}
	}
	if (title.door_check == true) {
		size -= 0.002f;
	}


	if (GetJoypadNum() != 0)return;

	if (IsKeyOn(KEY_INPUT_UP)) {
		dir = 3;
	}
	if (title.door_check == true) {
		size -= 0.002f;
	}
}

void Player::ResetDoor() {
	if (scene == GAME) {
		size = 1.0f;
		title.door_check = false;
	}
}


//----------------------------------
//���Ԃɍ��킹�ăX�s�[�h�ω�
//----------------------------------
void Player::SetSpeed(float speed)
{
	x += speed;

}
//-------------------------------------------
//�S�`��
//-------------------------------------------
void Player::PlayerRender() {
	if (scene == SELECT) {
	//�v���C���[�̕`��
	if (dir == 0) 	DrawRotaGraph((int)x, (int)y, 1, 0.0f, player_image[1], true, false);
	//�^�C�g����ʈȊO�Ȃ�

	
		//���


		if (dir == 3 && ani_counter <= 9) DrawRotaGraph((int)x, (int)y, size, 0.0f, player_image[10], true, false);
		if (dir == 3 && ani_counter >= 10 && ani_counter <= 19)
			DrawRotaGraph((int)x, (int)y, size, 0.0f, player_image[9], true, false);
		else if (dir == 3 && ani_counter >= 20 && ani_counter <= 30)
			DrawRotaGraph((int)x, (int)y, size, 0.0f, player_image[11], true, false);

		//�E
		if (dir == 1 && ani_counter <= 9) {
			DrawRotaGraph((int)x, (int)y, 1, 0.0f, player_image[7], true, false);
		}

		else if (dir == 1 && ani_counter >= 10 && ani_counter <= 19) {
			DrawRotaGraph((int)x, (int)y, 1, 0.0f, player_image[8], true, false);
		}

		else if (dir == 1 && ani_counter >= 20 && ani_counter <= 30) {
			DrawRotaGraph((int)x, (int)y, 1, 0.0f, player_image[6], true, false);
		}

		//��
		if (dir == 2 && ani_counter <= 9) {
			DrawRotaGraph((int)x, (int)y, 1, 0.0f, player_image[4], true, false);
		}

		else if (dir == 2 && ani_counter >= 10 && ani_counter <= 19) {
			DrawRotaGraph((int)x, (int)y, 1, 0.0f, player_image[5], true, false);
		}

		else if (dir == 2 && ani_counter >= 20 && ani_counter <= 30) {
			DrawRotaGraph((int)x, (int)y, 1, 0.0f, player_image[3], true, false);
		}
	}

}
//------------------------------------------------------
//�A�j���[�V�����p�imap�Ŏg���j
//------------------------------------------------------
//MAX=2,5,8,MIN=10,20,30.MID=4,9,14

void Player::RenderRight(int a, int b, int c) {
	ani_count_max = c;
	//�E
	if (scene == GAME||scene==RESULT) {

			if (dir == 1 && ani_counter <= a) {

				map.ScrollDrawGraph(x, y, 1, rota, player_image_map[0], true);
			}
			else if (dir == 1 && ani_counter >= a && ani_counter <= b) {
				map.ScrollDrawGraph(x, y, 1, rota, player_image_map[1], true);
			}
			else if (dir == 1 && ani_counter >= b && ani_counter <= c) {
				map.ScrollDrawGraph(x, y, 1, rota, player_image_map[2], true);
			}
		
	}
}

//------------------------------------------------------
//�_���[�W�œ_��
//------------------------------------------------------
void Player::Hit_Render() {
	if (is_hit == true) {
		rota = 0;
		if (hit_counter % 3 == 0) {
			player.RenderRight(10, 20, 30);
		}
	}
	if (hit_counter > 60) {
		is_hit = false;
		hit_counter = 0;
	}
}

void Player::AddHitCount() {
	if (is_hit == true) {
		hit_counter++;
	}
}


//------------------------------------------------------
//�O��̕�
//------------------------------------------------------
void Player::SetWall() {
	if (scene == GAME) {
		if (player.x < wall_x - 200) {
			player.x = wall_x - 200;
		}


		if (player.x > wall_x) {
			player.x = wall_x;
		}
	}
}

void Player::AddWallX() {
	if (scene == GAME) {
		if (is_hit == true) {

			wall_x += 0.5f;

		}
		else {
			wall_x += 2.0f;
		}
	}
}
//�ǂ̈ړ����E
void Player::LimitWall() {

	if (scene == GAME) {
		if(wall_x>(wall0_x+200)+map.scl){
			//	wall_x = (wall0_x + 200) + map.scl;

		}
	}
}

//�R���{
void Player::AddCombo() {
	_combo++;
}

void Player::ResetCombo() {
	if (sound.GetC() == 3) {
		_combo = 0;
	}
}



//HP�֌W
//HP����
void Player::DecHitPoint() {
	if (hit_counter == 1) {
		if(is_easy==false)
		_hitpoint--;
	}
}

void Player::GameOver () {
	if (_hitpoint == 0) {
		scene = GAMEOVER;
	}
}

void Player::DrawHP() {


	for (int i = 0; i < _hitpoint; i++) {
		if (is_easy == false&&scene==GAME)
		DrawGraph(0+(30*i), 0, _HP_image, true);
	}

}



void PlayerInit() {

	//�摜�̓ǂݍ���
	LoadDivGraph("data/player/player.png", 12, 3, 4, 32, 32, player_image);
	player_image_map[0] = LoadGraph("data/player/player_right1_map.png");
	player_image_map[1] = LoadGraph("data/player/player_right2_map.png");
	player_image_map[2] = LoadGraph("data/player/player_right3_map.png");
	player.rota_image = LoadGraph("data/player/rolling.png");
	player._HP_image = LoadGraph("data/player/HP.png");
	
	player.old_x = player.GetX();
	player.old_y = player.GetY();

}

void PlayerUpdate() {
	player.SetGravity();
	player.SetPlayerDir();
	player.ResetAniCounter();
	player.AddHitCount();

	player.ResetCombo();
	player.ResetDoor();

	player.Spin();
	player.MoveAction();

	//�n��
	if (scene == TITLE)
	{
		if (player.GetY() >= 200) player.SetY(200);
	}
	if (scene == SELECT) {
		player.SetOverWindow();
		if (check2Pos == true) {
			player.SetPlayerPos(200, 200);
			check2Pos = false;
		}
		//player.MoveAction();-----------------------------------debug
		player.Jump();
		player.ForInDoor();

	}
	player.GameOver();

	

}
void PlayerRender() {
	//DrawLine(player.wall_x - map.scl, 0, player.wall_x - map.scl, 400, GetColor(255, 255, 255));
//	DrawCircle(player.wall0_x, 50, 20, GetColor(255, 0, 255),true);
	player.PlayerRender();
	
	player.DrawHP();

}


