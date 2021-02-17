//---------------------------------------------------------------------------
//!	@file	unitManager.h
//!	@brief	UnitClassの管理
//---------------------------------------------------------------------------

#pragma once

#include "unitBase.h"
#include "unitTypeA.h"
#include "unitTypeB.h"
#include "unitTypeC.h"
#include "unitTypeD.h"

//! 現在配置しているユニット
struct size
{
    s16 TYPE_A,
        TYPE_B,
        TYPE_C,
        TYPE_D;
};

class UnitManager
{
public:
    UnitManager();
    ~UnitManager();

    //! 初期化
    bool initialize(s16 stage_);
    //! 更新
    void update(s16 selNum_, bool hit_mouse_point_);
    //! 描画
    void render();
    //! 解放
    void finalize();

public:
    //! 索敵(taskManagerで更新)
    bool search_d(VECTOR& fc_pos_, s16 f_size_, s16 i_);

    //! メインターゲット設定
    void setMainTarget(VECTOR& main_fc_pos_);

    //! 敵のHPが0になったらMOVEに
    void setMove(s16 hp_);

    //! 各ダメージ処理
    void damage_a(bool isAtk_, f32 atk_, s16 i_, TYPE type_);
    void damage_b(bool isAtk_, f32 atk_, s16 i_, TYPE type_);
    void damage_c(bool isAtk_, f32 atk_, s16 i_, TYPE type_);
    void damage_d(bool isAtk_, f32 atk_, s16 i_);

    //! 消滅処理
    void deleteObj_a();
    void deleteObj_b();
    void deleteObj_c();
    void deleteObj_d();
    //! 消滅処理まとめる
    void deleteObj();

    //! マウスと画面の当たり判定
    void setScreenPos();
    //! マウスで配置
    void setUnit();

    //! ゲームフィールド内外判定
    bool isOut();

    //! ステージごとのユニットの使用上限設定
    void unitLimit(s16 stage_);

    //! カウンター
    void count();

    //! 敵の索敵範囲で左クリック
    void errorCleckEnemy(VECTOR pos_);

    //! ユニットの残がない状態で左クリック
    void errorCleckUnit(VECTOR pos_);

    //! フィールドにいるユニットと手持ちのユニットが０になったらゲームオーバー
    void gameOver();

    //! TYPEBの攻撃アニメーション
    void atkMoveTypeB(VECTOR fac_pos_, f32 fac_size_, STATE state_);

private:
public:
    //! ゲッター
    VECTOR pos_a(s16 i_) const;
    s16    size_a(s16 i_) const;

    //! ゲッター
    VECTOR pos_b(s16 i_) const;
    s16    size_b(s16 i_) const;

    //! ゲッター
    VECTOR pos_c(s16 i_) const;
    s16    size_c(s16 i_) const;

    //! ゲッター
    VECTOR pos_d(s16 i_) const;
    s16    size_d(s16 i_) const;
    bool   isAtk_d(s16 i_) const;
    f32    atk_d(s16 i_) const;

    TYPE TYPE_D(s16 i_) const;

    //! インスタンスのヌルチェック
    bool checkInstance_a();
    bool checkInstance_b();
    bool checkInstance_c();
    bool checkInstance_d();

    std::vector<s16> unit_limit();

    //! taskManagerで敵の索敵範囲とマウスポインタの当たり判定するよう
    HITRESULT_LINE GetMousePosition() { return ScreenPos; }

    //ScreenPosとfactoryの索敵判定
    bool hit_ScreenPos_to_factory(VECTOR pos_, u32 r_);

    UnitTypeA* typeA(u32 index_) const { return _units_a[index_].get(); }
    UnitTypeB* typeB(u32 index_) const { return _units_b[index_].get(); }
    UnitTypeC* typeC(u32 index_) const { return _units_c[index_].get(); }
    UnitTypeD* typeD(u32 index_) const { return _units_d[index_].get(); }

public:
    //! 実体のサイズ
    s16 unitTypeASize();
    s16 unitTypeBSize();
    s16 unitTypeCSize();
    s16 unitTypeDSize();

private:
    //! ユニットのユニークポインター
    std::vector<std::unique_ptr<UnitTypeA>> _units_a;
    std::vector<std::unique_ptr<UnitTypeB>> _units_b;
    std::vector<std::unique_ptr<UnitTypeC>> _units_c;
    std::vector<std::unique_ptr<UnitTypeD>> _units_d;

    //! 現在配置しているユニット
    size _size;

    //! マウスクリックで配置する用
    //! 画面上の座標をワールド座標に変換するための変数
    VECTOR         Start3DPos, End3DPos;
    HITRESULT_LINE ScreenPos;

    int  _mouse_x, _mouse_y;   //! マウスの座標
    int  _click;               //! 入力情報
    bool _span;                //! 配置する間隔
    int  _count;               //! 配置する間隔

    s16 _selNum;   //! 今選択しているユニット

    //! ステージごとのユニット使用上限
    std::vector<s16> _unit_limit;

    //! 敵の索敵範囲とマウスポインタの当たり判定
    bool _hit_mouse_point;

    //! 敵の索敵範囲で左クリック
    bool _errorCleckEnemy;

    //! ユニットの残がない状態で左クリック
    bool _errorCleckUnit;

    //! ゲームオーバー用変数
    int _go_alpha;
    int _go_text_alpha;
};
