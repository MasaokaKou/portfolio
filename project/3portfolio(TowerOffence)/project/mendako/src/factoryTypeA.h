//---------------------------------------------------------------------------
//!	@file	FactoryTypeA.h
//!	@brief	FactoryTypeA
//---------------------------------------------------------------------------

#pragma once
#include "factoryBase.h"

//===========================================================================
//! ファクトリー
//===========================================================================

class FactoryTypeA : public FactoryBase
{
public:
    FactoryTypeA();
    ~FactoryTypeA();

    //! 初期化
    bool initialize();
    //! 更新
    void update();
    //! 描画
    void render();
    //! 解放
    void finalize();


public:
private:
};
