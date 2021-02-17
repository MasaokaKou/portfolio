//---------------------------------------------------------------------------
//!	@file	objBase.h
//!	@brief	�I�u�W�F�N�g�̊�b
//---------------------------------------------------------------------------

#pragma once

//===========================================================================
//!	�I�u�W�F�N�g���
//===========================================================================

//! ��Ԑݒ�̍\����
enum class STATE
{
    WAIT,
    MOVE,
    ATTACK,
    DEATH

};

//! ���
enum TYPE
{
    TYPE_A,
    TYPE_B,
    TYPE_C,
    TYPE_D

};

//! �Q�[�����p�����[�^�[
struct Parameter
{
    f32 _hp;       //! �ϋv�l
    f32 _atk;      //! �U����
    f32 _def;      //! �ϋv��
    f32 _movSpd;   //! �i�R���x
    s16 _atkSpd;   //! �U�����x(_atkSpd �t���[���Ɉ�x)
};

//! //! �����蔻��p�̕ϐ�(hit circle)
struct Hit
{
    VECTOR _hcPos;     //! ���݈ʒu
    s16    _hcSpace;   //! �Ԋu
    s16    _hcScale;   //! �T�C�Y
};

class BaseObject
{
public:
    BaseObject()          = default;
    virtual ~BaseObject() = default;

    virtual bool initialize() = 0;   //!> ������
    virtual void update()     = 0;   //!> �X�V
    virtual void render()     = 0;   //!> �`��
    virtual void finalize()   = 0;   //!> ���

public:
    //! �Q�b�^�[�֐�
    VECTOR pos() const { return _pos; }
    f32    hp() const { return par._hp; }
    f32    atk() const { return par._atk; }
    f32    def() const { return par._def; }
    f32    movSpd() const { return par._movSpd; }
    f32    atkSpd() const { return par._atkSpd; }
    f32    size() const { return _size; }
    bool   isAtk() const { return _isAtk; }
    STATE  state();   //! ���݂̏��

    //! ����ł��邩�ǂ���
    bool isDead() { return _is_dead; }

    //! H��������Ă���
    s16 HP();

public:
    //! ���W�ݒ�
    void setPos(VECTOR pos_);

    //! ���G�p�����蔻��
    bool hit(VECTOR& p0_, f32 r0_, VECTOR& p1_, f32 r1_);

    //! �U���t���O��������
    void setAtk(bool enable_) { _isAtk = enable_; }

protected:
    //! ��b���
    VECTOR    _pos;      //! �ʒu���W
    f32       _size;     //! �}�`�̃T�C�Y
    f32       _dir;      //! ����
    MATRIX    _matRot;   //! ��]�s��
    VECTOR    _side;     //! obj�̉E�����̃x�N�g�����쐬
    Parameter par;       //! �p�����[�^�[
    STATE     _state;    //! ���݂̏��
    TYPE      _type;     //! ���j�b�g�̎��

    //! ���f���֌W
    std::unique_ptr<Model> _model;         //! ���f��
    VECTOR                 _scale;         //! ���f���X�P�[��
    f32                    _alpha;         //! ���f���̕s�����x
    int                    _graphHandle;   //! ���f���̉摜�p�n���h��

    //! �U���t���O�֌W
    bool _isAtk;      //! �U�������ǂ���
    s16  _atkCount;   //! �U���p�̃J�E���g
    bool _isDamage;   //! �U������Ă��邩�ǂ���

    //! �����蔻��֌W
    Hit _hit;      //!�@���G�����蔻��p�ϐ�
    Hit _hitAtk;   //! �U�������蔻��

    //! �o�ꃂ�[�V�����p�ϐ�
    s16 _startUpTimer;

    //! HPBar�̎���
    std::unique_ptr<HpBar> _hpBar;   //! ���f��
    s16                    _HP;      //! HP�̏��

    //! ���Ń��[�V�������I����Ă邩�ǂ���
    //! UnitManager�Ŕ��肷��悤�B
    bool _is_dead;
};
