//---------------------------------------------------------------------------
//!	@file	unitManager.h
//!	@brief	UnitClass�̊Ǘ�
//---------------------------------------------------------------------------

#pragma once

#include "unitBase.h"
#include "unitTypeA.h"
#include "unitTypeB.h"
#include "unitTypeC.h"
#include "unitTypeD.h"

//! ���ݔz�u���Ă��郆�j�b�g
struct size
{
    s16 TYPE_A,
        TYPE_B,
        TYPE_C,
        TYPE_D;
};

class UnitManager
{
public:
    UnitManager();
    ~UnitManager();

    //! ������
    bool initialize(s16 stage_);
    //! �X�V
    void update(s16 selNum_, bool hit_mouse_point_);
    //! �`��
    void render();
    //! ���
    void finalize();

public:
    //! ���G(taskManager�ōX�V)
    bool search_d(VECTOR& fc_pos_, s16 f_size_, s16 i_);

    //! ���C���^�[�Q�b�g�ݒ�
    void setMainTarget(VECTOR& main_fc_pos_);

    //! �G��HP��0�ɂȂ�����MOVE��
    void setMove(s16 hp_);

    //! �e�_���[�W����
    void damage_a(bool isAtk_, f32 atk_, s16 i_, TYPE type_);
    void damage_b(bool isAtk_, f32 atk_, s16 i_, TYPE type_);
    void damage_c(bool isAtk_, f32 atk_, s16 i_, TYPE type_);
    void damage_d(bool isAtk_, f32 atk_, s16 i_);

    //! ���ŏ���
    void deleteObj_a();
    void deleteObj_b();
    void deleteObj_c();
    void deleteObj_d();
    //! ���ŏ����܂Ƃ߂�
    void deleteObj();

    //! �}�E�X�Ɖ�ʂ̓����蔻��
    void setScreenPos();
    //! �}�E�X�Ŕz�u
    void setUnit();

    //! �Q�[���t�B�[���h���O����
    bool isOut();

    //! �X�e�[�W���Ƃ̃��j�b�g�̎g�p����ݒ�
    void unitLimit(s16 stage_);

    //! �J�E���^�[
    void count();

    //! �G�̍��G�͈͂ō��N���b�N
    void errorCleckEnemy(VECTOR pos_);

    //! ���j�b�g�̎c���Ȃ���Ԃō��N���b�N
    void errorCleckUnit(VECTOR pos_);

    //! �t�B�[���h�ɂ��郆�j�b�g�Ǝ莝���̃��j�b�g���O�ɂȂ�����Q�[���I�[�o�[
    void gameOver();

    //! TYPEB�̍U���A�j���[�V����
    void atkMoveTypeB(VECTOR fac_pos_, f32 fac_size_, STATE state_);

private:
public:
    //! �Q�b�^�[
    VECTOR pos_a(s16 i_) const;
    s16    size_a(s16 i_) const;

    //! �Q�b�^�[
    VECTOR pos_b(s16 i_) const;
    s16    size_b(s16 i_) const;

    //! �Q�b�^�[
    VECTOR pos_c(s16 i_) const;
    s16    size_c(s16 i_) const;

    //! �Q�b�^�[
    VECTOR pos_d(s16 i_) const;
    s16    size_d(s16 i_) const;
    bool   isAtk_d(s16 i_) const;
    f32    atk_d(s16 i_) const;

    TYPE TYPE_D(s16 i_) const;

    //! �C���X�^���X�̃k���`�F�b�N
    bool checkInstance_a();
    bool checkInstance_b();
    bool checkInstance_c();
    bool checkInstance_d();

    std::vector<s16> unit_limit();

    //! taskManager�œG�̍��G�͈͂ƃ}�E�X�|�C���^�̓����蔻�肷��悤
    HITRESULT_LINE GetMousePosition() { return ScreenPos; }

    //ScreenPos��factory�̍��G����
    bool hit_ScreenPos_to_factory(VECTOR pos_, u32 r_);

    UnitTypeA* typeA(u32 index_) const { return _units_a[index_].get(); }
    UnitTypeB* typeB(u32 index_) const { return _units_b[index_].get(); }
    UnitTypeC* typeC(u32 index_) const { return _units_c[index_].get(); }
    UnitTypeD* typeD(u32 index_) const { return _units_d[index_].get(); }

public:
    //! ���̂̃T�C�Y
    s16 unitTypeASize();
    s16 unitTypeBSize();
    s16 unitTypeCSize();
    s16 unitTypeDSize();

private:
    //! ���j�b�g�̃��j�[�N�|�C���^�[
    std::vector<std::unique_ptr<UnitTypeA>> _units_a;
    std::vector<std::unique_ptr<UnitTypeB>> _units_b;
    std::vector<std::unique_ptr<UnitTypeC>> _units_c;
    std::vector<std::unique_ptr<UnitTypeD>> _units_d;

    //! ���ݔz�u���Ă��郆�j�b�g
    size _size;

    //! �}�E�X�N���b�N�Ŕz�u����p
    //! ��ʏ�̍��W�����[���h���W�ɕϊ����邽�߂̕ϐ�
    VECTOR         Start3DPos, End3DPos;
    HITRESULT_LINE ScreenPos;

    int  _mouse_x, _mouse_y;   //! �}�E�X�̍��W
    int  _click;               //! ���͏��
    bool _span;                //! �z�u����Ԋu
    int  _count;               //! �z�u����Ԋu

    s16 _selNum;   //! ���I�����Ă��郆�j�b�g

    //! �X�e�[�W���Ƃ̃��j�b�g�g�p���
    std::vector<s16> _unit_limit;

    //! �G�̍��G�͈͂ƃ}�E�X�|�C���^�̓����蔻��
    bool _hit_mouse_point;

    //! �G�̍��G�͈͂ō��N���b�N
    bool _errorCleckEnemy;

    //! ���j�b�g�̎c���Ȃ���Ԃō��N���b�N
    bool _errorCleckUnit;

    //! �Q�[���I�[�o�[�p�ϐ�
    int _go_alpha;
    int _go_text_alpha;
};
