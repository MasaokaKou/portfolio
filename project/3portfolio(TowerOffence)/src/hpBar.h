//---------------------------------------------------------------------------
//!	@file	hpBar.cpp
//!	@brief	hpBarの実装
//---------------------------------------------------------------------------

#pragma once

//===========================================================================
//! HPBar
//===========================================================================

class HpBar
{
public:
    HpBar();
    ~HpBar();

    bool initialize(s16 max_hp_);   //! 初期化
    void update();                  //! 更新
    void render();                  //! 描画
    void finalize();                //! 解放

public:
    //! posの受けわたし
    void prPos(VECTOR pos_);

    //! HPの受け渡し
    void setHp(s16 hp_);

    //! HP減少アニメーション
    void animation();
    //! カウント減少
    bool decCount();

    void type(s16 type_);

    void setPos(VECTOR v_);

private:
    //! HPを描画するものの座標
    VECTOR _pos;
    VECTOR _scr_pos;

    //! 描画するHP
    f32 _hp;
    f32 _max_hp;

    u32 _front_alpha;

    //! hpBarのサイズ設定
    f32 _wide, _hide;

    //! HPの減る割合
    f32 _rate;

    //! OBJECTがダメージを受けたら
    bool _is_damage;

    //! TYPEDに攻撃されているかどうか
    bool _is_heal;

    s16 _type;

    //! アニメーション
    //! 後ろのHPBar
    f32 _back_wide;
    //! 現在のhp(後ろのHPBarを減らす目安)
    f32 _dec;
    //! wideが削れてからback_wideが削れるまでの感覚
    s16 _anim_count;
    //! 後ろが削れ始めるまでのフラグ
    bool _anim_flag;
    s16  _alpha;
};
