
//---------------------------------------------------------------------------
//!	@file	mainFactory.cpp
//!	@brief	mainFactory
//---------------------------------------------------------------------------
#include "mainFactory.h"
//===========================================================================
//! 防衛施設
//===========================================================================

//---------------------------------------------------------------------------
//! コンストラクタ
//---------------------------------------------------------------------------
mainFactory ::mainFactory()
{
    par._hp = 20;   //! 耐久値
    _hit._hcPos = _pos;
    _hit._hcScale = 50;
}

//---------------------------------------------------------------------------
//! デストラクタ
//---------------------------------------------------------------------------
mainFactory ::~mainFactory()
{
}

//---------------------------------------------------------------------------
//! 初期化
//---------------------------------------------------------------------------
bool mainFactory::initialize()
{
    FactoryBase::initialize("data/Tower/tower.mqo", "data/Tower/towerMain.png");

    return true;
}

//---------------------------------------------------------------------------
//! 更新
//---------------------------------------------------------------------------
void mainFactory::update()
{
    FactoryBase::update();
    FactoryBase::setMainTower();
}
//---------------------------------------------------------------------------
//! 描画
//---------------------------------------------------------------------------
void mainFactory::render()
{
    FactoryBase::render();
    //DrawSphere3D(_pos, 5, 5, WHITE, WHITE, true);
}

//---------------------------------------------------------------------------
//! 解放
//---------------------------------------------------------------------------
void mainFactory::finalize()
{
    FactoryBase::finalize();
}

VECTOR mainFactory::hitPos()
{
    return _hit._hcPos;
}

s16 mainFactory::hitSize()
{
    return _hit._hcScale;
}
