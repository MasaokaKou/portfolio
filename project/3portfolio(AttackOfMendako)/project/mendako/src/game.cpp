//---------------------------------------------------------------------------
//!	@file	game.cpp
//!	@brief	ソースコード全体の管理
//---------------------------------------------------------------------------

static int _gametimer;   //! debug

//===========================================================================
//! ゲームメイン
//===========================================================================

//-----------------------------
//! コンストラクタ
//-----------------------------
Game::Game()
{
    // カメラの現在位置
    _cameraPos = VGet(0, 70, -70);

    // カメラの注視点
    _cameraTarget = VGet(0, 0, 0);
}

//-----------------------------
//デストラクタ
//-----------------------------
Game::~Game()
{
}

//-----------------------------
//! 初期化
//-----------------------------
void Game::initialize()
{
    // カメラの現在位置とどこを向いているか
    SetCameraPositionAndTarget_UpVecY(_cameraPos, _cameraTarget);
}
//---------------------------------------------------------------------------
//! 更新
//---------------------------------------------------------------------------
void Game::update()
{
    // シーンちゃんとする
    Scene::sceneUpdate();

    if(_gametimer == 1) {
        //Scene::sceneJump(new StageSelector());
        Scene::sceneJump(new SceneGamePlay(2, false));

        Scene::sceneJump(new SceneGameTitle());
        //Scene::sceneJump(new SceneGameClear());
    }
    _gametimer++;

#ifdef _DEBUG
    // カメラの移動

    if(CheckHitKey(KEY_INPUT_W)) {
        _cameraPos = VGet(0, 50, 50);
    }
    if(CheckHitKey(KEY_INPUT_A)) {
        _cameraPos = VGet(-50, 50, 0);
    }
    if(CheckHitKey(KEY_INPUT_S)) {
        _cameraPos = VGet(0, 50, -50);
    }
    if(CheckHitKey(KEY_INPUT_D)) {
        _cameraPos = VGet(50, 50, 0);
    }

    if(CheckHitKey(KEY_INPUT_UP)) {
        _cameraPos.y--;
    }
    if(CheckHitKey(KEY_INPUT_DOWN)) {
        _cameraPos.y++;
    }
    if(CheckHitKey(KEY_INPUT_RIGHT)) {
        _cameraPos.x++;
    }
    if(CheckHitKey(KEY_INPUT_LEFT)) {
        _cameraPos.x--;
    }

    // カメラの現在位置とどこを向いているか
    SetCameraPositionAndTarget_UpVecY(_cameraPos, _cameraTarget);

#endif   // _DEBUG
    VECTOR v = VScale(_cameraPos, -1);

    ChangeLightTypeDir(v);
    // カラーを素の色に近づける
    SetGlobalAmbientLight({ 0.4, 0.4, 0.4, 1.0 });
}
//---------------------------------------------------------------------------
//! 描画
//---------------------------------------------------------------------------
void Game::render()
{
}

//---------------------------------------------------------------------------
//! 解放
//---------------------------------------------------------------------------
void Game::finalize()
{
    // シーンシステム終了
    // ここで強制開放しないとバグる
    Scene::exit();
}