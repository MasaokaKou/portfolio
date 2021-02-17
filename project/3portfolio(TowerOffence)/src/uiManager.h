//---------------------------------------------------------------------------
//!	@file	sceneTest3.cpp
//!	@brief	ui全体の管理
//---------------------------------------------------------------------------

#pragma once

//===========================================================================
//! UI
//===========================================================================

class uiManager
{
public:
    uiManager();
    ~uiManager();

    bool initialize();   //! 初期化
    void update();       //! 更新
    void render();       //! 描画
    void finalize();     //! 解放

public:
    //! 各ユニットの上限をもらってくる
    void setUnitLimit(std::vector<s16> unit_limit_);

public:
    s16 selNum();
    s16 stage();


private:
    //! ユニットセレクターのユニークポインタ
    std::unique_ptr<unitSelector> _unit_sel;
    s16                           _unit_limit[UNIT_MAX];
};
