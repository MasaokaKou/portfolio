//---------------------------------------------------------------------------
//!	@file	sceneTest3.cpp
//!	@brief	enemyの当たり判定の動きの実装
//---------------------------------------------------------------------------

//===========================================================================
//! エネミー
//===========================================================================

//---------------------------------------------------------------------------
//! コンストラクタ
//---------------------------------------------------------------------------
SceneGameTest3 ::SceneGameTest3()
{
    _pos    = VGet(0, 0, 0);   //! 位置座標
    _oldPos = VGet(0, 0, 0);
    _dir    = TO_RADIAN(180.0f) * 0;
    _size   = 5;   //! 図形描画の際のサイズ

    par._hp     = 0;      //! 耐久値
    par._atk    = 0;      //! 攻撃力
    par._def    = 0;      //! 耐久力
    par._movSpd = 0.1f;   //! 進軍速度
    par._atkSpd = 0;      //! 攻撃速度

    _state = STATE::MOVE;   //! 現在の状態

    _targetPos = VGet(0, 0, 0);   //! 向かう施設

    //! 当たり判定用の変数
    _hcPos   = VGet(_pos.x, _pos.y, _pos.z + 5);   //! 現在位置
    _hcScale = 5;                                  //! サイズ
    _hcSpace = 10;                                  //! 間隔

    //! モデル
    _model = std::make_unique<Model>();   //! 実態作成

    //! 行列
    _matRot = MGetIdent();                            //! 単位行列を取得
    _matRot = MGetScale(VGet(_size, _size, _size));   //! サイズ指定
}

//---------------------------------------------------------------------------
//! デストラクタ
//---------------------------------------------------------------------------
SceneGameTest3 ::~SceneGameTest3()
{
}

//---------------------------------------------------------------------------
//! 初期化
//---------------------------------------------------------------------------
bool SceneGameTest3::initialize()
{
    //! モデルの読み込み
    _model.get()->load("data/sphereDebug.mqo");
    //! モデルの初期座標設定(マトリックス設定)
    MV1SetMatrix(_model.get()->handle(), _matRot);

    return true;
}

//---------------------------------------------------------------------------
//! 更新
//---------------------------------------------------------------------------
void SceneGameTest3::update()
{
    switch(_state) {
        case STATE::WAIT:
            break;
        case STATE::MOVE:

            //! 当たり判定確かめるため
            search(VGet(0, 0, 0), VGet(0, 0, 0));

            //! 移動
            move(_targetPos);

            //! 当たり判定の動き
            movHit();

            break;
        case STATE::ATTACK:
            break;
        case STATE::DEATH:
            break;
        default:
            break;
    }
}
//---------------------------------------------------------------------------
//! 描画
//---------------------------------------------------------------------------
void SceneGameTest3::render()
{
    _model.get()->draw();

    switch(_state) {
        case STATE::WAIT:
            break;
        case STATE::MOVE:
            break;
        case STATE::ATTACK:
            break;
        case STATE::DEATH:
            break;
        default:
            break;
    }

#ifdef _DEBUG
#if 1

    //! 当たり判定用の球
    DrawSphere3D(_hcPos, _hcScale, 5, WHITE, WHITE, false);

    //! 座標描画
    DrawString(0, 20, "PosX", WHITE);
    chengeText((s16)_pos.x, 50, 20, 255, 255, 255);
    DrawString(0, 40, "PosZ", WHITE);
    chengeText((s16)_pos.z, 50, 40, 255, 255, 255);

    //! ステータス描画
    switch(_state) {
        case STATE::WAIT:
            DrawString(0, 60, "STATE:", WHITE);
            DrawString(55, 60, "WAIT", WHITE);
            break;
        case STATE::MOVE:
            DrawString(0, 60, "STATE:", WHITE);
            DrawString(55, 60, "MOVE", WHITE);
            break;
        case STATE::ATTACK:
            DrawString(0, 60, "STATE:", WHITE);
            DrawString(55, 60, "ATTACK", WHITE);
            break;
        case STATE::DEATH:
            DrawString(0, 60, "STATE:", WHITE);
            DrawString(55, 60, "DEATH", WHITE);
            break;
        default:
            break;
    }

#endif   // 0

#endif   // _DEBUG
}

//---------------------------------------------------------------------------
//! 解放
//---------------------------------------------------------------------------
void SceneGameTest3::finalize()
{
}

//---------------------------------------------------------------------------
//! 索敵用当たり判定
//---------------------------------------------------------------------------
bool SceneGameTest3::hit(VECTOR& p0, f32 r0, VECTOR& p1, f32 r1)
{
    VECTOR v;
    // p0からp1を引いて円同士の距離を出す
    v = VSub(p0, p1);

    // 判定用
    f32 length = sqrtf(v.x * v.x + v.z * v.z);

    //  最初に出した距離と二つの半径を足したものを比べる
    if(length < r0 + r1) {
        //　p0からp1を引いて円同士の距離をのほうが小さければtrue
        return true;
    }

    return false;
}

//---------------------------------------------------------------------------
//! 索敵(taskManagerで更新)
//---------------------------------------------------------------------------
void SceneGameTest3::search(VECTOR& fc_pos, VECTOR& main_fc_pos)
{
    //!(仮)
    VECTOR pos  = VGet(20, 0, -30);
    f32    size = 5;

    DrawSphere3D(pos, size, 5, BLACK, BLACK, false);

    _targetPos = pos;

    // if(hit(_hcPos, _hcScale, pos, size)) {
    //     //! 索敵範囲に防衛施設があればそこへ
    //     _targetPos = fc_pos;
    //
    //     DrawString(0, 80, "IsHit:", WHITE);
    //     DrawString(55, 80, "TRUE", WHITE);
    // }
    // else {
    //     //! 無ければ本拠地へ向かう
    //     _targetPos = main_fc_pos;
    //     DrawString(0, 80, "IsHit:", WHITE);
    //     DrawString(55, 80, "FALSE", WHITE);
    // }
}

//---------------------------------------------------------------------------
//! 移動
//!索敵して範囲内に施設があったらその座標を目的地にして移動
//---------------------------------------------------------------------------
void SceneGameTest3::move(VECTOR& fc_pos)
{
    //! enemyからプレイヤーの方向ベクトル作成
    VECTOR dir;

    //! enemyの座標から防衛施設の座標を引く
    dir = VSub(fc_pos, _pos);

    // 正規化
    dir = VNorm(dir);

    //! 正規化したベクトルに速度をかける
    dir = VScale(dir, par._movSpd);

    // //! enemyの座標に正規化した方向ベクトルを足す
    _pos = VAdd(_pos, dir);

#ifdef _DEBUG

    if(CheckHitKey(KEY_INPUT_LEFT))
        _dir += 0.1f;
    if(CheckHitKey(KEY_INPUT_RIGHT))
        _dir -= 0.1f;

    if(CheckHitKey(KEY_INPUT_UP)) {
        _pos.x += par._movSpd * cosf(_dir);
        _pos.z += par._movSpd * sinf(_dir);
    }

#endif   // _DEBUG

    //! 方向転換
    direction(fc_pos);

    //! 一フレーム前の座標
    _oldPos = VGet(_pos.x, _pos.y, _pos.z);
}

//---------------------------------------------------------------------------
//! 方向転換
//---------------------------------------------------------------------------
void SceneGameTest3::direction(VECTOR& fc_pos)
{
    //! enemyからプレイヤーの方向ベクトル作成
    VECTOR dir;

    //! enemyの座標から防衛施設の座標を引く
    dir = VSub(fc_pos, _pos);

    // 正規化
    dir = VNorm(dir);

    // enemyの右方向のベクトルを作成
    // 右向きなので90.0ｆ
    float side_rot = _dir + TO_RADIAN(180.0f);

    _side.x += cosf(side_rot);
    _side.z -= sinf(side_rot);

    //! 正規化
    _side = VNorm(_side);

    //! ２つのベクトルの内積を取得
    //! (enemyからプレイヤーの方向ベクトル作成 , enemyの右方向のベクトルを作成)
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
    _matRot.m[3][2] = _pos.z;

    //! マトリックス設定
    MV1SetMatrix(_model.get()->handle(), _matRot);
}

//---------------------------------------------------------------------------
//! 当たり判定の動き
//---------------------------------------------------------------------------
void SceneGameTest3::movHit()
{
    //! マトリックスのZ情報
    VECTOR vec = VGet(_matRot.m[2][0], _matRot.m[2][1], _matRot.m[2][2]);

    //! 正規化
    vec = VNorm(vec);

    //!  間隔をかける
    mulVec(vec, _hcSpace);
    //

    //!  Z軸だと反対になるので反転させる
    mulVec(vec, -1.0f);

    //! enemyのポジションとマトリックスのZ情報を足す
    _hcPos = VAdd(_pos, vec);

#ifdef _DEBUG
#if 1
    // _motRotrix の値を画面に表示
    DrawString(0, 300, "Ｙ軸回転行列", GetColor(255, 255, 255));
    DrawFormatString(0, 16 + 300, GetColor(255, 255, 255), "m00 %f  m01 %f  m02 %f  m03 %f",
                     _matRot.m[0][0], _matRot.m[0][1], _matRot.m[0][2], _matRot.m[0][3]);

    DrawFormatString(0, 32 + 300, GetColor(255, 255, 255), "m10 %f  m11 %f  m12 %f  m13 %f",
                     _matRot.m[1][0], _matRot.m[1][1], _matRot.m[1][2], _matRot.m[1][3]);

    DrawFormatString(0, 48 + 300, GetColor(255, 255, 255), "m20 %f  m21 %f  m22 %f  m23 %f",
                     _matRot.m[2][0], _matRot.m[2][1], _matRot.m[2][2], _matRot.m[2][3]);

    DrawFormatString(0, 64 + 300, GetColor(255, 255, 255), "m30 %f  m31 %f  m32 %f  m33 %f",
                     _matRot.m[3][0], _matRot.m[3][1], _matRot.m[3][2], _matRot.m[3][3]);

    DrawString(0, 80, "dir", WHITE);
    chengeTextF(_dir, 50, 80, 255, 255, 255);





#endif   // 0
#endif   // _DEBUG
}
