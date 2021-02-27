//---------------------------------------------------------------------------
//!	@file	unitTypeB.cpp
//!	@brief	UnitTypeB�̎���
//---------------------------------------------------------------------------
#include "unitTypeC.h"

//---------------------------------------------------------------------------
//! �R���X�g���N�^
//---------------------------------------------------------------------------
UnitTypeC::UnitTypeC()
{
    // ���j�b�g�̎��
    _type = TYPE::TYPE_C;
    _pos  = VGet(0, 0, 0);   // �ʒu���W
                             // _size = 0.04f;           // �}�`�`��̍ۂ̃T�C�Y
    _HP         = 40;
    par._hp     = _HP;    // �ϋv�l
    par._atk    = 1;      // �U����
    par._def    = 0;      // �ϋv��
    par._movSpd = 0.1f;   // �i�R���x
    par._atkSpd = 150;     //�U�����x(_atkSpd �t���[���Ɉ�x)

    // �����蔻��p�̕ϐ�(���G)
    _hit._hcPos   = VGet(_pos.x, _pos.y, _pos.z);   // ���݈ʒu
    _hit._hcScale = 20;                             // �T�C�Y
    _hit._hcSpace = 0;                              // �Ԋu

    // �����蔻��p�̕ϐ�(�U��)
    _hitAtk._hcPos   = VGet(_pos.x, _pos.y, _pos.z);   // ���݈ʒu
    //_hitAtk._hcScale = 1;                              // �T�C�Y
    //_hitAtk._hcSpace = 200;
    _hitAtk._hcScale = 10;
    _hitAtk._hcSpace = 0;


    // ���f���i�J���j
    _model = std::make_unique<Model>();   // ���ԍ쐬

    // �s��
    _mat = MGetIdent();                            // �P�ʍs����擾
    _mat = MGetScale(VGet(0.07f, 0.07f, 0.07f));   // �T�C�Y�w��

    _modelDead = false;
    _alpha     = 255;

    // �J���̃��f���̓����悤�^�C�}�[
    _dead_timer = 20;
}

//---------------------------------------------------------------------------
//! �f�X�g���N�^
//---------------------------------------------------------------------------
UnitTypeC::~UnitTypeC()
{
}

//---------------------------------------------------------------------------
//! ������
//---------------------------------------------------------------------------
bool UnitTypeC::initialize()
{
    SetUseTransColor(FALSE);
    UnitBase::initialize("data/Unit/Unit.mqo", "data/Unit/unitTypeC.png");
    _model.get()->load("data/Unit/kame.mqo");
    //! ���f���̏������W�ݒ�(�}�g���b�N�X�ݒ�)
    MV1SetMatrix(_model.get()->handle(), _mat);
    _graphHandle = LoadGraph("data/Unit/kame2.png");

    return true;
}
//---------------------------------------------------------------------------
//! �X�V
//---------------------------------------------------------------------------
void UnitTypeC::update()
{
    UnitBase::update();

    if((_state == STATE::MOVE)) {
        //! �}�g���b�N�X�̍��W�Ɍ��݈ʒu������
        _mat.m[3][0] = _pos.x;
        _mat.m[3][1] = 0;
        _mat.m[3][2] = _pos.z;
    }

    _pos.y = 7;
    modelMove();
    modelDead();

    MV1SetTextureGraphHandle(_model.get()->handle(), 0, _graphHandle, false);

    MV1SetUseVertDifColor(_model.get()->handle(), true);
    MV1SetUseVertSpcColor(_model.get()->handle(), true);

    //! �}�g���b�N�X�ݒ�
    MV1SetMatrix(_model.get()->handle(), _mat);
}
//---------------------------------------------------------------------------
//! �`��
//---------------------------------------------------------------------------
void UnitTypeC::render()
{
    _model.get()->draw();
    UnitBase::render();
}

//---------------------------------------------------------------------------
//! ���
//---------------------------------------------------------------------------
void UnitTypeC::finalize()
{
    UnitBase::finalize();
}

//---------------------------------------------------------------------------
//! ���f�����̂��̂̓���
//---------------------------------------------------------------------------
void UnitTypeC::modelMove()
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
    _mat = MScale(_mat, _size);

    //! �}�g���b�N�X�̍��W�Ɍ��݈ʒu������
    _mat.m[3][0] = _pos.x;

    _mat.m[3][2] = _pos.z;
}

//---------------------------------------------------------------------------
//! ���f���̏��Ń��[�V����
//---------------------------------------------------------------------------
void UnitTypeC::modelDead()
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

    //! �Q�̃x�N�g���̓��ς��擾

    //! �}�g���b�N�X���g�������f���̉�]
    _mat = MGetRotY(_dir);
    //! MGetRotY�łȂ���scale��1�ɂȂ�̂ŋ����ύX
    _mat = MScale(_mat, _size);

    //! �}�g���b�N�X�̍��W�Ɍ��݈ʒu������
    _mat.m[3][0] = _pos.x;

    _mat.m[3][2] = _pos.z;

    //! �����]��
    direction(dir);

    // //! Unit�̍��W�ɐ��K�����������x�N�g���𑫂�
    _pos = VAdd(_pos, dir);

    if(_pos.x <= -140) {
        _modelDead = true;
    }
}
//---------------------------------------------------------------------------
//! ���f���̕����]��
//---------------------------------------------------------------------------
void UnitTypeC::direction(VECTOR dir_)
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
