
//---------------------------------------------------------------------------
//!	@file	factoryBase.cpp
//!	@brief	FactoryBase
//---------------------------------------------------------------------------
#include "factoryBase.h"
//===========================================================================
//! �h�q�{��
//===========================================================================

//---------------------------------------------------------------------------
//! �R���X�g���N�^
//---------------------------------------------------------------------------
FactoryBase ::FactoryBase()
{
    // �ʒu���W
    _pos = VGet(40, 0, 40);
    // �}�`�`��̍ۂ̃T�C�Y
    _size = 0.01f;

    _dir = TO_RADIAN(180.0f) * 0;

    par._hp     = 100;   //< �ϋv�l
    par._atk    = 1;     //< �U����
    par._def    = 0;     //< �ϋv��
    par._atkSpd = 60;    //< �U�����x

    _isAtk    = false;   //< �U�������ǂ���
    _atkCount = 0;       //< �U���p�̃J�E���g

    // �����蔻��p�̕ϐ�
    _hit._hcPos   = VGet(_pos.x, _pos.y, _pos.z);   //< ���݈ʒu
    _hit._hcScale = 15;                             //< �T�C�Y

    // �U���p�����蔻��p�̕ϐ�
    _hitAtk._hcPos   = VGet(_pos.x, _pos.y, _pos.z);   //< ���݈ʒu
    _hitAtk._hcScale = 5;                              //< �T�C�Y
    _hitAtk._hcSpace = 8;

    _state = STATE::WAIT;   //< ���݂̏��

    _isDamage = false;   //< �U������Ă��邩�ǂ���

    // ���f��
    _model = std::make_unique<Model>();   //< ���ԍ쐬

    // �s��
    _matRot = MGetIdent();                            //< �P�ʍs����擾
    _matRot = MGetScale(VGet(_size, _size, _size));   //< �T�C�Y�w��

    // HpBar�̎���
    _hpBar = std::make_unique<HpBar>();

    // ���S���̃A�j���[�V����
    _is_dead = false;

    //! �U���A�j���[�V����
    _is_reset  = true;
    _color     = WHITE;
    _atk_size  = 1;
    _atk_alpha = 255;
    _count     = 0;
}

//---------------------------------------------------------------------------
//! �f�X�g���N�^
//---------------------------------------------------------------------------
FactoryBase ::~FactoryBase()
{
}

//---------------------------------------------------------------------------
//! ������
//---------------------------------------------------------------------------
bool FactoryBase::initialize(const char* modelName_, const char* materialName_)
{
    //! ���f���̓ǂݍ���
    _model->load(modelName_);
    //! ���f���̏������W�ݒ�(�}�g���b�N�X�ݒ�)
    MV1SetMatrix(_model->handle(), _matRot);

    //! ���f���Ƀe�N�X�`���𒣂�t��
    _graphHandle = LoadGraph(materialName_);
    MV1SetTextureGraphHandle(_model->handle(), 0, _graphHandle, false);

    if(_hpBar) {
        _hpBar->initialize(par._hp);
    }

    return true;
}

//---------------------------------------------------------------------------
//! �X�V
//---------------------------------------------------------------------------
void FactoryBase::update()
{
    switch(_state) {
        case STATE::WAIT:

            movHit();

            _atk_pos = VGet(_pos.x, _pos.y, _pos.z);
            break;

        case STATE::MOVE:

            _atk_pos = VGet(_pos.x, _pos.y, _pos.z);

            break;

        case STATE::ATTACK:

            movHit();
            attack();
            visibleAttack();

            break;

        case STATE::DEATH:

            deadAnim();

            break;

        default:

            break;
    }

    //! �}�g���b�N�X�̍��W�Ɍ��݈ʒu������
    setMat();

    //! �����蔻��p�̕ϐ�
    _hit._hcPos    = VGet(_pos.x, _pos.y, _pos.z);   //! ���݈ʒu
    _hitAtk._hcPos = VGet(_pos.x, _pos.y, _pos.z);   //! ���݈ʒu

    //! HpBar�̍X�V
    hpbarUpdate();

    ////! �}�g���b�N�X�ݒ�
    MV1SetMatrix(_model->handle(), _matRot);

    //! ���S���̋���
    dead();
}
//---------------------------------------------------------------------------
//! �`��
//---------------------------------------------------------------------------
void FactoryBase::render()
{
    //DrawSphere3D(_pos, _size, 5, BLACK, BLACK, false);

    _model->draw();

    movHit();

    //! HpBar
    if(_hpBar)
        _hpBar->render();

    SetUseLighting(false);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _atk_alpha);
    DrawSphere3D(_atk_pos, _atk_size, 5, _color, _color, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    SetUseLighting(true);

    //! �����蔻��p�̋�
    //DrawSphere3D(_hit._hcPos, _hit._hcScale, 5, WHITE, WHITE, false);
    //DrawSphere3D(_hitAtk._hcPos, _hitAtk._hcScale, 5, RED, RED, false);
}

//---------------------------------------------------------------------------
//! ���
//---------------------------------------------------------------------------
void FactoryBase::finalize()
{
    //! HpBar
    if(_hpBar)
        _hpBar->finalize();
}

//---------------------------------------------------------------------------
//! ���G(taskManager�ōX�V)
//---------------------------------------------------------------------------
bool FactoryBase::search(VECTOR& e_pos_, s16 e_size_)
{
    if(_state == STATE::DEATH)
        return false;

    if(hit(_hit._hcPos, _hit._hcScale, e_pos_, e_size_)) {
        direction(e_pos_);
        _target = e_pos_;

        return true;
    }

    return false;
}

//---------------------------------------------------------------------------
//! �U���J�n�g�p�����蔻��
//---------------------------------------------------------------------------
bool FactoryBase::atkSearch(VECTOR& e_pos_, s16 e_size_, int unit_hp_)
{
    if(_state == STATE::DEATH)
        return false;

    if(unit_hp_ <= 0)
        return false;

    if(hit(_hitAtk._hcPos, _hitAtk._hcScale, e_pos_, e_size_)) {
        _state = STATE::ATTACK;   //! ���݂̏��

        return true;
    }

    return false;
}

//---------------------------------------------------------------------------
//! ��葬�x�Ń��j�b�g�Ƀ_���[�W��^����
//---------------------------------------------------------------------------
void FactoryBase::attack()
{
    if(_atkCount % par._atkSpd == 0) {
        _isAtk = true;
    }
    else {
        _isAtk = false;
    }

    _atkCount++;

    if(_atkCount >= par._atkSpd)
        _atkCount = 0;
}

//---------------------------------------------------------------------------
//! �_���[�W����
//---------------------------------------------------------------------------
void FactoryBase::damage(f32 atk)
{
    if(_isDamage)
        par._hp -= atk;
}

//---------------------------------------------------------------------------
//! �����]��
//---------------------------------------------------------------------------
void FactoryBase::direction(VECTOR& fc_pos_)
{
    //! Unit����v���C���[�̕����x�N�g���쐬
    VECTOR dir;

    //! Unit�̍��W����h�q�{�݂̍��W������
    dir = VSub(fc_pos_, _pos);

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
    _matRot = MGetRotY(_dir);
    //! MGetRotY�łȂ���scale��1�ɂȂ�̂ŋ����ύX
    _matRot = MScale(_matRot, _size);

    //! �}�g���b�N�X�̍��W�Ɍ��݈ʒu������
    _matRot.m[3][0] = _pos.x;
    _matRot.m[3][1] = _pos.y;
    _matRot.m[3][2] = _pos.z;

    ////! �}�g���b�N�X�ݒ�
    MV1SetMatrix(_model->handle(), _matRot);
}

//---------------------------------------------------------------------------
//! �����蔻��̓���
//---------------------------------------------------------------------------
void FactoryBase::movHit()
{
    //! �}�g���b�N�X��Z���
    VECTOR vec_atk = VGet(_matRot.m[2][0], _matRot.m[2][1], _matRot.m[2][2]);

    //! ���K��
    vec_atk = VNorm(vec_atk);

    //!  �Ԋu��������
    mulVec(vec_atk, _hitAtk._hcSpace);

    //!  Z�����Ɣ��΂ɂȂ�̂Ŕ��]������
    mulVec(vec_atk, -1.0f);

    //! Unit�̃|�W�V�����ƃ}�g���b�N�X��Z���𑫂�
    _hitAtk._hcPos = VAdd(_pos, vec_atk);
}

//---------------------------------------------------------------------------
//!�@���G�����蔻��p�ϐ�
//---------------------------------------------------------------------------
VECTOR FactoryBase::hitPos()
{
    return _hit._hcPos;
}
s16 FactoryBase::hitSize()
{
    return _hit._hcScale;
}

//---------------------------------------------------------------------------
//! �G�̖{���n�̃T�C�Y��ς���
//---------------------------------------------------------------------------
void FactoryBase::setMainTower()
{
    _matRot = MGetScale(VGet(0.02f, 0.02f, 0.02f));

    //! �}�g���b�N�X�̍��W�Ɍ��݈ʒu������
    _matRot.m[3][0] = 60;
    _matRot.m[3][1] = 0;
    _matRot.m[3][2] = 60;

    ////! �}�g���b�N�X�ݒ�
    MV1SetMatrix(_model->handle(), _matRot);
}

//---------------------------------------------------------------------------
//! ���S
//---------------------------------------------------------------------------
void FactoryBase::dead()
{
    if(par._hp <= 0) {
        _state = STATE::DEATH;
    }
}

//---------------------------------------------------------------------------
//! ���S���̃A�j���[�V����
//---------------------------------------------------------------------------
void FactoryBase::deadAnim()
{
    _pos.y -= 1.0f;

    if(_pos.y <= -15) {
        _is_dead = true;
    }
}

//---------------------------------------------------------------------------
//! ���S���̃A�j���[�V�������I��������ǂ���
//---------------------------------------------------------------------------
bool FactoryBase::endAnimOfDead()
{
    if(_is_dead) {
        return true;
    }
    return false;
}

//---------------------------------------------------------------------------
//! �}�g���b�N�X��ݒ�
//---------------------------------------------------------------------------
void FactoryBase::setMat()
{
    _matRot.m[3][0] = _pos.x;
    _matRot.m[3][1] = _pos.y;
    _matRot.m[3][2] = _pos.z;
}

//---------------------------------------------------------------------------
//! HpBar�̍X�V
//---------------------------------------------------------------------------
void FactoryBase::hpbarUpdate()
{
    if(_hpBar) {
        _hpBar->prPos(_pos);

        _hpBar->setHp(par._hp);

        _hpBar->type(_type);

        _hpBar->update();

        _hpBar->setPos(VGet(-20, -60, 0));
    }
}

//---------------------------------------------------------------------------
//! �U������������
//---------------------------------------------------------------------------
void FactoryBase::visibleAttack()
{
    if(_is_reset) {
        _atk_pos = VGet(_pos.x, _pos.y + 15, _pos.z);

        if(_type == TYPE::TYPE_C)
            _atk_pos = VGet(_pos.x, _pos.y + 50, _pos.z);

        _is_reset  = false;
        _count     = 0;
        _atk_alpha = 255;
        _atk_size  = 1;
    }

    //! Unit����v���C���[�̕����x�N�g���쐬
    VECTOR dir;

    //! Unit�̍��W����h�q�{�݂̍��W������
    dir = VSub(_target, _atk_pos);

    // ���K��
    dir = VNorm(dir);

    if(_type == TYPE::TYPE_C)
    dir = VScale(dir, par._atkSpd * 0.002f);

    _atk_pos = VAdd(_atk_pos, dir);

    _count++;

    if(_count > par._atkSpd) {
        _is_reset = true;
    }
}

//---------------------------------------------------------------------------
//! �����A�j���[�V����
//---------------------------------------------------------------------------
void FactoryBase::attackAnimTypeA()
{
    if(_count < par._atkSpd * 0.6f)
        return;

    _atk_size += 0.7f;
    _atk_alpha -= 30;
}

void FactoryBase::attackAnimTypeC()
{
    if(_count < par._atkSpd * 0.9f)
        return;

    _atk_size += 2;
    _atk_alpha -= 30;
}

//---------------------------------------------------------------------------
//! attack���I�������move�ɖ߂�
//---------------------------------------------------------------------------
void FactoryBase::setMove(s16 hp_)
{
    if(hp_ <= 0) {
        _atk_pos   = VGet(_pos.x, _pos.y, _pos.z);
        _state     = STATE::WAIT;
        _isAtk     = false;
        _atk_alpha = 0;
    }
}
