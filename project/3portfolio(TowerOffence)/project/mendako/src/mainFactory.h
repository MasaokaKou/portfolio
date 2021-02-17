//---------------------------------------------------------------------------
//!	@file	mainFactory.h
//!	@brief	mainFactory
//---------------------------------------------------------------------------

#pragma once
#include "factoryBase.h"

//===========================================================================
//! �t�@�N�g���[
//===========================================================================

class mainFactory : public FactoryBase
{
public:
    mainFactory();
    ~mainFactory();

    //! ������
    bool initialize();
    //! �X�V
    void update();
    //! �`��
    void render();
    //! ���
    void finalize();


public:
    VECTOR hitPos();
    s16    hitSize();

private:
};
