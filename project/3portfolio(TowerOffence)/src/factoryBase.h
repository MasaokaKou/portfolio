//---------------------------------------------------------------------------
//!	@file	factoryBase.h
//!	@brief	FactoryBase
//---------------------------------------------------------------------------

#pragma once
#include "objBase.h"

//===========================================================================
//! �t�@�N�g���[
//===========================================================================

class FactoryBase : public BaseObject
{
public:
    FactoryBase();
    ~FactoryBase();

    //! ������
    bool initialize(const char* modelName_, const char* materialName_);
    //! �X�V
    void update();
    //! �`��
    void render();
    //! ���
    void finalize();

public:
    //! ���G
    bool search(VECTOR& e_pos_, s16 e_size_);
    //! �U���J�n�g�p�����蔻��
    bool atkSearch(VECTOR& e_pos_, s16 e_size_ , int unit_hp_);

    //! �_���[�W����
    void damage(f32 atk_);
    void setDamage() { _isDamage = true; }

    //! ��葬�x�Ń��j�b�g�Ƀ_���[�W��^����
    void attack();

    //! �����]��
    void direction(VECTOR& fc_pos_);
    //! �����蔻��̓���
    void movHit();

    //! �G�̖{���n�̃T�C�Y��ς���
    void setMainTower();

    //! ���S���̃A�j���[�V����
    void deadAnim();
    bool endAnimOfDead();
    void dead();

    //! �}�g���b�N�X��ݒ�
    void setMat();

    //! HpBar�̍X�V
    void hpbarUpdate();

    //! �U������������
    void visibleAttack();

    //! �����A�j���[�V����
    void attackAnimTypeA();
    void attackAnimTypeC();

    //! attack���I�������move�ɖ߂�
    void setMove(s16 hp_);

    void setState(STATE s) { _state = s; }

public:
    //! �Q�b�^�[
    TYPE   type() { return _type; }
    VECTOR hitPos();
    s16    hitSize();
    int    atkCount() { return _atkCount; }

    int count() { return _count; }

protected:
    //! �U������������
    //! ���݈ʒu
    VECTOR _atk_pos;
    //! �ړI�n
    VECTOR _target;
    //! �ړI�n�؂�ւ�
    bool _is_reset;
    //! �U���̐F
    unsigned int _color;
    //! �U���̃T�C�Y
    f32 _atk_size;
    //! �U���̓��ߓx
    int _atk_alpha;
    int _count;
};
