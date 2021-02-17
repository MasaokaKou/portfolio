//---------------------------------------------------------------------------
//!	@file	FactoryTypeA.h
//!	@brief	FactoryTypeA
//---------------------------------------------------------------------------

#pragma once
#include "factoryBase.h"

//===========================================================================
//! ファクトリー
//===========================================================================

class FactoryTypeB : public FactoryBase
{
public:
    FactoryTypeB();
    ~FactoryTypeB();

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
