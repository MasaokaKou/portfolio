#pragma once
//---------------------------------------------------------------------------
//!	@file	unitTypeA.h
//!	@brief	UnitTypeAの実装
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! 近接の敵
//---------------------------------------------------------------------------

class UnitTypeA
: public UnitBase
{
public:
    UnitTypeA();
    ~UnitTypeA();

public:
    bool initialize();   //! 初期化
    void update();       //! 更新
    void render();       //! 描画
    void finalize();     //! 解放

private:

};
