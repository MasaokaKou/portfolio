#pragma once
//---------------------------------------------------------------------------
//!	@file	unitTypeB.h
//!	@brief	UnitTypeBの実装
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! 遠距離の敵
//---------------------------------------------------------------------------

class UnitTypeC
: public UnitBase
{
public:
    UnitTypeC();
    ~UnitTypeC();

public:
    bool initialize();   //! 初期化
    void update();       //! 更新
    void render();       //! 描画
    void finalize();     //! 解放

public:
    //! モデルそのものの動き
    void modelMove();
    //! モデルの消滅モーション
    void modelDead();

    bool isMolDead() { return _modelDead; }

    //! モデルの方向転換
    void direction(VECTOR dir_);

private:
    //! 乗り物のモデル
    std::unique_ptr<Model> _model;
    MATRIX                 _mat;

    int _graphHandle;
    bool _modelDead;

    //! モデルの透過度
    f32 _alpha;

    //! カメのモデルの動きようタイマー
    int _dead_timer;
};
