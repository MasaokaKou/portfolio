//---------------------------------------------------------------------------
//!	@file	FactoryTypeA.h
//!	@brief	FactoryTypeA
//---------------------------------------------------------------------------

#pragma once
#include "factoryBase.h"

//===========================================================================
//! ファクトリー
//===========================================================================

class FactoryTypeC : public FactoryBase
{
public:
    FactoryTypeC();
    ~FactoryTypeC();

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
