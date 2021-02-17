//---------------------------------------------------------------------------
//!	@file	sceneGame.cpp
//!	@brief	ゲームプレイ中のシーンの管理
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! コンストラクタ
//---------------------------------------------------------------------------
SceneGameTitle::SceneGameTitle()
{
    _texture      = 0;
    _under_ground = new Model;
    _check        = false;
    _alpha        = 255;

    for(int i = 0; i < STAGE_MAX; i++) {
        _lock_stage_alpha[i] = 255;
        _clearStage[i]       = 0;
        _is_stage_lock[i]    = FALSE;
    }
}

//---------------------------------------------------------------------------
//! デストラクタ
//---------------------------------------------------------------------------
SceneGameTitle::~SceneGameTitle()
{
}

//---------------------------------------------------------------------------
//! 初期化
//!	@retval	true	正常終了	(成功)
//!	@retval	false	エラー終了	(失敗)
//---------------------------------------------------------------------------
bool SceneGameTitle::initialize()
{
    _texture = MV1LoadTexture("data/title.png");

    if(_under_ground)
        _under_ground->load("data/sea.mqo");
    return true;
}

//---------------------------------------------------------------------------
//! 更新
//---------------------------------------------------------------------------
void SceneGameTitle::update()
{
    if(_under_ground) {
        _under_ground->setPos(VGet(0, -0.1, 0));
        _under_ground->setScale(VGet(2, 0.0001, 2));
    }

    //! 暗転
    blackOut();
    //! シーン切り替え
    switchScene();
}

//---------------------------------------------------------------------------
//! 描画
//---------------------------------------------------------------------------
void SceneGameTitle::render()
{
    if(_under_ground)
        _under_ground->draw();

    DrawRotaGraph(310, 150, 0.5f, 0, _texture, true);

    int x = WINDOW_W * 0.5f - 55;
    int y = WINDOW_H * 0.5f + 150;

    blinkText(x, y, "PUSH SPACE");

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
    DrawBox(0, 0, WINDOW_W, WINDOW_H, BLACK, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//---------------------------------------------------------------------------
//! 解放
//---------------------------------------------------------------------------
void SceneGameTitle::finalize()
{
}

//---------------------------------------------------------------------------
//! 暗転
//---------------------------------------------------------------------------
void SceneGameTitle::blackOut()
{
    if(CheckHitKey(KEY_INPUT_SPACE)) {
        _check = true;
    }

    if(_check) {
        _alpha += 3;
    }

    if(_check)
        return;

    _alpha -= 5;
    if(_alpha <= 0) {
        _alpha = 0;
    }
}
//---------------------------------------------------------------------------
//! シーン切り替え
//---------------------------------------------------------------------------
void SceneGameTitle::switchScene()
{
    if(!_check)
        return;

    if(_alpha < 255)
        return;

    Scene::sceneJump(new StageSelector());
}
