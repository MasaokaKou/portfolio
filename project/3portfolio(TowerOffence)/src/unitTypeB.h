#pragma once
//---------------------------------------------------------------------------
//!	@file	unitTypeB.h
//!	@brief	UnitTypeBの実装
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! 遠距離の敵
//---------------------------------------------------------------------------

class UnitTypeB
: public UnitBase
{
public:
    UnitTypeB();
    ~UnitTypeB();

public:
    bool initialize();   //! 初期化
    void update();       //! 更新
    void render();       //! 描画
    void finalize();     //! 解放

public:
    //! 遠距離武器の動き
    void atkMove(VECTOR fac_pos_, f32 fac_size_, STATE state_);
    

private:
    //! 遠距離攻撃のモデル（ウニ）
    std::unique_ptr<Model> _model;  
    MATRIX                 _mat;

    


};
