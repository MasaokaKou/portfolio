//---------------------------------------------------------------------------
//!	@file	hpBar.cpp
//!	@brief	hpBar�̎���
//---------------------------------------------------------------------------

#pragma once

//===========================================================================
//! HPBar
//===========================================================================

class HpBar
{
public:
    HpBar();
    ~HpBar();

    bool initialize(s16 max_hp_);   //! ������
    void update();                  //! �X�V
    void render();                  //! �`��
    void finalize();                //! ���

public:
    //! pos�̎󂯂킽��
    void prPos(VECTOR pos_);

    //! HP�̎󂯓n��
    void setHp(s16 hp_);

    //! HP�����A�j���[�V����
    void animation();
    //! �J�E���g����
    bool decCount();

    void type(s16 type_);

    void setPos(VECTOR v_);

private:
    //! HP��`�悷����̂̍��W
    VECTOR _pos;
    VECTOR _scr_pos;

    //! �`�悷��HP
    f32 _hp;
    f32 _max_hp;

    u32 _front_alpha;

    //! hpBar�̃T�C�Y�ݒ�
    f32 _wide, _hide;

    //! HP�̌��銄��
    f32 _rate;

    //! OBJECT���_���[�W���󂯂���
    bool _is_damage;

    //! TYPED�ɍU������Ă��邩�ǂ���
    bool _is_heal;

    s16 _type;

    //! �A�j���[�V����
    //! ����HPBar
    f32 _back_wide;
    //! ���݂�hp(����HPBar�����炷�ڈ�)
    f32 _dec;
    //! wide�����Ă���back_wide������܂ł̊��o
    s16 _anim_count;
    //! ��낪���n�߂�܂ł̃t���O
    bool _anim_flag;
    s16  _alpha;
};
