//---------------------------------------------------------------------------
//!	@file	FactoryTypeA.h
//!	@brief	FactoryTypeA
//---------------------------------------------------------------------------

#pragma once
#include "factoryBase.h"

//===========================================================================
//! �t�@�N�g���[
//===========================================================================

class FactoryTypeB : public FactoryBase
{
public:
    FactoryTypeB();
    ~FactoryTypeB();

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
