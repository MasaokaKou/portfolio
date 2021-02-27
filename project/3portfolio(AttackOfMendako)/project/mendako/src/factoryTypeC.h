//---------------------------------------------------------------------------
//!	@file	FactoryTypeA.h
//!	@brief	FactoryTypeA
//---------------------------------------------------------------------------

#pragma once
#include "factoryBase.h"

//===========================================================================
//! �t�@�N�g���[
//===========================================================================

class FactoryTypeC : public FactoryBase
{
public:
    FactoryTypeC();
    ~FactoryTypeC();

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
