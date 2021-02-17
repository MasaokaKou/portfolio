#include"main.h"
#include"GAME.H"
#include"Result.h"
#include"player.h"
#include"easing.h"
#include"KEYINPUT.H"
#include"Score.h"
#include"sound.h"


Result::Result() {

	_circle.SetPosition( 320, 170 );
	_circle._alpha = 210;

	_px = -30;
	_py = 250;
	_p_anim_counter=0;
	_gravity = -0.2f;
	_is_jump = false;

	_box_x=245;
	_box2_x = 318;
	_box_color = 0;

	_image_alpha = 0;

	_cube1_x = 270;
	_cube1_y = 120;
	_cube2_x = 270+45;
	_cube2_y = 120;
	_cube3_x = 270;
	_cube3_y = 120+45;
	_cube4_x = 270+45;
	_cube4_y = 120+45;
	_cube_color = 0;

	color = GetColor(0, 0, 0);
	_counter = 0;
	
	//���[����
	_t = 0.0f;

	_diffusionCounter = 0;

	_isShowScore = false;
	_isFinishAnimation = false;
}

Result::~Result() {


}

//�摜�ǂݍ���
void Result::Load() {
	_image = LoadGraph("data/result.png");
	_txt_image[0]= LoadGraph("data/result_txt.png");
	_txt_image[1]= LoadGraph("data/result_txt_pad.png");

	//�v���C���[�ǂݍ���
	LoadDivGraph("data/player/player.png", 12, 3, 4, 32, 32, _player_image);
	_rank_image[0]= LoadGraph("data/Rank/S.png");
	_rank_image[1] = LoadGraph("data/Rank/A.png");
	_rank_image[2] = LoadGraph("data/Rank/B.png");
	_rank_image[3] = LoadGraph("data/Rank/C.png");
}

// �X�V
void Result::Update()
{
//	if (_isFinishAnimation) return;

	if (_counter == 1)StopMusic();

	SetGravity();
	// �J�E���^�[���Z
	_counter++;
	
	//�A�j���[�V�����J�E���^�[����
	if (_counter > 750) {
		_p_anim_counter = (_p_anim_counter + 1) % 40;
		MovePlayer();
	}
	//----------------------------------------------
	// �A�j���[�V����
	//----------------------------------------------

	// �~�̔��a���g�債�Ă���
	if (_circle._radius < 370) {
		_circle._radius += 3;
	}

	UpdateMoveWindow();

	UpdateFadeOutColor();

	



	if (_counter > 500) {
		// �S�ẴA�j���[�V��������������
		_isFinishAnimation = true;
	}
	else if (_counter > 300) {
		_isShowScore = true;
	}

	if (_py >= 250) {
		if (_is_jump==false) {
			_v = 0.0f;
		}
		_py = 250;

	}
}

// ��ɕ`��
void Result::PreDraw()
{
	_circle.Draw();
	DrawText();
}

// ��ŕ`��
void Result::PostDraw()
{
	DrawCube();
	DrawPlayer();
	//�W���C�p�b�h���Ȃ����Ă��Ȃ����
	if (GetJoypadNum() == 0) {
		if (_counter > 1000)DrawGraph(470, 260, _txt_image[0], true);
	}
	else {
		if (_counter > 1000)DrawGraph(470, 260, _txt_image[1], true);
	}
	

}

bool Result::IsShowScore() const {
	return _isShowScore;
}

bool Result::IsFinishAnimation() const {
	return _isFinishAnimation;
}



//�E�C���h�E�̓���
void Result::UpdateMoveWindow() {

	//-------------------------------------------------------------
	// �uResult�v���B���Ă���{�b�N�X���J��
	//-------------------------------------------------------------
	if(_counter==200)_box_color =255;
	if (_counter > 200) {
		_box_x -= 6;
		_box2_x += 6;
		_box_color -=5;
		_image_alpha += 5;
	}

	//---- �w��̃J�E���g�������̏ꍇ�͉������Ȃ�
	if (_counter <= 300) return;

	//-------------------------------------------------------------
	// �X�R�A���B���Ă���{�b�N�X���g�U������
	// �g�U���������s
	//-------------------------------------------------------------

	// �g�U�J�E���^�[
	const int DIFFUSION_COUNT_MAX = 180;
	++_diffusionCounter;
	if (_diffusionCounter > DIFFUSION_COUNT_MAX) {
		_diffusionCounter = DIFFUSION_COUNT_MAX;
	}

	// 0.0 ~ 1.0 �ɕϊ�
	float time = _diffusionCounter / (float)DIFFUSION_COUNT_MAX;

	// �C�[�W���O�֐��ŋȐ��p�����[�^�ɕϊ�
	auto easingFunction = getEasingFunction(EaseOutBack);
	float t = easingFunction(time);

	// �g�U�͈�
	const float RANGE = 80.0f;

	// �w��̈ʒu����g�U����v�Z
	const float ADD = RANGE * t;

	// �e��̃L���[�u�̍��W�v�Z���s��
	_cube1_x = -ADD + 270;
	_cube1_y = -ADD + 120;

	_cube2_x = +ADD + (270 + 45);
	_cube2_y = -ADD + 120;

	_cube3_x = -ADD + 270;
	_cube3_y = +ADD + (120 + 45);

	_cube4_x = +ADD + (270 + 45);
	_cube4_y = +ADD + (120 + 45);

	// �A���t�@�l�v�Z
	_cube_color = 255 - (int)(255 * t);

#if 0
	_cube1_x--;
	_cube1_y--;
	_cube2_x++;
	_cube2_y--;
	_cube3_x--;
	_cube3_y++;
	_cube4_x++;
	_cube4_y++;
#endif
}

//��莞�Ԃ�����������Ă���
void Result::UpdateFadeOutColor() {
#if 0
	if (_cube_color == 0) return;
	if (_counter <= 300) return;

	_cube_color -= 2;
	if (_cube_color < 0) {
		_cube_color = 0;
	}
	//_cube_color = max( _cube_color - 2, 0 );
#endif
}


//�e�L�X�g�摜�`��
void Result::DrawText() {
	if (_counter <= 130) return;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _image_alpha);
	DrawGraph(245, 40, _image, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _box_color);
	DrawBox(_box_x, 40, _box_x + 73, 40 + 50, GetColor(255, 255, 255), true);
	DrawBox(_box2_x, 40, _box2_x + 73, 40 + 50, GetColor(255, 255, 255), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Result::DrawCube() {
	if (_counter <= 130) return;

	// �A���t�@�u�����h�J�n
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _cube_color);
	{
		DrawBox(_cube1_x, _cube1_y, _cube1_x + 45, _cube1_y + 45, GetColor(255, 0, 0), true);
		DrawBox(_cube2_x, _cube2_y, _cube2_x + 45, _cube2_y + 45, GetColor(255, 0, 0), true);
		DrawBox(_cube3_x, _cube3_y, _cube3_x + 45, _cube3_y + 45, GetColor(255, 0, 0), true);
		DrawBox(_cube4_x, _cube4_y, _cube4_x + 45, _cube4_y + 45, GetColor(255, 0, 0), true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}


//�v���C���[�`��
void Result::DrawPlayer() {
	if (player.GetDir() == 0) DrawGraph(_px, _py, _player_image[6], true);
	if (player.GetDir() == 1 && _p_anim_counter <= 9) { DrawGraph(_px, _py, _player_image[1], true); }
	else if(player.GetDir()==1 && _p_anim_counter >= 10 && _p_anim_counter <= 19) { DrawGraph(_px, _py, _player_image[7], true); }
	else if (player.GetDir() == 1 && _p_anim_counter >= 20 && _p_anim_counter <= 29) { DrawGraph(_px, _py, _player_image[10], true); }
	else if (player.GetDir() == 1 && _p_anim_counter >= 30 && _p_anim_counter <= 40) { DrawGraph(_px, _py, _player_image[4], true); }
}

//�v���C���[�̓���
void Result::MovePlayer() {
	if (_py >= 250) {
		_is_jump = true;
	}
	if (_py <= 245) {
		_is_jump = false;
	}
	if (_is_jump == true) {
		_v = 6.0f;
	}
	if (_px >= 660) {
		_px = -30;
	}
	_px += 2;
}

//�d��
void Result::SetGravity() {
	//�d��	
	_v += _gravity;
	_py -=_v;
}

//���U���g��ʂ��烉���L���O��
void Result::EndGame() {

	//�W���C�p�b�h
	if (GetJoypadInputState(DX_INPUT_PAD1) & (PAD_INPUT_2)) {

		if ((player._before_BIT & PAD_INPUT_2) == false) {
			if (scene == RESULT)
			{
				scene = RANKING;
			}
		
		}
	
	}



	if (GetJoypadNum() != 0)return;
	if (IsKeyOn(KEY_INPUT_RETURN)) {
		if (scene == RESULT)
		{
			scene = RANKING;
		}
	}
}

//���U���g�ϐ��̏�����
void Result::ReSetGame() {
	if (scene == SELECT) {
		_px = -30;
		_py = 250;
		_p_anim_counter = 0;

		_box_x = 245;
		_box2_x = 318;

		_cube1_x = 270;
		_cube1_y = 120;
		_cube2_x = 270 + 45;
		_cube2_y = 120;
		_cube3_x = 270;
		_cube3_y = 120 + 45;
		_cube4_x = 270 + 45;
		_cube4_y = 120 + 45;
		_t = 0.0f;
		_diffusionCounter = 0;

		_isShowScore = false;
		_isFinishAnimation = false;

		_circle.SetPosition(320, 170);
		_circle._alpha = 210;
		
		_box_color = 0;
		_image_alpha = 0;

		_counter = 0;
		_circle._radius = 0.0f;

	}


}


void Result::ShowRank( Score *score) {
	if (scene == RESULT) {
		if (_counter == 910) {
			sound.Rank();

		}

		if (_counter > 900) {
			if (score->GetScore() >= 12000  && all_coin == 3)
			{
				DrawGraph(400, 50, _rank_image[0], true);
			}
			else if (score->GetScore() >= 10000 && all_coin >= 2)
			{
				DrawGraph(400, 50, _rank_image[1], true);
			}
			else if (score->GetScore() >= 7000 <= 50 && all_coin >= 1)
			{
				DrawGraph(400, 50, _rank_image[2], true);
			}
			else if (score->GetScore() <= 7000 &&score->GetTime() >= 65 && all_coin == 0)
			{
				DrawGraph(400, 50, _rank_image[3], true);
			}
		
		}
	}

}