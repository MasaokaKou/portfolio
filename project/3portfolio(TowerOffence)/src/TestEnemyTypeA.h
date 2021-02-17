//---------------------------------------------------------------------------
//!	@file	sceneTest3.cpp
//!	@brief	enemyの当たり判定の動きの実装
//---------------------------------------------------------------------------

#pragma once
#include "objBase.h"

//===========================================================================
//! エネミー
//===========================================================================

class SceneGameTest3 : public Scene,
                       public BaseObject
{
public:
    SceneGameTest3();
    ~SceneGameTest3();

    //! 初期化
    bool initialize();
    //! 更新
    void update();
    //! 描画
    void render();
    //! 解放
    void finalize();

    //! 索敵用当たり判定
    bool hit(VECTOR& p0, f32 r0, VECTOR& p1, f32 r1);
    //! 索敵
    void search(VECTOR& fc_pos, VECTOR& main_fc_pos);

    //! 移動
    //!索敵して範囲内に施設があったらその座標を目的地にして移動
    void move(VECTOR& fc_pos);

    //! 方向転換
    void direction(VECTOR& fc_pos);

    //! 当たり判定の動き
    void movHit();

private:
    //! 向かう施設
    VECTOR _targetPos;

    //! 当たり判定用の変数(hit circle)
    VECTOR _hcPos;     //! 現在位置
    s16    _hcScale;   //! サイズ
    s16    _hcSpace;   //! 間隔

    //! 一フレーム前の座標
    VECTOR _oldPos;
};
