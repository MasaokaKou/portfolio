//---------------------------------------------------------------------------
//!	@file	unitTypeD.cpp
//!	@brief	UnitTypeD�̎���
//---------------------------------------------------------------------------
#include "unitTypeD.h"

//---------------------------------------------------------------------------
//! �R���X�g���N�^
//---------------------------------------------------------------------------
UnitTypeD::UnitTypeD()
{
    //! ���j�b�g�̎��
    _type = TYPE::TYPE_D;
    _pos  = VGet(0, 10, 0);   //! �ʒu���W
    //_size = 0.03f;            //! �}�`�`��̍ۂ̃T�C�Y

    _HP         = 6;
    par._hp     = _HP;    //! �ϋv�l
    par._atk    = -5;     //! �U����
    par._def    = 0;      //! �ϋv��
    par._movSpd = 0.2f;   //! �i�R���x
    par._atkSpd = 240;    //!�U�����x(_atkSpd �t���[���Ɉ�x)

    //! �����蔻��p�̕ϐ�(���G)
    _hit._hcPos   = VGet(_pos.x, _pos.y, _pos.z);   //! ���݈ʒu
    _hit._hcScale = 50;                             //! �T�C�Y
    _hit._hcSpace = 0;                              //! �Ԋu

    //! �����蔻��p�̕ϐ�(�U��)
    _hitAtk._hcPos   = VGet(_pos.x, _pos.y, _pos.z);   //! ���݈ʒu
    _hitAtk._hcScale = 20;                             //! �T�C�Y
    _hitAtk._hcSpace = 1;

    //! ��蕨�̃��f���i�N���I�l�j
    _ride_model = std::make_unique<Model>();   //! ���ԍ쐬
    //! �U���p�̃��f��
    _atk_circle = std::make_unique<Model>();   //! ���ԍ쐬
    _atk_alpha  = 0;
    _atk_scale  = 0.01f;

    //! �s��
    _mat       = MGetIdent();                         //! �P�ʍs����擾
    _mat       = MGetScale(VGet(1.8f, 1.8f, 1.8f));   //! �T�C�Y�w��
    _modelDead = false;

    //! �J���̃��f���̓����悤�^�C�}�[
    _dead_timer = 20;
}

//---------------------------------------------------------------------------
//! �f�X�g���N�^
//---------------------------------------------------------------------------
UnitTypeD::~UnitTypeD()
{
}

//---------------------------------------------------------------------------
//! ������
//---------------------------------------------------------------------------
bool UnitTypeD::initialize()
{
    SetUseTransColor(FALSE);
    UnitBase::initialize("data/Unit/Unit.mqo", "data/Unit/unitTypeD.png");
    _ride_model->load("data/Unit/kurione.mqo");
    _atk_circle->load("data/Unit/unitTypeD-Atk.mqo");

    //! ���f���̏������W�ݒ�(�}�g���b�N�X�ݒ�)
    MV1SetMatrix(_ride_model->handle(), _mat);
    // _graphHandle = LoadGraph("data/kurione.png");
    _graphHandle = LoadGraph("data/Unit/kuro.png");

    return true;
}
//---------------------------------------------------------------------------
//! �X�V
//---------------------------------------------------------------------------
void UnitTypeD::update()
{
    UnitBase::update();

    //MV1SetTextureGraphHandle(_ride_model.get()->handle(), 0, _graphHandle, false);

    if((_state == STATE::MOVE)) {
        //! �}�g���b�N�X�̍��W�Ɍ��݈ʒu������
        _mat.m[3][0] = _pos.x;
        _mat.m[3][1] = -5;
        _mat.m[3][2] = _pos.z;
    }

    if((_state == STATE::ATTACK)) {
        _hitAtk._hcScale = 40;
    }

    else {
        _hitAtk._hcScale = 20;
    }
    _pos.y = 10;

    modelMove();
    modelDead();

    MV1SetUseVertDifColor(_ride_model->handle(), true);
    MV1SetUseVertSpcColor(_ride_model->handle(), true);

    //! �񕜃��[�V�����X�V
    atkAnimUpdate();

    //! �}�g���b�N�X�ݒ�
    MV1SetMatrix(_ride_model->handle(), _mat);
}
//---------------------------------------------------------------------------
//! �`��
//---------------------------------------------------------------------------
void UnitTypeD::render()
{
    _ride_model->draw();

    UnitBase::render();
    //! �񕜃��[�V�����`��
    atkAnimDraw();
}

//---------------------------------------------------------------------------
//! ���
//---------------------------------------------------------------------------
void UnitTypeD::finalize()
{
    UnitBase::finalize();
}

//---------------------------------------------------------------------------
//! ���f���̏��Ń��[�V����
//---------------------------------------------------------------------------
void UnitTypeD::modelMove()
{
    if(isDead())
        return;

    //! ���f������U���p�����蔻��ւ̃x�N�g���쐬
    VECTOR dir;

    //! ���f���̍��W����U���p�����蔻��̍��W������
    dir = VSub(_hitAtk._hcPos, VGet(_mat.m[3][0], _mat.m[3][1], _mat.m[3][2]));

    // ���K��
    dir = VNorm(dir);

    // Unit�̉E�����̃x�N�g�����쐬
    // �E�����Ȃ̂�90.0��
    float side_rot = _dir + TO_RADIAN(180.0f);

    _side.x += cosf(side_rot);
    _side.z -= sinf(side_rot);

    //! ���K��
    _side = VNorm(_side);

    //! �Q�̃x�N�g���̓��ς��擾
    //! (Unit����v���C���[�̕����x�N�g���쐬 , Unit�̉E�����̃x�N�g�����쐬)
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
    _mat = MGetRotY(_dir);
    //! MGetRotY�łȂ���scale��1�ɂȂ�̂ŋ����ύX
    _mat = MScale(_mat, 0.1f);
    //_mat = MScale(_mat, 1);
    //! �}�g���b�N�X�̍��W�Ɍ��݈ʒu������
    _mat.m[3][0] = _pos.x;
    _mat.m[3][1] = -5;
    _mat.m[3][2] = _pos.z;
}

//---------------------------------------------------------------------------
//! ���f���̏��Ń��[�V����
//---------------------------------------------------------------------------
void UnitTypeD::modelDead()
{
    if(!isDead())
        return;

    //! ���f������U���p�����蔻��ւ̃x�N�g���쐬
    VECTOR dir;

    //! ���f���̍��W����U���p�����蔻��̍��W������
    dir = VSub(VGet(-150, 0, -150), VGet(_mat.m[3][0], _mat.m[3][1], _mat.m[3][2]));
    // ���K��
    dir = VNorm(dir);

    // Unit�̉E�����̃x�N�g�����쐬
    // �E�����Ȃ̂�90.0��
    float side_rot = _dir + TO_RADIAN(180.0f);

    _side.x += cosf(side_rot);
    _side.z -= sinf(side_rot);

    //! ���K��
    _side = VNorm(_side);

    direction(dir);

    //! �}�g���b�N�X���g�������f���̉�]
    _mat = MGetRotY(_dir);
    //! MGetRotY�łȂ���scale��1�ɂȂ�̂ŋ����ύX
    //  _mat = MScale(_mat, _size);
    _mat = MScale(_mat, 0.1f);
    //! �}�g���b�N�X�̍��W�Ɍ��݈ʒu������
    _mat.m[3][0] = _pos.x;

    _mat.m[3][2] = _pos.z;

    // //! Unit�̍��W�ɐ��K�����������x�N�g���𑫂�
    _pos = VAdd(_pos, dir);

    if(_pos.x <= -140) {
        _modelDead = true;
    }
}
//---------------------------------------------------------------------------
//! ���f���̕����]��
//---------------------------------------------------------------------------
void UnitTypeD::direction(VECTOR dir_)
{
    // ���ς̒l���v���X���}�C�i�X�ŉ�]���������߂�
    //! (Unit����v���C���[�̕����x�N�g���쐬 , Unit�̉E�����̃x�N�g�����쐬)
    float side_dot = VDot(_side, dir_);

    if(_dead_timer < 0) {
        return;
    }

    if(side_dot > 0.0f) {
        _dir += TO_RADIAN(10.0f);
    }
    // ���ς̒l���}�C�i�X�̎���
    if(side_dot < 0.0f) {
        _dir -= TO_RADIAN(10.0f);
    }

    _dead_timer--;
}

//---------------------------------------------------------------------------
//! �񕜃��[�V�����X�V
//---------------------------------------------------------------------------
void UnitTypeD::atkAnimUpdate()
{
    //! �񕜃��[�V�����z�u
    _atk_circle->setScale(VGet(_atk_scale, _atk_scale, _atk_scale));
    _atk_circle->setPos(_pos);

    if(_state != STATE::ATTACK) {
        if(_atk_scale >= 0) {
            _atk_scale -= 0.02f;
        }
    }

    if(_state == STATE::ATTACK) {
        if(_atk_scale <= 0.45f) {
            _atk_scale += 0.02f;
        }
    }
}

//---------------------------------------------------------------------------
//! �񕜃��[�V�����`��
//---------------------------------------------------------------------------
void UnitTypeD::atkAnimDraw()
{
    _atk_circle->draw();
}
