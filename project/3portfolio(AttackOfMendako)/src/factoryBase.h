//---------------------------------------------------------------------------
//!	@file	factoryBase.h
//!	@brief	FactoryBase
//---------------------------------------------------------------------------

#pragma once
#include "objBase.h"

//===========================================================================
//! ファクトリー
//===========================================================================

class FactoryBase : public BaseObject
{
public:
    FactoryBase();
    ~FactoryBase();

    //! 初期化
    bool initialize(const char* modelName_, const char* materialName_);
    //! 更新
    void update();
    //! 描画
    void render();
    //! 解放
    void finalize();

public:
    //! 索敵
    bool search(VECTOR& e_pos_, s16 e_size_);
    //! 攻撃開始使用当たり判定
    bool atkSearch(VECTOR& e_pos_, s16 e_size_ , int unit_hp_);

    //! ダメージ処理
    void damage(f32 atk_);
    void setDamage() { _isDamage = true; }

    //! 一定速度でユニットにダメージを与える
    void attack();

    //! 方向転換
    void direction(VECTOR& fc_pos_);
    //! 当たり判定の動き
    void movHit();

    //! 敵の本拠地のサイズを変える
    void setMainTower();

    //! 死亡時のアニメーション
    void deadAnim();
    bool endAnimOfDead();
    void dead();

    //! マトリックスを設定
    void setMat();

    //! HpBarの更新
    void hpbarUpdate();

    //! 攻撃を可視化する
    void visibleAttack();

    //! 爆発アニメーション
    void attackAnimTypeA();
    void attackAnimTypeC();

    //! attackが終わったらmoveに戻す
    void setMove(s16 hp_);

    void setState(STATE s) { _state = s; }

public:
    //! ゲッター
    TYPE   type() { return _type; }
    VECTOR hitPos();
    s16    hitSize();
    int    atkCount() { return _atkCount; }

    int count() { return _count; }

protected:
    //! 攻撃を可視化する
    //! 現在位置
    VECTOR _atk_pos;
    //! 目的地
    VECTOR _target;
    //! 目的地切り替え
    bool _is_reset;
    //! 攻撃の色
    unsigned int _color;
    //! 攻撃のサイズ
    f32 _atk_size;
    //! 攻撃の透過度
    int _atk_alpha;
    int _count;
};
