//---------------------------------------------------------------------------
//!	@file	FactoryTypeA.h
//!	@brief	FactoryTypeA
//---------------------------------------------------------------------------

#pragma once
#include "factoryBase.h"

//===========================================================================
//! �t�@�N�g���[
//===========================================================================

class FactoryTypeA : public FactoryBase
{
public:
    FactoryTypeA();
    ~FactoryTypeA();

    //! ������
    bool initialize();
    //! �X�V
    void update();
    //! �`��
    void render();
    //! ���
    void finalize();


public:
private:
};
