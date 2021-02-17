//---------------------------------------------------------------------------
//!	@file	mainFactory.h
//!	@brief	mainFactory
//---------------------------------------------------------------------------

#pragma once
#include "factoryBase.h"

//===========================================================================
//! ファクトリー
//===========================================================================

class mainFactory : public FactoryBase
{
public:
    mainFactory();
    ~mainFactory();

    //! 初期化
    bool initialize();
    //! 更新
    void update();
    //! 描画
    void render();
    //! 解放
    void finalize();


public:
    VECTOR hitPos();
    s16    hitSize();

private:
};
