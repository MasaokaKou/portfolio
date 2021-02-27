//---------------------------------------------------------------------------
//!	@file	unitTypeB.cpp
//!	@brief	UnitTypeB�̎���
//---------------------------------------------------------------------------
#include "unitTypeB.h"

//---------------------------------------------------------------------------
//! �R���X�g���N�^
//---------------------------------------------------------------------------
UnitTypeB::UnitTypeB()
{
    // ���j�b�g�̎��
    _type = TYPE::TYPE_B;
    _pos  = VGet(0, 0, 0);   // �ʒu���W
    //_size = 0.04f;           // �}�`�`��̍ۂ̃T�C�Y

    _HP         = 5;
    par._hp     = _HP;    // �ϋv�l
    par._atk    = 2;      // �U����
    par._def    = 0;      // �ϋv��
    par._movSpd = 0.4f;   // �i�R���x
    par._atkSpd = 60;     //�U�����x(_atkSpd �t���[���Ɉ�x)

    // �����蔻��p�̕ϐ�(���G)
    _hit._hcPos   = VGet(_pos.x, _pos.y, _pos.z);   // ���݈ʒu
    _hit._hcScale = 40;                             // �T�C�Y
    _hit._hcSpace = 0;                              // �Ԋu

    // �����蔻��p�̕ϐ�(�U��)
    _hitAtk._hcPos = VGet(_pos.x, _pos.y, _pos.z);   // ���݈ʒu
    //_hitAtk._hcScale = 1;                              // �T�C�Y
    //_hitAtk._hcSpace = 500;
    _hitAtk._hcScale = 20;
    _hitAtk._hcSpace = 0;

    // �������U���̃��f���i�E�j�j
    _model = std::make_unique<Model>();   // ���ԍ쐬

    // �s��
    _mat = MGetIdent();                         // �P�ʍs����擾
    _mat = MGetScale(VGet(0.01, 0.01, 0.01));   // �T�C�Y�w��

    _mat.m[3][1] = 2;
}

//---------------------------------------------------------------------------
//! �f�X�g���N�^
//---------------------------------------------------------------------------
UnitTypeB::~UnitTypeB()
{
}

//---------------------------------------------------------------------------
//! ������
//---------------------------------------------------------------------------
bool UnitTypeB::initialize()
{
    UnitBase::initialize("data/Unit/Unit.mqo", "data/Unit/unitTypeB.png");

    _model.get()->load("data/Unit/uni.mqo");

    return true;
}

//---------------------------------------------------------------------------
//! �X�V
//---------------------------------------------------------------------------
void UnitTypeB::update()
{
    UnitBase::update();

    if((_state == STATE::WAIT || _state == STATE::MOVE)) {
        //! �}�g���b�N�X�̍��W�Ɍ��݈ʒu������
        _mat.m[3][0] = _pos.x;
        _mat.m[3][2] = _pos.z;
    }

    if(_mat.m[3][1] <= 7.0f) {
        _mat.m[3][1] += 0.05f;
    }

    //! �}�g���b�N�X�ݒ�
    MV1SetMatrix(_model.get()->handle(), _mat);
}
//---------------------------------------------------------------------------
//! �`��
//---------------------------------------------------------------------------
void UnitTypeB::render()
{
    _model.get()->draw();
    UnitBase::render();
}

//---------------------------------------------------------------------------
//! ���
//---------------------------------------------------------------------------
void UnitTypeB::finalize()
{
    UnitBase::finalize();
}

//---------------------------------------------------------------------------
//! ����������̓���
//---------------------------------------------------------------------------
void UnitTypeB::atkMove(VECTOR fac_pos_, f32 fac_size_, STATE state_)
{
    if(_state != STATE::ATTACK) {
        return;
    }

    //! ���킩��U���p�����蔻��ւ̃x�N�g���쐬
    VECTOR dir;

    //! ���G�͈͂ɓ����Ă�G��
    if(UnitBase::search(fac_pos_, fac_size_, state_)) {
        //! ���f���̍��W����U���p�����蔻��̍��W������
        dir = VSub(fac_pos_, VGet(_mat.m[3][0], _mat.m[3][1], _mat.m[3][2]));

        // ���K��
        dir = VNorm(dir);

        //! ���K�������x�N�g���ɑ��x��������
        dir = VScale(dir, 1);

        //! Unit�̍��W�ɐ��K�����������x�N�g���𑫂�
        //_model_pos = VAdd(_pos, dir);
        _mat.m[3][0] = _mat.m[3][0] + dir.x;
        _mat.m[3][2] = _mat.m[3][2] + dir.z;

        if(dir.x <= 0.01f && dir.x >= -0.01f) {
            _mat.m[3][0] = _pos.x;
            _mat.m[3][1] = 8;
            _mat.m[3][2] = _pos.z;
        }
    }
}
