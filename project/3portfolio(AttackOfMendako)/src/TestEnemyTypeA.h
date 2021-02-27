//---------------------------------------------------------------------------
//!	@file	sceneTest3.cpp
//!	@brief	enemy�̓����蔻��̓����̎���
//---------------------------------------------------------------------------

#pragma once
#include "objBase.h"

//===========================================================================
//! �G�l�~�[
//===========================================================================

class SceneGameTest3 : public Scene,
                       public BaseObject
{
public:
    SceneGameTest3();
    ~SceneGameTest3();

    //! ������
    bool initialize();
    //! �X�V
    void update();
    //! �`��
    void render();
    //! ���
    void finalize();

    //! ���G�p�����蔻��
    bool hit(VECTOR& p0, f32 r0, VECTOR& p1, f32 r1);
    //! ���G
    void search(VECTOR& fc_pos, VECTOR& main_fc_pos);

    //! �ړ�
    //!���G���Ĕ͈͓��Ɏ{�݂��������炻�̍��W��ړI�n�ɂ��Ĉړ�
    void move(VECTOR& fc_pos);

    //! �����]��
    void direction(VECTOR& fc_pos);

    //! �����蔻��̓���
    void movHit();

private:
    //! �������{��
    VECTOR _targetPos;

    //! �����蔻��p�̕ϐ�(hit circle)
    VECTOR _hcPos;     //! ���݈ʒu
    s16    _hcScale;   //! �T�C�Y
    s16    _hcSpace;   //! �Ԋu

    //! ��t���[���O�̍��W
    VECTOR _oldPos;
};
