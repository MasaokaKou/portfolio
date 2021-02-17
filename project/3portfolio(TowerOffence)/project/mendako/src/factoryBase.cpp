
//---------------------------------------------------------------------------
//!	@file	factoryBase.cpp
//!	@brief	FactoryBase
//---------------------------------------------------------------------------
#include "factoryBase.h"
//===========================================================================
//! 防衛施設
//===========================================================================

//---------------------------------------------------------------------------
//! コンストラクタ
//---------------------------------------------------------------------------
FactoryBase ::FactoryBase()
{
    // 位置座標
    _pos = VGet(40, 0, 40);
    // 図形描画の際のサイズ
    _size = 0.01f;

    _dir = TO_RADIAN(180.0f) * 0;

    par._hp     = 100;   //< 耐久値
    par._atk    = 1;     //< 攻撃力
    par._def    = 0;     //< 耐久力
    par._atkSpd = 60;    //< 攻撃速度

    _isAtk    = false;   //< 攻撃中かどうか
    _atkCount = 0;       //< 攻撃用のカウント

    // 当たり判定用の変数
    _hit._hcPos   = VGet(_pos.x, _pos.y, _pos.z);   //< 現在位置
    _hit._hcScale = 15;                             //< サイズ

    // 攻撃用当たり判定用の変数
    _hitAtk._hcPos   = VGet(_pos.x, _pos.y, _pos.z);   //< 現在位置
    _hitAtk._hcScale = 5;                              //< サイズ
    _hitAtk._hcSpace = 8;

    _state = STATE::WAIT;   //< 現在の状態

    _isDamage = false;   //< 攻撃されているかどうか

    // モデル
    _model = std::make_unique<Model>();   //< 実態作成

    // 行列
    _matRot = MGetIdent();                            //< 単位行列を取得
    _matRot = MGetScale(VGet(_size, _size, _size));   //< サイズ指定

    // HpBarの実体
    _hpBar = std::make_unique<HpBar>();

    // 死亡時のアニメーション
    _is_dead = false;

    //! 攻撃アニメーション
    _is_reset  = true;
    _color     = WHITE;
    _atk_size  = 1;
    _atk_alpha = 255;
    _count     = 0;
}

//---------------------------------------------------------------------------
//! デストラクタ
//---------------------------------------------------------------------------
FactoryBase ::~FactoryBase()
{
}

//---------------------------------------------------------------------------
//! 初期化
//---------------------------------------------------------------------------
bool FactoryBase::initialize(const char* modelName_, const char* materialName_)
{
    //! モデルの読み込み
    _model->load(modelName_);
    //! モデルの初期座標設定(マトリックス設定)
    MV1SetMatrix(_model->handle(), _matRot);

    //! モデルにテクスチャを張り付け
    _graphHandle = LoadGraph(materialName_);
    MV1SetTextureGraphHandle(_model->handle(), 0, _graphHandle, false);

    if(_hpBar) {
        _hpBar->initialize(par._hp);
    }

    return true;
}

//---------------------------------------------------------------------------
//! 更新
//---------------------------------------------------------------------------
void FactoryBase::update()
{
    switch(_state) {
        case STATE::WAIT:

            movHit();

            _atk_pos = VGet(_pos.x, _pos.y, _pos.z);
            break;

        case STATE::MOVE:

            _atk_pos = VGet(_pos.x, _pos.y, _pos.z);

            break;

        case STATE::ATTACK:

            movHit();
            attack();
            visibleAttack();

            break;

        case STATE::DEATH:

            deadAnim();

            break;

        default:

            break;
    }

    //! マトリックスの座標に現在位置を入れる
    setMat();

    //! 当たり判定用の変数
    _hit._hcPos    = VGet(_pos.x, _pos.y, _pos.z);   //! 現在位置
    _hitAtk._hcPos = VGet(_pos.x, _pos.y, _pos.z);   //! 現在位置

    //! HpBarの更新
    hpbarUpdate();

    ////! マトリックス設定
    MV1SetMatrix(_model->handle(), _matRot);

    //! 死亡時の挙動
    dead();
}
//---------------------------------------------------------------------------
//! 描画
//---------------------------------------------------------------------------
void FactoryBase::render()
{
    //DrawSphere3D(_pos, _size, 5, BLACK, BLACK, false);

    _model->draw();

    movHit();

    //! HpBar
    if(_hpBar)
        _hpBar->render();

    SetUseLighting(false);
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _atk_alpha);
    DrawSphere3D(_atk_pos, _atk_size, 5, _color, _color, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    SetUseLighting(true);

    //! 当たり判定用の球
    //DrawSphere3D(_hit._hcPos, _hit._hcScale, 5, WHITE, WHITE, false);
    //DrawSphere3D(_hitAtk._hcPos, _hitAtk._hcScale, 5, RED, RED, false);
}

//---------------------------------------------------------------------------
//! 解放
//---------------------------------------------------------------------------
void FactoryBase::finalize()
{
    //! HpBar
    if(_hpBar)
        _hpBar->finalize();
}

//---------------------------------------------------------------------------
//! 索敵(taskManagerで更新)
//---------------------------------------------------------------------------
bool FactoryBase::search(VECTOR& e_pos_, s16 e_size_)
{
    if(_state == STATE::DEATH)
        return false;

    if(hit(_hit._hcPos, _hit._hcScale, e_pos_, e_size_)) {
        direction(e_pos_);
        _target = e_pos_;

        return true;
    }

    return false;
}

//---------------------------------------------------------------------------
//! 攻撃開始使用当たり判定
//---------------------------------------------------------------------------
bool FactoryBase::atkSearch(VECTOR& e_pos_, s16 e_size_, int unit_hp_)
{
    if(_state == STATE::DEATH)
        return false;

    if(unit_hp_ <= 0)
        return false;

    if(hit(_hitAtk._hcPos, _hitAtk._hcScale, e_pos_, e_size_)) {
        _state = STATE::ATTACK;   //! 現在の状態

        return true;
    }

    return false;
}

//---------------------------------------------------------------------------
//! 一定速度でユニットにダメージを与える
//---------------------------------------------------------------------------
void FactoryBase::attack()
{
    if(_atkCount % par._atkSpd == 0) {
        _isAtk = true;
    }
    else {
        _isAtk = false;
    }

    _atkCount++;

    if(_atkCount >= par._atkSpd)
        _atkCount = 0;
}

//---------------------------------------------------------------------------
//! ダメージ処理
//---------------------------------------------------------------------------
void FactoryBase::damage(f32 atk)
{
    if(_isDamage)
        par._hp -= atk;
}

//---------------------------------------------------------------------------
//! 方向転換
//---------------------------------------------------------------------------
void FactoryBase::direction(VECTOR& fc_pos_)
{
    //! Unitからプレイヤーの方向ベクトル作成
    VECTOR dir;

    //! Unitの座標から防衛施設の座標を引く
    dir = VSub(fc_pos_, _pos);

    // 正規化
    dir = VNorm(dir);

    // Unitの右方向のベクトルを作成
    // 右向きなので90.0ｆ
    float side_rot = _dir + TO_RADIAN(180.0f);

    _side.x += cosf(side_rot);
    _side.z -= sinf(side_rot);

    //! 正規化
    _side = VNorm(_side);

    //! ２つのベクトルの内積を取得
    //! (Unitからプレイヤーの方向ベクトル作成 , Unitの右方向のベクトルを作成)
    float side_dot = VDot(_side, dir);

    // 内積の値がプラスかマイナスで回転方向を決める
    if(side_dot > 0.0f) {
        _dir += TO_RADIAN(1.0f);
    }
    // 内積の値がマイナスの時は
    if(side_dot < 0.0f) {
        _dir -= TO_RADIAN(1.0f);
    }

    //! マトリックスを使ったモデルの回転
    _matRot = MGetRotY(_dir);
    //! MGetRotYでなぜかscaleが1になるので強制変更
    _matRot = MScale(_matRot, _size);

    //! マトリックスの座標に現在位置を入れる
    _matRot.m[3][0] = _pos.x;
    _matRot.m[3][1] = _pos.y;
    _matRot.m[3][2] = _pos.z;

    ////! マトリックス設定
    MV1SetMatrix(_model->handle(), _matRot);
}

//---------------------------------------------------------------------------
//! 当たり判定の動き
//---------------------------------------------------------------------------
void FactoryBase::movHit()
{
    //! マトリックスのZ情報
    VECTOR vec_atk = VGet(_matRot.m[2][0], _matRot.m[2][1], _matRot.m[2][2]);

    //! 正規化
    vec_atk = VNorm(vec_atk);

    //!  間隔をかける
    mulVec(vec_atk, _hitAtk._hcSpace);

    //!  Z軸だと反対になるので反転させる
    mulVec(vec_atk, -1.0f);

    //! UnitのポジションとマトリックスのZ情報を足す
    _hitAtk._hcPos = VAdd(_pos, vec_atk);
}

//---------------------------------------------------------------------------
//!　索敵当たり判定用変数
//---------------------------------------------------------------------------
VECTOR FactoryBase::hitPos()
{
    return _hit._hcPos;
}
s16 FactoryBase::hitSize()
{
    return _hit._hcScale;
}

//---------------------------------------------------------------------------
//! 敵の本拠地のサイズを変える
//---------------------------------------------------------------------------
void FactoryBase::setMainTower()
{
    _matRot = MGetScale(VGet(0.02f, 0.02f, 0.02f));

    //! マトリックスの座標に現在位置を入れる
    _matRot.m[3][0] = 60;
    _matRot.m[3][1] = 0;
    _matRot.m[3][2] = 60;

    ////! マトリックス設定
    MV1SetMatrix(_model->handle(), _matRot);
}

//---------------------------------------------------------------------------
//! 死亡
//---------------------------------------------------------------------------
void FactoryBase::dead()
{
    if(par._hp <= 0) {
        _state = STATE::DEATH;
    }
}

//---------------------------------------------------------------------------
//! 死亡時のアニメーション
//---------------------------------------------------------------------------
void FactoryBase::deadAnim()
{
    _pos.y -= 1.0f;

    if(_pos.y <= -15) {
        _is_dead = true;
    }
}

//---------------------------------------------------------------------------
//! 死亡時のアニメーションが終わったかどうか
//---------------------------------------------------------------------------
bool FactoryBase::endAnimOfDead()
{
    if(_is_dead) {
        return true;
    }
    return false;
}

//---------------------------------------------------------------------------
//! マトリックスを設定
//---------------------------------------------------------------------------
void FactoryBase::setMat()
{
    _matRot.m[3][0] = _pos.x;
    _matRot.m[3][1] = _pos.y;
    _matRot.m[3][2] = _pos.z;
}

//---------------------------------------------------------------------------
//! HpBarの更新
//---------------------------------------------------------------------------
void FactoryBase::hpbarUpdate()
{
    if(_hpBar) {
        _hpBar->prPos(_pos);

        _hpBar->setHp(par._hp);

        _hpBar->type(_type);

        _hpBar->update();

        _hpBar->setPos(VGet(-20, -60, 0));
    }
}

//---------------------------------------------------------------------------
//! 攻撃を可視化する
//---------------------------------------------------------------------------
void FactoryBase::visibleAttack()
{
    if(_is_reset) {
        _atk_pos = VGet(_pos.x, _pos.y + 15, _pos.z);

        if(_type == TYPE::TYPE_C)
            _atk_pos = VGet(_pos.x, _pos.y + 50, _pos.z);

        _is_reset  = false;
        _count     = 0;
        _atk_alpha = 255;
        _atk_size  = 1;
    }

    //! Unitからプレイヤーの方向ベクトル作成
    VECTOR dir;

    //! Unitの座標から防衛施設の座標を引く
    dir = VSub(_target, _atk_pos);

    // 正規化
    dir = VNorm(dir);

    if(_type == TYPE::TYPE_C)
    dir = VScale(dir, par._atkSpd * 0.002f);

    _atk_pos = VAdd(_atk_pos, dir);

    _count++;

    if(_count > par._atkSpd) {
        _is_reset = true;
    }
}

//---------------------------------------------------------------------------
//! 爆発アニメーション
//---------------------------------------------------------------------------
void FactoryBase::attackAnimTypeA()
{
    if(_count < par._atkSpd * 0.6f)
        return;

    _atk_size += 0.7f;
    _atk_alpha -= 30;
}

void FactoryBase::attackAnimTypeC()
{
    if(_count < par._atkSpd * 0.9f)
        return;

    _atk_size += 2;
    _atk_alpha -= 30;
}

//---------------------------------------------------------------------------
//! attackが終わったらmoveに戻す
//---------------------------------------------------------------------------
void FactoryBase::setMove(s16 hp_)
{
    if(hp_ <= 0) {
        _atk_pos   = VGet(_pos.x, _pos.y, _pos.z);
        _state     = STATE::WAIT;
        _isAtk     = false;
        _atk_alpha = 0;
    }
}
