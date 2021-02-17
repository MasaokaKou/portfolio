//---------------------------------------------------------------------------
//!	@file	unitTypeD.cpp
//!	@brief	UnitTypeDの実装
//---------------------------------------------------------------------------
#include "unitTypeD.h"

//---------------------------------------------------------------------------
//! コンストラクタ
//---------------------------------------------------------------------------
UnitTypeD::UnitTypeD()
{
    //! ユニットの種類
    _type = TYPE::TYPE_D;
    _pos  = VGet(0, 10, 0);   //! 位置座標
    //_size = 0.03f;            //! 図形描画の際のサイズ

    _HP         = 6;
    par._hp     = _HP;    //! 耐久値
    par._atk    = -5;     //! 攻撃力
    par._def    = 0;      //! 耐久力
    par._movSpd = 0.2f;   //! 進軍速度
    par._atkSpd = 240;    //!攻撃速度(_atkSpd フレームに一度)

    //! 当たり判定用の変数(索敵)
    _hit._hcPos   = VGet(_pos.x, _pos.y, _pos.z);   //! 現在位置
    _hit._hcScale = 50;                             //! サイズ
    _hit._hcSpace = 0;                              //! 間隔

    //! 当たり判定用の変数(攻撃)
    _hitAtk._hcPos   = VGet(_pos.x, _pos.y, _pos.z);   //! 現在位置
    _hitAtk._hcScale = 20;                             //! サイズ
    _hitAtk._hcSpace = 1;

    //! 乗り物のモデル（クリオネ）
    _ride_model = std::make_unique<Model>();   //! 実態作成
    //! 攻撃用のモデル
    _atk_circle = std::make_unique<Model>();   //! 実態作成
    _atk_alpha  = 0;
    _atk_scale  = 0.01f;

    //! 行列
    _mat       = MGetIdent();                         //! 単位行列を取得
    _mat       = MGetScale(VGet(1.8f, 1.8f, 1.8f));   //! サイズ指定
    _modelDead = false;

    //! カメのモデルの動きようタイマー
    _dead_timer = 20;
}

//---------------------------------------------------------------------------
//! デストラクタ
//---------------------------------------------------------------------------
UnitTypeD::~UnitTypeD()
{
}

//---------------------------------------------------------------------------
//! 初期化
//---------------------------------------------------------------------------
bool UnitTypeD::initialize()
{
    SetUseTransColor(FALSE);
    UnitBase::initialize("data/Unit/Unit.mqo", "data/Unit/unitTypeD.png");
    _ride_model->load("data/Unit/kurione.mqo");
    _atk_circle->load("data/Unit/unitTypeD-Atk.mqo");

    //! モデルの初期座標設定(マトリックス設定)
    MV1SetMatrix(_ride_model->handle(), _mat);
    // _graphHandle = LoadGraph("data/kurione.png");
    _graphHandle = LoadGraph("data/Unit/kuro.png");

    return true;
}
//---------------------------------------------------------------------------
//! 更新
//---------------------------------------------------------------------------
void UnitTypeD::update()
{
    UnitBase::update();

    //MV1SetTextureGraphHandle(_ride_model.get()->handle(), 0, _graphHandle, false);

    if((_state == STATE::MOVE)) {
        //! マトリックスの座標に現在位置を入れる
        _mat.m[3][0] = _pos.x;
        _mat.m[3][1] = -5;
        _mat.m[3][2] = _pos.z;
    }

    if((_state == STATE::ATTACK)) {
        _hitAtk._hcScale = 40;
    }

    else {
        _hitAtk._hcScale = 20;
    }
    _pos.y = 10;

    modelMove();
    modelDead();

    MV1SetUseVertDifColor(_ride_model->handle(), true);
    MV1SetUseVertSpcColor(_ride_model->handle(), true);

    //! 回復モーション更新
    atkAnimUpdate();

    //! マトリックス設定
    MV1SetMatrix(_ride_model->handle(), _mat);
}
//---------------------------------------------------------------------------
//! 描画
//---------------------------------------------------------------------------
void UnitTypeD::render()
{
    _ride_model->draw();

    UnitBase::render();
    //! 回復モーション描画
    atkAnimDraw();
}

//---------------------------------------------------------------------------
//! 解放
//---------------------------------------------------------------------------
void UnitTypeD::finalize()
{
    UnitBase::finalize();
}

//---------------------------------------------------------------------------
//! モデルの消滅モーション
//---------------------------------------------------------------------------
void UnitTypeD::modelMove()
{
    if(isDead())
        return;

    //! モデルから攻撃用当たり判定へのベクトル作成
    VECTOR dir;

    //! モデルの座標から攻撃用当たり判定の座標を引く
    dir = VSub(_hitAtk._hcPos, VGet(_mat.m[3][0], _mat.m[3][1], _mat.m[3][2]));

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
    _mat = MGetRotY(_dir);
    //! MGetRotYでなぜかscaleが1になるので強制変更
    _mat = MScale(_mat, 0.1f);
    //_mat = MScale(_mat, 1);
    //! マトリックスの座標に現在位置を入れる
    _mat.m[3][0] = _pos.x;
    _mat.m[3][1] = -5;
    _mat.m[3][2] = _pos.z;
}

//---------------------------------------------------------------------------
//! モデルの消滅モーション
//---------------------------------------------------------------------------
void UnitTypeD::modelDead()
{
    if(!isDead())
        return;

    //! モデルから攻撃用当たり判定へのベクトル作成
    VECTOR dir;

    //! モデルの座標から攻撃用当たり判定の座標を引く
    dir = VSub(VGet(-150, 0, -150), VGet(_mat.m[3][0], _mat.m[3][1], _mat.m[3][2]));
    // 正規化
    dir = VNorm(dir);

    // Unitの右方向のベクトルを作成
    // 右向きなので90.0ｆ
    float side_rot = _dir + TO_RADIAN(180.0f);

    _side.x += cosf(side_rot);
    _side.z -= sinf(side_rot);

    //! 正規化
    _side = VNorm(_side);

    direction(dir);

    //! マトリックスを使ったモデルの回転
    _mat = MGetRotY(_dir);
    //! MGetRotYでなぜかscaleが1になるので強制変更
    //  _mat = MScale(_mat, _size);
    _mat = MScale(_mat, 0.1f);
    //! マトリックスの座標に現在位置を入れる
    _mat.m[3][0] = _pos.x;

    _mat.m[3][2] = _pos.z;

    // //! Unitの座標に正規化した方向ベクトルを足す
    _pos = VAdd(_pos, dir);

    if(_pos.x <= -140) {
        _modelDead = true;
    }
}
//---------------------------------------------------------------------------
//! モデルの方向転換
//---------------------------------------------------------------------------
void UnitTypeD::direction(VECTOR dir_)
{
    // 内積の値がプラスかマイナスで回転方向を決める
    //! (Unitからプレイヤーの方向ベクトル作成 , Unitの右方向のベクトルを作成)
    float side_dot = VDot(_side, dir_);

    if(_dead_timer < 0) {
        return;
    }

    if(side_dot > 0.0f) {
        _dir += TO_RADIAN(10.0f);
    }
    // 内積の値がマイナスの時は
    if(side_dot < 0.0f) {
        _dir -= TO_RADIAN(10.0f);
    }

    _dead_timer--;
}

//---------------------------------------------------------------------------
//! 回復モーション更新
//---------------------------------------------------------------------------
void UnitTypeD::atkAnimUpdate()
{
    //! 回復モーション配置
    _atk_circle->setScale(VGet(_atk_scale, _atk_scale, _atk_scale));
    _atk_circle->setPos(_pos);

    if(_state != STATE::ATTACK) {
        if(_atk_scale >= 0) {
            _atk_scale -= 0.02f;
        }
    }

    if(_state == STATE::ATTACK) {
        if(_atk_scale <= 0.45f) {
            _atk_scale += 0.02f;
        }
    }
}

//---------------------------------------------------------------------------
//! 回復モーション描画
//---------------------------------------------------------------------------
void UnitTypeD::atkAnimDraw()
{
    _atk_circle->draw();
}
