//---------------------------------------------------------------------------
//!	@file	sceneTest3.cpp
//!	@brief	ui�S�̂̊Ǘ�
//---------------------------------------------------------------------------

#pragma once

//===========================================================================
//! UI
//===========================================================================

class uiManager
{
public:
    uiManager();
    ~uiManager();

    bool initialize();   //! ������
    void update();       //! �X�V
    void render();       //! �`��
    void finalize();     //! ���

public:
    //! �e���j�b�g�̏����������Ă���
    void setUnitLimit(std::vector<s16> unit_limit_);

public:
    s16 selNum();
    s16 stage();


private:
    //! ���j�b�g�Z���N�^�[�̃��j�[�N�|�C���^
    std::unique_ptr<unitSelector> _unit_sel;
    s16                           _unit_limit[UNIT_MAX];
};
