//---------------------------------------------------------------------------
//!	@file	unitTypeB.cpp
//!	@brief	UnitTypeBの実装
//---------------------------------------------------------------------------
#include "unitTypeC.h"

//---------------------------------------------------------------------------
//! コンストラクタ
//---------------------------------------------------------------------------
UnitTypeC::UnitTypeC()
{
    // ユニットの種類
    _type = TYPE::TYPE_C;
    _pos  = VGet(0, 0, 0);   // 位置座標
                             // _size = 0.04f;           // 図形描画の際のサイズ
    _HP         = 40;
    par._hp     = _HP;    // 耐久値
    par._atk    = 1;      // 攻撃力
    par._def    = 0;      // 耐久力
    par._movSpd = 0.1f;   // 進軍速度
    par._atkSpd = 150;     //攻撃速度(_atkSpd フレームに一度)

    // 当たり判定用の変数(索敵)
    _hit._hcPos   = VGet(_pos.x, _pos.y, _pos.z);   // 現在位置
    _hit._hcScale = 20;                             // サイズ
    _hit._hcSpace = 0;                              // 間隔

    // 当たり判定用の変数(攻撃)
    _hitAtk._hcPos   = VGet(_pos.x, _pos.y, _pos.z);   // 現在位置
    //_hitAtk._hcScale = 1;                              // サイズ
    //_hitAtk._hcSpace = 200;
    _hitAtk._hcScale = 10;
    _hitAtk._hcSpace = 0;


    // モデル（カメ）
    _model = std::make_unique<Model>();   // 実態作成

    // 行列
    _mat = MGetIdent();                            // 単位行列を取得
    _mat = MGetScale(VGet(0.07f, 0.07f, 0.07f));   // サイズ指定

    _modelDead = false;
    _alpha     = 255;

    // カメのモデルの動きようタイマー
    _dead_timer = 20;
}

//---------------------------------------------------------------------------
//! デストラクタ
//---------------------------------------------------------------------------
UnitTypeC::~UnitTypeC()
{
}

//---------------------------------------------------------------------------
//! 初期化
//---------------------------------------------------------------------------
bool UnitTypeC::initialize()
{
    SetUseTransColor(FALSE);
    UnitBase::initialize("data/Unit/Unit.mqo", "data/Unit/unitTypeC.png");
    _model.get()->load("data/Unit/kame.mqo");
    //! モデルの初期座標設定(マトリックス設定)
    MV1SetMatrix(_model.get()->handle(), _mat);
    _graphHandle = LoadGraph("data/Unit/kame2.png");

    return true;
}
//---------------------------------------------------------------------------
//! 更新
//---------------------------------------------------------------------------
void UnitTypeC::update()
{
    UnitBase::update();

    if((_state == STATE::MOVE)) {
        //! マトリックスの座標に現在位置を入れる
        _mat.m[3][0] = _pos.x;
        _mat.m[3][1] = 0;
        _mat.m[3][2] = _pos.z;
    }

    _pos.y = 7;
    modelMove();
    modelDead();

    MV1SetTextureGraphHandle(_model.get()->handle(), 0, _graphHandle, false);

    MV1SetUseVertDifColor(_model.get()->handle(), true);
    MV1SetUseVertSpcColor(_model.get()->handle(), true);

    //! マトリックス設定
    MV1SetMatrix(_model.get()->handle(), _mat);
}
//---------------------------------------------------------------------------
//! 描画
//---------------------------------------------------------------------------
void UnitTypeC::render()
{
    _model.get()->draw();
    UnitBase::render();
}

//---------------------------------------------------------------------------
//! 解放
//---------------------------------------------------------------------------
void UnitTypeC::finalize()
{
    UnitBase::finalize();
}

//---------------------------------------------------------------------------
//! モデルそのものの動き
//---------------------------------------------------------------------------
void UnitTypeC::modelMove()
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
    _mat = MScale(_mat, _size);

    //! マトリックスの座標に現在位置を入れる
    _mat.m[3][0] = _pos.x;

    _mat.m[3][2] = _pos.z;
}

//---------------------------------------------------------------------------
//! モデルの消滅モーション
//---------------------------------------------------------------------------
void UnitTypeC::modelDead()
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

    //! ２つのベクトルの内積を取得

    //! マトリックスを使ったモデルの回転
    _mat = MGetRotY(_dir);
    //! MGetRotYでなぜかscaleが1になるので強制変更
    _mat = MScale(_mat, _size);

    //! マトリックスの座標に現在位置を入れる
    _mat.m[3][0] = _pos.x;

    _mat.m[3][2] = _pos.z;

    //! 方向転換
    direction(dir);

    // //! Unitの座標に正規化した方向ベクトルを足す
    _pos = VAdd(_pos, dir);

    if(_pos.x <= -140) {
        _modelDead = true;
    }
}
//---------------------------------------------------------------------------
//! モデルの方向転換
//---------------------------------------------------------------------------
void UnitTypeC::direction(VECTOR dir_)
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
