//---------------------------------------------------------------------------
//!	@file	sceneTest3.cpp
//!	@brief	Unit�̓����蔻��̓����̎���
//---------------------------------------------------------------------------

#pragma once
//#include "objBase.h"

//===========================================================================
//! ���j�b�g
//===========================================================================



class unitSelector :public Scene
{
public:
    unitSelector();
    ~unitSelector();

    bool initialize();   //! ������
    void update();       //! �X�V
    void render();       //! �`��
    void finalize();     //! ���

public:
    //! ��x�J�[�\���𓮂����Ă��玟�ɂ���������܂�
    bool timer();
    //! �J�[�\���̈ړ�����
    void limit();

    //! �e���j�b�g�̏����������Ă���
    void setUnitLimit(std::vector<s16> unit_limit_);

    //! �}�E�X�ƃZ���N�g�{�b�N�X�̔���
    void hitMouseCheck();
    void setUnitFromMouse();
    bool checkHit(int i_);


    //! �I�ׂ郆�j�b�g�̐���
    void lockUnit();

    //! ���`��
    void drawLock(int i_);

    //! �A�����b�N�A�j���[�V����
    void lockAnim(int i_);


    //! ���j�b�g�ɃJ�[�\�������������̃e�L�X�g
    void textTypeOfUnit(int i_);

public:
    s16 selNum()
    {
        return _sel_num;
    }
    
private:
    //! �ǂ̃��j�b�g��I�����Ă��邩
    //! unitManager�ɓn��
    s16 _sel_num;

    //! �Z���N�^�[�J�[�\��
    //!(x,y,h&w)
    VECTOR _sel_car;
    //! �Z���N�^�[�{�b�N�X
    VECTOR _sel_box[UNIT_MAX];
    

    //!�@�J�[�\���ړ��t���O
    bool _is_move;
    //! �J�[�\���ړ��Ԋu
    s16 _timer;
    //! �e���j�b�g�摜
    int _graph[UNIT_MAX];

    //! �e���j�b�g�̏��
    std::vector<s16> _unit_limit;

    //! �}�E�X�J�[�\��
    int _mouse_x, _mouse_y;
    bool _is_hit[UNIT_MAX];

    //! ���̉摜
    int _lock_graph;

    
};
