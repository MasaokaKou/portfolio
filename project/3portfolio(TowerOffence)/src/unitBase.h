//---------------------------------------------------------------------------
//!	@file	sceneTest3.cpp
//!	@brief	Unit�̓����蔻��̓����̎���
//---------------------------------------------------------------------------

#pragma once

//===========================================================================
//! ���j�b�g
//===========================================================================

class UnitBase : 
                  public BaseObject
{
public:
    UnitBase();
    ~UnitBase();

    bool initialize(const char* modelName_, const char* materialName_);   //!< ������
    void update();                                                      //!< �X�V
    void render();                                                      //!< �`��
    void finalize();                                                    //!< ���

    //! �����_�R�̓o�ꃂ�[�V����
    void startUp();
    //! �J�n��b�̊ԉ�]����
    void startRotation(float side_dot_);
    //! �}�g���b�N�X�̂��Ă͂�
    void setMat();

    //! ���G
    bool search(VECTOR& fc_pos_, f32 f_size_, STATE _f_state_);

    //! �ړ�
    //!���G���Ĕ͈͓��Ɏ{�݂��������炻�̍��W��ړI�n�ɂ��Ĉړ�
    void move(VECTOR& fc_pos_);
    void setMainTarget(VECTOR& main_fc_pos_);

    //! �����]��
    void direction(VECTOR& fc_pos_);

    //! �����蔻��̓���
    void movHit();

    //! ��葬�x�Ńt�@�N�g���[�Ƀ_���[�W��^����
    void attack();

    //! attack���I�������move�ɖ߂�
    void setMove(s16 hp_);

    void damage(bool isAtk_, f32 atk_);

    bool getIsDamage() { return _isDamage; }
    void isDamage() { _isDamage = true; }

    //! ���S���̃��[�V����
    void checkMotion();
    void deadMotion();
    //! �G�����񂾂�is_search��true�ɂ���
    void isSearch() { _is_search = true; }

    //! HP�̏���ȏ�񕜂��Ȃ��悤��
    void setMaxHitPoint();
    //! �T�C�Y�ύX
    void setSize();

    //! �X�e�[�^�X���ƂɍX�V
    void stateUpdate();

    //! HpBar�̍X�V
    void hpbarUpdate();

public:
    //! ���j�b�g�̎��
    TYPE type();

private:
    VECTOR _oldPos;   //!< ��t���[���O�̍��W

protected:
    //! �������{��
    VECTOR _targetPos;

    //!�ŏ��̍��G���I��莟����G��؂�
    VECTOR _fc_pos;
    bool   _is_search;
};
