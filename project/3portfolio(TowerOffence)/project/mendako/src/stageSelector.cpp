//---------------------------------------------------------------------------
//!	@file	stageSelector.cpp
//!	@brief	タスク管理
//---------------------------------------------------------------------------
//#include "stageSelector.h"

//---------------------------------------------------------------------------
//! コンストラクタ
//---------------------------------------------------------------------------
StageSelector::StageSelector()
{
    for(s16 i = 0; i < STAGE_MAX; i++) {
        _cube_x[i] = 0 + (i * 135);
        _cube_y[i] = 200;

        _flag[i] = false;

        // _is_clear[i] = false;
    }
    _stage = 0;
    //! 高さと横幅
    high = wide = 100;

    //! 選択後のアニメーションが始まったかどうか
    _isAnim    = false;
    _isAnimEnd = false;

    //!　透過度
    _alpha[0] = 255;
    _alpha[1] = 0;

    //! チュートリアル機能選択
    _tutorial_x     = 270;
    _tutorial_y     = 350;
    _is_tutorial    = true;
    _tutorial_timer = 30;
    _timer          = false;

    //! マウスの座標
    GetMousePoint(&_mouse_x, &_mouse_y);

    //! 鎖の画像
    _lock_graph = 0;
    _lock_x     = 50;
    _lock_y     = 250;

    for(int i = 0; i < STAGE_MAX; i++) {
        if(!_is_stage_lock[i])
            _lock_stage_alpha[i] = 255;
    }
    _is_stage_lock[0] = true;

    _back_alpha  = 255;
    _check       = false;
    _reset_timer = 0;
}

//---------------------------------------------------------------------------
//! デストラクタ
//---------------------------------------------------------------------------

StageSelector::~StageSelector()
{
}

//---------------------------------------------------------------------------
//! 初期化
//---------------------------------------------------------------------------
bool StageSelector::initialize()
{
    _lock_graph = LoadGraph("data/lock.png");
    _back_graph = LoadGraph("data/stage_select_back.png");

    return false;
}

//---------------------------------------------------------------------------
//! 更新
//---------------------------------------------------------------------------
void StageSelector::update()
{
    _reset_timer++;

    blackOut();

    //! ステージアンロック
    unlock();
    unlockAnim();

    //! マウスの座標
    GetMousePoint(&_mouse_x, &_mouse_y);
    for(s16 i = 0; i < STAGE_MAX; i++) {
        if(_cube_x[i] < _mouse_x && _cube_x[i] + wide > _mouse_x && _cube_y[i] < _mouse_y && _cube_y[i] + high > _mouse_y) {
            _flag[i] = true;
            if(GetMouseInput() && _is_stage_lock[i]) {
                if(_isAnim)
                    return;
                _stage  = i;
                _isAnim = true;
            }
        }
        else {
            _flag[i] = false;
        }
    }

    //! チュートリアル
    if(_tutorial_x < _mouse_x && _tutorial_x + wide > _mouse_x && _tutorial_y < _mouse_y && _tutorial_y + high > _mouse_y) {
        if(GetMouseInput()) {
            if(_timer)
                return;
            if(!_is_tutorial) {
                _is_tutorial = true;
                _timer       = true;
            }
            else {
                _is_tutorial = false;
                _timer       = true;
            }
        }
    }

    if(_timer) {
        _tutorial_timer--;
        if(_tutorial_timer <= 0) {
            _tutorial_timer = 30;
            _timer          = false;
        }
    }

    decAlpha();
    addAlpha();

    gameReset();

    if(CheckHitKey(KEY_INPUT_1))
        _clearStage[0] = 1;

    if(CheckHitKey(KEY_INPUT_2))
        _clearStage[1] = 1;
    if(CheckHitKey(KEY_INPUT_3))
        _clearStage[2] = 1;
    if(CheckHitKey(KEY_INPUT_4))
        _clearStage[3] = 1;
}

//---------------------------------------------------------------------------
//! 描画
//---------------------------------------------------------------------------
void StageSelector::render()
{
    DrawRotaGraph(0, 0, 2.0f, 0, _back_graph, true);

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha[0]);
    for(s16 i = 0; i < STAGE_MAX; i++) {
        if(!_flag[i]) {
            DrawBox(_cube_x[i], _cube_y[i], _cube_x[i] + high, _cube_y[i] + wide, WHITE, false);
        }
        else {
            DrawBox(_cube_x[i], _cube_y[i], _cube_x[i] + high, _cube_y[i] + wide, RED, false);
        }
        SetFontSize(80);
        char text[256];
        sprintf_s(text, "%d", i + 1);
        DrawString(_cube_x[i] + 30, _cube_y[i] + 15, text, WHITE, WHITE);

        SetFontSize(40);
        if(_clearStage[i] == 1) {
            // デフォルトフォントハンドルを使用して文字列を回転描画する
            DrawRotaString(_cube_x[i] + 15, _cube_y[i] + 5, 1.0f, 1.0f, 0, 0, 0.5f, RED, WHITE, 0, "CLEAR");
        }
    }

    if(_is_tutorial) {
        DrawBox(_tutorial_x, _tutorial_y, _tutorial_x + high, _tutorial_y + wide * 0.5f, RED, false);
    }
    else {
        DrawBox(_tutorial_x, _tutorial_y, _tutorial_x + high, _tutorial_y + wide * 0.5f, WHITE, false);
    }

    SetFontSize(12);
    if(_tutorial_x < _mouse_x && _tutorial_x + wide > _mouse_x && _tutorial_y < _mouse_y && _tutorial_y + high > _mouse_y) {
        drawTextToTutorial();
    }
    DrawString(_tutorial_x + 5, _tutorial_y + 19, "ちゅーとりある", WHITE, true);

    SetFontSize(80);
    DrawString(70, 100, "STAGE SELECT", WHITE, WHITE);

    //! 鎖の描画
    lockStage();

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha[1]);
    SetFontSize(100);
    char text[256];
    sprintf_s(text, "%d", _stage + 1);
    DrawString(100, 100, "STAGE", WHITE, WHITE);
    DrawString(400, 100, text, WHITE, WHITE);
    SetFontSize(20);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    //! マウスの場所を描画
    DrawCircle(_mouse_x, _mouse_y, 5, WHITE, true);

    DrawString(300, 450, "BACK TITLE[RESET]  ", WHITE);
    blinkText(500, 450, "PUSH SPACE");

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _back_alpha);
    DrawBox(0, 0, WINDOW_W, WINDOW_H, BLACK, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//---------------------------------------------------------------------------
//! 解放
//---------------------------------------------------------------------------
void StageSelector::finalize()
{
}

//---------------------------------------------------------------------------
//! 全体の透過度を下げる
//---------------------------------------------------------------------------
void StageSelector::decAlpha()
{
    if(_isAnim) {
        if(!_alpha <= 0)
            _alpha[0] -= 3;
    }
}

void StageSelector::addAlpha()
{
    if(_alpha[0] <= 0) {
        _alpha[1] += 3;
    }
    if(_alpha[1] >= 255) {
        _isAnimEnd = true;
    }
    if(_isAnimEnd) {
        _alpha[1] -= 7;
    }
    if(_alpha[1] <= 0 && _isAnimEnd) {
        Scene::sceneJump(new SceneGamePlay(_stage, _is_tutorial));
    }
}

s16 StageSelector::stage()
{
    return _stage;
}

//---------------------------------------------------------------------------
//! チュートリアル機能選択
//---------------------------------------------------------------------------
bool StageSelector::isTutorial()
{
    return _is_tutorial;
}

//---------------------------------------------------------------------------
//! ステージロック
//---------------------------------------------------------------------------
void StageSelector::lockStage()
{
    for(int i = 0; i < STAGE_MAX; i++) {
        //  if(_is_lock[i])
        //      break;

        //! アニメーションが始まっているかどうかでつかうalpha値を変更

        if(_is_stage_lock[i]) {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, _lock_stage_alpha[i]);
        }
        else if(_isAnim) {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha[0]);
        }

        DrawRotaGraph(_lock_x + (135 * i), _lock_y, 0.2f, 0, _lock_graph, true);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}

//---------------------------------------------------------------------------
//! ステージアンロック
//---------------------------------------------------------------------------
void StageSelector::unlock()
{
    for(int i = 0; i < STAGE_MAX; i++) {
        if(_clearStage[i] == 1) {
            _is_stage_lock[i + 1] = true;
        }
    }
}

//---------------------------------------------------------------------------
//! 鎖が消えるアニメーション
//---------------------------------------------------------------------------
void StageSelector::unlockAnim()
{
    for(int i = 0; i < STAGE_MAX; i++) {
        if(_is_stage_lock[i]) {
            _lock_stage_alpha[i] -= 5;
        }
    }
}

//---------------------------------------------------------------------------
//! チュートリアルオンオフ説明
//---------------------------------------------------------------------------
void StageSelector::drawTextToTutorial()
{
    DrawString(_tutorial_x, _tutorial_y + 50, " クリックでON,OFFを切り替えれます", WHITE, true);
    if(_is_tutorial) {
        DrawString(_tutorial_x + 100, _tutorial_y + 20, " ON", WHITE, true);
    }
    else {
        DrawString(_tutorial_x + 100, _tutorial_y + 20, " OFF", WHITE, true);
    }
}

//---------------------------------------------------------------------------
//! 暗転
//---------------------------------------------------------------------------
void StageSelector::blackOut()
{
    if(_back_alpha <= 0) {
        _back_alpha = 0;
    }

    if(_check)
        return;

    _back_alpha -= 5;
}

//---------------------------------------------------------------------------
//! ステージセレクターからタイトルへ
//---------------------------------------------------------------------------
void StageSelector::gameReset()
{
    if(_reset_timer < 120) {
        return;
    }

    if(CheckHitKey(KEY_INPUT_SPACE)) {
        _check = true;
    }

    if(!_check)
        return;

    if(_check) {
        _back_alpha += 3;
    }

    if(_back_alpha >= 255) {
        Scene::sceneJump(new SceneGameTitle());
    }
}
