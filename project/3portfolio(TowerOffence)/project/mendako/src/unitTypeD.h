#pragma once
//---------------------------------------------------------------------------
//!	@file	unitTypeB.h
//!	@brief	UnitTypeBの実装
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! 回復用ユニット
//---------------------------------------------------------------------------

class UnitTypeD
: public UnitBase
{
public:
    UnitTypeD();
    ~UnitTypeD();

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

    //! 回復モーション更新
    void atkAnimUpdate();

    //! 回復モーション描画
    void atkAnimDraw();

private:
    //! 乗り物のモデル
    std::unique_ptr<Model> _ride_model;
    MATRIX                 _mat;

    //! 攻撃用のモデル
    std::unique_ptr<Model> _atk_circle;
    int                    _atk_alpha;
    f32                    _atk_scale;


    int  _graphHandle;
    bool _modelDead;

    //! クリオネのモデルの動きようタイマー
    int _dead_timer;
};
