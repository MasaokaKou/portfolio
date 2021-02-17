//---------------------------------------------------------------------------
//!	@file	unitBase.cpp
//!	@brief	unitBase実装
//---------------------------------------------------------------------------

//===========================================================================
//! ユニット
//===========================================================================

//---------------------------------------------------------------------------
//! コンストラクタ
//---------------------------------------------------------------------------
UnitBase ::UnitBase()
{
    _pos = VGet(0, 0, 0);

    _type = TYPE::TYPE_A;

    _oldPos = VGet(0, 0, 0);
    _dir    = TO_RADIAN(180.0f) * 0;
    _size   = 0.00f;

    par._hp     = 1;      // 耐久値
    par._atk    = 1;      // 攻撃力
    par._def    = 0;      // 耐久力
    par._movSpd = 0.2f;   // 進軍速度
    par._atkSpd = 30;     // 攻撃速度(_atkSpd フレームに一度)

    _isAtk    = false;   // 攻撃中かどうか
    _atkCount = 0;       // 攻撃用のカウント

    _state = STATE::WAIT;   // 現在の状態

    _targetPos = VGet(0, 0, 0);   // 向かう施設

    // 当たり判定用の変数(索敵)
    _hit._hcPos   = VGet(_pos.x, _pos.y, _pos.z);   // 現在位置
    _hit._hcScale = 1;                              // サイズ
    _hit._hcSpace = 1;                              // 間隔

    // 当たり判定用の変数(攻撃)
    _hitAtk._hcPos   = VGet(_pos.x, _pos.y, _pos.z);   // 現在位置
    _hitAtk._hcScale = 1;                              // サイズ
    _hitAtk._hcSpace = 130;                            // 間隔

    // モデル
    _model = std::make_unique<Model>();   // 実態作成

    // 行列
    _matRot = MGetIdent();                            // 単位行列を取得
    _matRot = MGetScale(VGet(_size, _size, _size));   // サイズ指定

    _isDamage = false;   // 攻撃されているかどうか

    // 登場モーション用変数
    _startUpTimer = 30;
    _startUpTimer = 30;

    // モデルの不透明度
    _alpha = 1.0f;

    // 消滅モーションが終わっているかどうか
    _is_dead = false;

    // HpBarの実体
    _hpBar = std::make_unique<HpBar>();

    //最初の索敵が終わり次第索敵を切る
    _is_search = true;
}

//---------------------------------------------------------------------------
//! デストラクタ
//---------------------------------------------------------------------------
UnitBase ::~UnitBase()
{
}

//---------------------------------------------------------------------------
//! 初期化
//---------------------------------------------------------------------------
bool UnitBase::initialize(const char* modelName_, const char* materialName_)
{
    SetUseTransColor(FALSE);

    //! モデルの読み込み
    _model.get()->load(modelName_);
    //! モデルの初期座標設定(マトリックス設定)
    //  MV1SetMatrix(_model.get()->handle(), _matRot);
    _graphHandle = LoadGraph(materialName_);

    //! モデルにテクスチャを張り付け
    MV1SetTextureGraphHandle(_model.get()->handle(), 0, _graphHandle, false);
    //! HpBar
    if(_hpBar) {
        _hpBar.get()->initialize(par._hp);
    }

    _matRot.m[3][0] = _pos.x;
    _matRot.m[3][1] = _pos.y;
    _matRot.m[3][2] = _pos.z;

    return true;
}

//---------------------------------------------------------------------------
//! 更新
//---------------------------------------------------------------------------
void UnitBase::update()
{
    //! 消滅モーション
    checkMotion();

    //! HPの上限以上回復しないように
    setMaxHitPoint();

    //! サイズ変更
    setSize();

    //! ステータスごとに更新
    stateUpdate();

    //! HpBarの更新
    hpbarUpdate();

    //! c.d以外なら5に固定
    if(_type != TYPE::TYPE_C && _type != TYPE::TYPE_D)
        _matRot.m[3][1] = 5;

    //! マトリックス設定
    MV1SetMatrix(_model.get()->handle(), _matRot);
}
//---------------------------------------------------------------------------
//! 描画
//---------------------------------------------------------------------------
void UnitBase::render()
{
    _model.get()->draw();

    //! HpBar
    if(_hpBar)
        _hpBar.get()->render();

    //! 当たり判定用の球
    //DrawSphere3D(_hit._hcPos, _hit._hcScale, 5, WHITE, WHITE, false);
    //DrawSphere3D(_hitAtk._hcPos, _hitAtk._hcScale, 5, RED, RED, false);
}

//---------------------------------------------------------------------------
//! 解放
//---------------------------------------------------------------------------
void UnitBase::finalize()
{
    //! HpBar
    if(_hpBar)
        _hpBar.get()->finalize();
}

//---------------------------------------------------------------------------
//! メンダコの登場モーション
//---------------------------------------------------------------------------
void UnitBase::startUp()
{
    //! unitからプレイヤーの方向ベクトル作成
    VECTOR dir;

    //! unitの座標から防衛施設の座標を引く
    dir = VSub(_targetPos, _pos);
    dir = VNorm(dir);

    // 右向きなので90.0ｆ
    float side_rot = _dir + TO_RADIAN(180.0f);

    _side.x += cosf(side_rot);
    _side.z -= sinf(side_rot);

    _side = VNorm(_side);

    //! ２つのベクトルの内積を取得
    //! (unitからプレイヤーの方向ベクトル作成 , unitの右方向のベクトルを作成)
    float side_dot = VDot(_side, dir);

    //! マトリックスを使ったモデルの回転
    _matRot = MGetRotY(_dir);
    //! MGetRotYでなぜかscaleが1になるので強制変更
    _matRot = MScale(_matRot, _size);

    //! マトリックスの座標に現在位置を入れる
    setMat();

    //! 開始一秒の間回転する
    startRotation(side_dot);

    _startUpTimer--;
}
//---------------------------------------------------------------------------
//! マトリックスのあてはめ
//---------------------------------------------------------------------------
void UnitBase::setMat()
{
    _matRot.m[3][0] = _pos.x;
    _matRot.m[3][1] = _pos.y;
    _matRot.m[3][2] = _pos.z;
}

//---------------------------------------------------------------------------
//! 開始一秒の間回転する
//---------------------------------------------------------------------------
void UnitBase::startRotation(float side_dot)
{
    //! 開始一秒の間回転する
    if(_startUpTimer <= 0) {
        _state = STATE::MOVE;

        // 内積の値がプラスかマイナスで回転方向を決める
        if(side_dot > 0.0f) {
            _dir += TO_RADIAN(2.0f);
        }
        // 内積の値がマイナスの時は
        if(side_dot < 0.0f) {
            _dir -= TO_RADIAN(2.0f);
        }
    }
    else {
        _dir += TO_RADIAN(20.0f);
    }
}

//---------------------------------------------------------------------------
//! ステータスごとに更新
//---------------------------------------------------------------------------
void UnitBase::stateUpdate()
{
    switch(_state) {
        case STATE::WAIT:

            startUp();

            //! 当たり判定の動き
            movHit();

            break;

        case STATE::MOVE:

            //! 移動
            move(_targetPos);
            //! 当たり判定の動き
            movHit();

            break;
        case STATE::ATTACK:

            attack();
            movHit();

            break;

        case STATE::DEATH:

            deadMotion();
            break;
        default:
            break;
    }
}

//---------------------------------------------------------------------------
//! HpBarの更新
//---------------------------------------------------------------------------
void UnitBase::hpbarUpdate()
{
    if(_hpBar) {
        _hpBar.get()->prPos(_pos);

        _hpBar.get()->setHp(par._hp);

        _hpBar.get()->type(_type);

        _hpBar.get()->update();

        _hpBar.get()->setPos(VGet(-25, -30, 0));
    }
}

//---------------------------------------------------------------------------
//! 索敵(taskManagerで更新)  (isDamage はfactoryに渡す)
//---------------------------------------------------------------------------
bool UnitBase::search(VECTOR& fc_pos, f32 f_size, STATE _f_state)
{
    //! 敵が死んでいたらスルー
    if(_f_state == STATE::DEATH) {
        return false;
    }

    //! 登場モーション中はretrun false
    if(_state == STATE::WAIT)
        return false;

    if(hit(_hit._hcPos, _hit._hcScale, fc_pos, f_size)) {
        //! 索敵範囲に防衛施設があればそこへ
        if(_is_search) {
            _fc_pos = fc_pos;
            if(_type != TYPE::TYPE_D)
                _is_search = false;
        }

        //! 攻撃用当たり判定に入ってたら攻撃開始

        if(hit(_hitAtk._hcPos, _hitAtk._hcScale, fc_pos, f_size)) {
            _state = STATE::ATTACK;   //! 現在の状態

            return true;
        }
        else {
            if(_type == TYPE::TYPE_D) {
                _state = STATE::MOVE;
                _isAtk = false;
            }
        }
    }

    if(!_is_search) {
        _targetPos = _fc_pos;
    }

    return false;
}

//---------------------------------------------------------------------------
//!　MOVEの間常に本拠地へ移動
//---------------------------------------------------------------------------
void UnitBase::setMainTarget(VECTOR& main_fc_pos)
{
    _targetPos = main_fc_pos;
}

//---------------------------------------------------------------------------
//! 移動
//!索敵して範囲内に施設があったらその座標を目的地にして移動
//---------------------------------------------------------------------------
void UnitBase::move(VECTOR& fc_pos)
{
    //! unitからプレイヤーの方向ベクトル作成
    VECTOR dir;

    //! unitの座標から防衛施設の座標を引く
    dir = VSub(fc_pos, _pos);

    // 正規化
    dir = VNorm(dir);

    //! 正規化したベクトルに速度をかける
    dir = VScale(dir, par._movSpd);

    //! unitの座標に正規化した方向ベクトルを引く
    //! 正規化したベクトルに速度をかける

    _pos = VAdd(_pos, dir);

    //! 方向転換
    direction(fc_pos);

    //! 一フレーム前の座標
    _oldPos = VGet(_pos.x, _pos.y, _pos.z);
}

//---------------------------------------------------------------------------
//! 方向転換
//---------------------------------------------------------------------------
void UnitBase::direction(VECTOR& fc_pos)
{
    //! unitからプレイヤーの方向ベクトル作成
    VECTOR dir;

    //! unitの座標から防衛施設の座標を引く
    dir = VSub(fc_pos, _pos);

    // 正規化
    dir = VNorm(dir);

    // unitの右方向のベクトルを作成
    // 右向きなので90.0ｆ
    float side_rot = _dir + TO_RADIAN(180.0f);

    _side.x += cosf(side_rot);
    _side.z -= sinf(side_rot);

    //! 正規化
    _side = VNorm(_side);

    //! ２つのベクトルの内積を取得
    //! (unitからプレイヤーの方向ベクトル作成 , unitの右方向のベクトルを作成)
    float side_dot = VDot(_side, dir);

    // 内積の値をみて回転方向を決める
    if(side_dot > 0.0f) {
        _dir += TO_RADIAN(2.0f);
    }
    if(side_dot < 0.0f) {
        _dir -= TO_RADIAN(2.0f);
    }

    //! マトリックスを使ったモデルの回転
    _matRot = MGetRotY(_dir);
    //! MGetRotYでなぜかscaleが1になるので強制変更
    _matRot = MScale(_matRot, _size);

    //! マトリックスの座標に現在位置を入れる
    _matRot.m[3][0] = _pos.x;
    _matRot.m[3][1] = _pos.y;
    _matRot.m[3][2] = _pos.z;
}

//---------------------------------------------------------------------------
//! 当たり判定の動き
//---------------------------------------------------------------------------
void UnitBase::movHit()
{
    //! マトリックスのZ情報
    VECTOR vec     = VGet(_matRot.m[2][0], _matRot.m[2][1], _matRot.m[2][2]);
    VECTOR vec_atk = VGet(_matRot.m[2][0], _matRot.m[2][1], _matRot.m[2][2]);

    //! 正規化
    vec = VNorm(vec);

    //!  間隔をかける
    mulVec(vec, _hit._hcSpace);
    mulVec(vec_atk, _hitAtk._hcSpace);

    //!  Z軸だと反対になるので反転させる
    mulVec(vec, -1.0f);
    mulVec(vec_atk, -1.0f);

    //! unitのポジションとマトリックスのZ情報を足す
    _hit._hcPos    = VAdd(_pos, vec);
    _hitAtk._hcPos = VAdd(_pos, vec_atk);
}

//---------------------------------------------------------------------------
//! 一定速度でファクトリーにダメージを与える
//---------------------------------------------------------------------------
void UnitBase::attack()
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
//! attackが終わったらmoveに戻す
//---------------------------------------------------------------------------
void UnitBase::setMove(s16 hp)
{
    if(hp <= 0) {
        _state = STATE::MOVE;
        _isAtk = false;

        isSearch();
    }
}

//---------------------------------------------------------------------------
//! ダメージ処理
//---------------------------------------------------------------------------
void UnitBase::damage(bool isAtk, f32 atk)
{
    if(isAtk && _isDamage) {
        par._hp -= atk;
        isAtk = false;
    }
}

//---------------------------------------------------------------------------
//! 死亡時のモーション
//---------------------------------------------------------------------------
void UnitBase::checkMotion()
{
    if(par._hp <= 0) {
        _state = STATE::DEATH;
    }
}

void UnitBase::deadMotion()
{
    //! matrixのY軸を小さくする
    if(_matRot.m[1][1] >= 0.00f) {
        _matRot.m[1][1] -= 0.005;
    }
    else {
        _alpha -= 0.02f;
    }

    if(_alpha <= 0.0f) {
        _is_dead = true;
    }

    //! モデルの不透明度を変える
    MV1SetMeshOpacityRate(_model.get()->handle(), 0, _alpha);
}
//---------------------------------------------------------------------------
//! HPの上限以上回復しないように
//---------------------------------------------------------------------------
void UnitBase::setMaxHitPoint()
{
    if(par._hp > _HP) {
        par._hp = _HP;
    }
}
//---------------------------------------------------------------------------
//! サイズ変更
//---------------------------------------------------------------------------
void UnitBase::setSize()
{
    if(_size <= 0.04f) {
        _size += 0.002;
    }
}

//!---------------------------
//! ゲッター
//!---------------------------

//---------------------------------------------------------------------------
//! ユニットの種類
//---------------------------------------------------------------------------
TYPE UnitBase::type()
{
    return _type;
}
