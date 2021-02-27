//---------------------------------------------------------------------------
//!	@file	sceneTest3.cpp
//!	@brief	Unitの当たり判定の動きの実装
//---------------------------------------------------------------------------

#pragma once

//===========================================================================
//! ユニット
//===========================================================================

class UnitBase : 
                  public BaseObject
{
public:
    UnitBase();
    ~UnitBase();

    bool initialize(const char* modelName_, const char* materialName_);   //!< 初期化
    void update();                                                      //!< 更新
    void render();                                                      //!< 描画
    void finalize();                                                    //!< 解放

    //! メンダコの登場モーション
    void startUp();
    //! 開始一秒の間回転する
    void startRotation(float side_dot_);
    //! マトリックスのあてはめ
    void setMat();

    //! 索敵
    bool search(VECTOR& fc_pos_, f32 f_size_, STATE _f_state_);

    //! 移動
    //!索敵して範囲内に施設があったらその座標を目的地にして移動
    void move(VECTOR& fc_pos_);
    void setMainTarget(VECTOR& main_fc_pos_);

    //! 方向転換
    void direction(VECTOR& fc_pos_);

    //! 当たり判定の動き
    void movHit();

    //! 一定速度でファクトリーにダメージを与える
    void attack();

    //! attackが終わったらmoveに戻す
    void setMove(s16 hp_);

    void damage(bool isAtk_, f32 atk_);

    bool getIsDamage() { return _isDamage; }
    void isDamage() { _isDamage = true; }

    //! 死亡時のモーション
    void checkMotion();
    void deadMotion();
    //! 敵が死んだらis_searchをtrueにする
    void isSearch() { _is_search = true; }

    //! HPの上限以上回復しないように
    void setMaxHitPoint();
    //! サイズ変更
    void setSize();

    //! ステータスごとに更新
    void stateUpdate();

    //! HpBarの更新
    void hpbarUpdate();

public:
    //! ユニットの種類
    TYPE type();

private:
    VECTOR _oldPos;   //!< 一フレーム前の座標

protected:
    //! 向かう施設
    VECTOR _targetPos;

    //!最初の索敵が終わり次第索敵を切る
    VECTOR _fc_pos;
    bool   _is_search;
};
