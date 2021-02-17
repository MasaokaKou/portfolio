//---------------------------------------------------------------------------
//!	@file	sceneTest3.cpp
//!	@brief	enemy�̓����蔻��̓����̎���
//---------------------------------------------------------------------------

//===========================================================================
//! �G�l�~�[
//===========================================================================

//---------------------------------------------------------------------------
//! �R���X�g���N�^
//---------------------------------------------------------------------------
SceneGameTest3 ::SceneGameTest3()
{
    _pos    = VGet(0, 0, 0);   //! �ʒu���W
    _oldPos = VGet(0, 0, 0);
    _dir    = TO_RADIAN(180.0f) * 0;
    _size   = 5;   //! �}�`�`��̍ۂ̃T�C�Y

    par._hp     = 0;      //! �ϋv�l
    par._atk    = 0;      //! �U����
    par._def    = 0;      //! �ϋv��
    par._movSpd = 0.1f;   //! �i�R���x
    par._atkSpd = 0;      //! �U�����x

    _state = STATE::MOVE;   //! ���݂̏��

    _targetPos = VGet(0, 0, 0);   //! �������{��

    //! �����蔻��p�̕ϐ�
    _hcPos   = VGet(_pos.x, _pos.y, _pos.z + 5);   //! ���݈ʒu
    _hcScale = 5;                                  //! �T�C�Y
    _hcSpace = 10;                                  //! �Ԋu

    //! ���f��
    _model = std::make_unique<Model>();   //! ���ԍ쐬

    //! �s��
    _matRot = MGetIdent();                            //! �P�ʍs����擾
    _matRot = MGetScale(VGet(_size, _size, _size));   //! �T�C�Y�w��
}

//---------------------------------------------------------------------------
//! �f�X�g���N�^
//---------------------------------------------------------------------------
SceneGameTest3 ::~SceneGameTest3()
{
}

//---------------------------------------------------------------------------
//! ������
//---------------------------------------------------------------------------
bool SceneGameTest3::initialize()
{
    //! ���f���̓ǂݍ���
    _model.get()->load("data/sphereDebug.mqo");
    //! ���f���̏������W�ݒ�(�}�g���b�N�X�ݒ�)
    MV1SetMatrix(_model.get()->handle(), _matRot);

    return true;
}

//---------------------------------------------------------------------------
//! �X�V
//---------------------------------------------------------------------------
void SceneGameTest3::update()
{
    switch(_state) {
        case STATE::WAIT:
            break;
        case STATE::MOVE:

            //! �����蔻��m���߂邽��
            search(VGet(0, 0, 0), VGet(0, 0, 0));

            //! �ړ�
            move(_targetPos);

            //! �����蔻��̓���
            movHit();

            break;
        case STATE::ATTACK:
            break;
        case STATE::DEATH:
            break;
        default:
            break;
    }
}
//---------------------------------------------------------------------------
//! �`��
//---------------------------------------------------------------------------
void SceneGameTest3::render()
{
    _model.get()->draw();

    switch(_state) {
        case STATE::WAIT:
            break;
        case STATE::MOVE:
            break;
        case STATE::ATTACK:
            break;
        case STATE::DEATH:
            break;
        default:
            break;
    }

#ifdef _DEBUG
#if 1

    //! �����蔻��p�̋�
    DrawSphere3D(_hcPos, _hcScale, 5, WHITE, WHITE, false);

    //! ���W�`��
    DrawString(0, 20, "PosX", WHITE);
    chengeText((s16)_pos.x, 50, 20, 255, 255, 255);
    DrawString(0, 40, "PosZ", WHITE);
    chengeText((s16)_pos.z, 50, 40, 255, 255, 255);

    //! �X�e�[�^�X�`��
    switch(_state) {
        case STATE::WAIT:
            DrawString(0, 60, "STATE:", WHITE);
            DrawString(55, 60, "WAIT", WHITE);
            break;
        case STATE::MOVE:
            DrawString(0, 60, "STATE:", WHITE);
            DrawString(55, 60, "MOVE", WHITE);
            break;
        case STATE::ATTACK:
            DrawString(0, 60, "STATE:", WHITE);
            DrawString(55, 60, "ATTACK", WHITE);
            break;
        case STATE::DEATH:
            DrawString(0, 60, "STATE:", WHITE);
            DrawString(55, 60, "DEATH", WHITE);
            break;
        default:
            break;
    }

#endif   // 0

#endif   // _DEBUG
}

//---------------------------------------------------------------------------
//! ���
//---------------------------------------------------------------------------
void SceneGameTest3::finalize()
{
}

//---------------------------------------------------------------------------
//! ���G�p�����蔻��
//---------------------------------------------------------------------------
bool SceneGameTest3::hit(VECTOR& p0, f32 r0, VECTOR& p1, f32 r1)
{
    VECTOR v;
    // p0����p1�������ĉ~���m�̋������o��
    v = VSub(p0, p1);

    // ����p
    f32 length = sqrtf(v.x * v.x + v.z * v.z);

    //  �ŏ��ɏo���������Ɠ�̔��a�𑫂������̂��ׂ�
    if(length < r0 + r1) {
        //�@p0����p1�������ĉ~���m�̋������̂ق������������true
        return true;
    }

    return false;
}

//---------------------------------------------------------------------------
//! ���G(taskManager�ōX�V)
//---------------------------------------------------------------------------
void SceneGameTest3::search(VECTOR& fc_pos, VECTOR& main_fc_pos)
{
    //!(��)
    VECTOR pos  = VGet(20, 0, -30);
    f32    size = 5;

    DrawSphere3D(pos, size, 5, BLACK, BLACK, false);

    _targetPos = pos;

    // if(hit(_hcPos, _hcScale, pos, size)) {
    //     //! ���G�͈͂ɖh�q�{�݂�����΂�����
    //     _targetPos = fc_pos;
    //
    //     DrawString(0, 80, "IsHit:", WHITE);
    //     DrawString(55, 80, "TRUE", WHITE);
    // }
    // else {
    //     //! ������Ζ{���n�֌�����
    //     _targetPos = main_fc_pos;
    //     DrawString(0, 80, "IsHit:", WHITE);
    //     DrawString(55, 80, "FALSE", WHITE);
    // }
}

//---------------------------------------------------------------------------
//! �ړ�
//!���G���Ĕ͈͓��Ɏ{�݂��������炻�̍��W��ړI�n�ɂ��Ĉړ�
//---------------------------------------------------------------------------
void SceneGameTest3::move(VECTOR& fc_pos)
{
    //! enemy����v���C���[�̕����x�N�g���쐬
    VECTOR dir;

    //! enemy�̍��W����h�q�{�݂̍��W������
    dir = VSub(fc_pos, _pos);

    // ���K��
    dir = VNorm(dir);

    //! ���K�������x�N�g���ɑ��x��������
    dir = VScale(dir, par._movSpd);

    // //! enemy�̍��W�ɐ��K�����������x�N�g���𑫂�
    _pos = VAdd(_pos, dir);

#ifdef _DEBUG

    if(CheckHitKey(KEY_INPUT_LEFT))
        _dir += 0.1f;
    if(CheckHitKey(KEY_INPUT_RIGHT))
        _dir -= 0.1f;

    if(CheckHitKey(KEY_INPUT_UP)) {
        _pos.x += par._movSpd * cosf(_dir);
        _pos.z += par._movSpd * sinf(_dir);
    }

#endif   // _DEBUG

    //! �����]��
    direction(fc_pos);

    //! ��t���[���O�̍��W
    _oldPos = VGet(_pos.x, _pos.y, _pos.z);
}

//---------------------------------------------------------------------------
//! �����]��
//---------------------------------------------------------------------------
void SceneGameTest3::direction(VECTOR& fc_pos)
{
    //! enemy����v���C���[�̕����x�N�g���쐬
    VECTOR dir;

    //! enemy�̍��W����h�q�{�݂̍��W������
    dir = VSub(fc_pos, _pos);

    // ���K��
    dir = VNorm(dir);

    // enemy�̉E�����̃x�N�g�����쐬
    // �E�����Ȃ̂�90.0��
    float side_rot = _dir + TO_RADIAN(180.0f);

    _side.x += cosf(side_rot);
    _side.z -= sinf(side_rot);

    //! ���K��
    _side = VNorm(_side);

    //! �Q�̃x�N�g���̓��ς��擾
    //! (enemy����v���C���[�̕����x�N�g���쐬 , enemy�̉E�����̃x�N�g�����쐬)
    float side_dot = VDot(_side, dir);

    // ���ς̒l���v���X���}�C�i�X�ŉ�]���������߂�
    if(side_dot > 0.0f) {
        _dir += TO_RADIAN(1.0f);
    }
    // ���ς̒l���}�C�i�X�̎���
    if(side_dot < 0.0f) {
        _dir -= TO_RADIAN(1.0f);
    }

    //! �}�g���b�N�X���g�������f���̉�]
    _matRot = MGetRotY(_dir);
    //! MGetRotY�łȂ���scale��1�ɂȂ�̂ŋ����ύX
    _matRot = MScale(_matRot, _size);

    //! �}�g���b�N�X�̍��W�Ɍ��݈ʒu������
    _matRot.m[3][0] = _pos.x;
    _matRot.m[3][2] = _pos.z;

    //! �}�g���b�N�X�ݒ�
    MV1SetMatrix(_model.get()->handle(), _matRot);
}

//---------------------------------------------------------------------------
//! �����蔻��̓���
//---------------------------------------------------------------------------
void SceneGameTest3::movHit()
{
    //! �}�g���b�N�X��Z���
    VECTOR vec = VGet(_matRot.m[2][0], _matRot.m[2][1], _matRot.m[2][2]);

    //! ���K��
    vec = VNorm(vec);

    //!  �Ԋu��������
    mulVec(vec, _hcSpace);
    //

    //!  Z�����Ɣ��΂ɂȂ�̂Ŕ��]������
    mulVec(vec, -1.0f);

    //! enemy�̃|�W�V�����ƃ}�g���b�N�X��Z���𑫂�
    _hcPos = VAdd(_pos, vec);

#ifdef _DEBUG
#if 1
    // _motRotrix �̒l����ʂɕ\��
    DrawString(0, 300, "�x����]�s��", GetColor(255, 255, 255));
    DrawFormatString(0, 16 + 300, GetColor(255, 255, 255), "m00 %f  m01 %f  m02 %f  m03 %f",
                     _matRot.m[0][0], _matRot.m[0][1], _matRot.m[0][2], _matRot.m[0][3]);

    DrawFormatString(0, 32 + 300, GetColor(255, 255, 255), "m10 %f  m11 %f  m12 %f  m13 %f",
                     _matRot.m[1][0], _matRot.m[1][1], _matRot.m[1][2], _matRot.m[1][3]);

    DrawFormatString(0, 48 + 300, GetColor(255, 255, 255), "m20 %f  m21 %f  m22 %f  m23 %f",
                     _matRot.m[2][0], _matRot.m[2][1], _matRot.m[2][2], _matRot.m[2][3]);

    DrawFormatString(0, 64 + 300, GetColor(255, 255, 255), "m30 %f  m31 %f  m32 %f  m33 %f",
                     _matRot.m[3][0], _matRot.m[3][1], _matRot.m[3][2], _matRot.m[3][3]);

    DrawString(0, 80, "dir", WHITE);
    chengeTextF(_dir, 50, 80, 255, 255, 255);





#endif   // 0
#endif   // _DEBUG
}
