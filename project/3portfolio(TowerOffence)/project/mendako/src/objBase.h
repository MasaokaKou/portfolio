//---------------------------------------------------------------------------
//!	@file	objBase.h
//!	@brief	オブジェクトの基礎
//---------------------------------------------------------------------------

#pragma once

//===========================================================================
//!	オブジェクト基底
//===========================================================================

//! 状態設定の構造体
enum class STATE
{
    WAIT,
    MOVE,
    ATTACK,
    DEATH

};

//! 種類
enum TYPE
{
    TYPE_A,
    TYPE_B,
    TYPE_C,
    TYPE_D

};

//! ゲーム内パラメーター
struct Parameter
{
    f32 _hp;       //! 耐久値
    f32 _atk;      //! 攻撃力
    f32 _def;      //! 耐久力
    f32 _movSpd;   //! 進軍速度
    s16 _atkSpd;   //! 攻撃速度(_atkSpd フレームに一度)
};

//! //! 当たり判定用の変数(hit circle)
struct Hit
{
    VECTOR _hcPos;     //! 現在位置
    s16    _hcSpace;   //! 間隔
    s16    _hcScale;   //! サイズ
};

class BaseObject
{
public:
    BaseObject()          = default;
    virtual ~BaseObject() = default;

    virtual bool initialize() = 0;   //!> 初期化
    virtual void update()     = 0;   //!> 更新
    virtual void render()     = 0;   //!> 描画
    virtual void finalize()   = 0;   //!> 解放

public:
    //! ゲッター関数
    VECTOR pos() const { return _pos; }
    f32    hp() const { return par._hp; }
    f32    atk() const { return par._atk; }
    f32    def() const { return par._def; }
    f32    movSpd() const { return par._movSpd; }
    f32    atkSpd() const { return par._atkSpd; }
    f32    size() const { return _size; }
    bool   isAtk() const { return _isAtk; }
    STATE  state();   //! 現在の状態

    //! 死んでいるかどうか
    bool isDead() { return _is_dead; }

    //! Hｐを取ってくる
    s16 HP();

public:
    //! 座標設定
    void setPos(VECTOR pos_);

    //! 索敵用当たり判定
    bool hit(VECTOR& p0_, f32 r0_, VECTOR& p1_, f32 r1_);

    //! 攻撃フラグをいじる
    void setAtk(bool enable_) { _isAtk = enable_; }

protected:
    //! 基礎情報
    VECTOR    _pos;      //! 位置座標
    f32       _size;     //! 図形のサイズ
    f32       _dir;      //! 方向
    MATRIX    _matRot;   //! 回転行列
    VECTOR    _side;     //! objの右方向のベクトルを作成
    Parameter par;       //! パラメーター
    STATE     _state;    //! 現在の状態
    TYPE      _type;     //! ユニットの種類

    //! モデル関係
    std::unique_ptr<Model> _model;         //! モデル
    VECTOR                 _scale;         //! モデルスケール
    f32                    _alpha;         //! モデルの不透明度
    int                    _graphHandle;   //! モデルの画像用ハンドル

    //! 攻撃フラグ関係
    bool _isAtk;      //! 攻撃中かどうか
    s16  _atkCount;   //! 攻撃用のカウント
    bool _isDamage;   //! 攻撃されているかどうか

    //! 当たり判定関係
    Hit _hit;      //!　索敵当たり判定用変数
    Hit _hitAtk;   //! 攻撃当たり判定

    //! 登場モーション用変数
    s16 _startUpTimer;

    //! HPBarの実体
    std::unique_ptr<HpBar> _hpBar;   //! モデル
    s16                    _HP;      //! HPの上限

    //! 消滅モーションが終わってるかどうか
    //! UnitManagerで判定するよう。
    bool _is_dead;
};
