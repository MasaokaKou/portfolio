//---------------------------------------------------------------------------
//!	@file	sceneGame.cpp
//!	@brief	ゲームプレイ中のシーンの管理
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! コンストラクタ
//---------------------------------------------------------------------------
SceneStageClear::SceneStageClear(s16 stage, int fac_max_, int fac_num_, int time_)
{
    _stage      = stage;
    _alpha_frag = false;

    //　ステージ毎の敵の最大数
    _fac_max = fac_max_;
    //　ステージ毎の敵をたおした数
    _fac_num = fac_num_;

    // 経過時間
    _time = time_;
    // 透過度
    _alpha = 255;

    //! ランク
    _rank     = 0;
    _fac_sum  = 0;
    _time_sum = 0;
    _sum      = 0;
}

//---------------------------------------------------------------------------
//! デストラクタ
//---------------------------------------------------------------------------
SceneStageClear::~SceneStageClear()
{
}
//---------------------------------------------------------------------------
//! 初期化
//!	@retval	true	正常終了	(成功)
//!	@retval	false	エラー終了	(失敗)
//---------------------------------------------------------------------------
bool SceneStageClear::initialize()
{
    _back_graph = LoadGraph("data/stage_select_back.png");
    return true;
}

//---------------------------------------------------------------------------
//! 更新
//---------------------------------------------------------------------------
void SceneStageClear::update()
{
    //! スペースでシーン移動
    if(CheckHitKey(KEY_INPUT_SPACE)) {
        Scene::sceneJump(new StageSelector());
        gameClear();
    }

    //! 背景の黒を透過
    decAlpha();
    rank();

    //! ステージをクリアしたかどうかのフラグを立てる
    if(_rank != 5)
        _clearStage[_stage] = 1;
}

//---------------------------------------------------------------------------
//! 描画
//---------------------------------------------------------------------------
void SceneStageClear::render()
{
    // 透過度
    static int alpha_txst1 = 0;
    static int alpha_txst2 = 0;
    static int alpha_txst3 = 0;

    //! 背景描画
    DrawRotaGraph(0, 0, 2.0f, 0, _back_graph, true);

    //! 文字描画
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_txst1);
    SetFontSize(50);
    DrawString(120, 100, "RESULT", WHITE, WHITE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    //! スコア描画
    drawScore(alpha_txst2);

    //! 順々に透過度変更
    if(_alpha_frag)
        alpha_txst1 += 5;

    if(alpha_txst1 >= 255) {
        alpha_txst2 += 5;
    }
    if(alpha_txst2 >= 255) {
        alpha_txst3 += 5;
    }

    if(alpha_txst3 >= 255)
        blinkText(400, 350, "PUSH SPACE");

    drawBack();

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_txst3);
    drawRank();
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    

}

//---------------------------------------------------------------------------
//! 解放
//---------------------------------------------------------------------------
void SceneStageClear::finalize()
{
}

//---------------------------------------------------------------------------
//! 背景描画
//---------------------------------------------------------------------------
void SceneStageClear::drawBack()
{
    //! 背景の黒を描画
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
    DrawBox(0, 0, WINDOW_W, WINDOW_H, BLACK, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//---------------------------------------------------------------------------
//! スコア更新
//---------------------------------------------------------------------------
void SceneStageClear::updateScore()
{
}

//---------------------------------------------------------------------------
//! スコア描画
//---------------------------------------------------------------------------
void SceneStageClear::drawScore(int alpha_txst2_)
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_txst2_);
    SetFontSize(30);
    DrawString(120, 200, "TIME", WHITE, WHITE);
    chengeText(_time, 200, 200, 255, 255, 255);

    DrawString(120, 250, "SCORE", WHITE, WHITE);
    chengeText(_fac_num, 240, 250, 255, 255, 255);
    DrawString(270, 250, "/", WHITE, WHITE);
    chengeText(_fac_max, 300, 250, 255, 255, 255);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//---------------------------------------------------------------------------
//! 背景の黒を透過
//---------------------------------------------------------------------------
void SceneStageClear::decAlpha()
{
    //! 背景の黒を透過
    _alpha -= 5;
    if(_alpha <= 0) {
        _alpha_frag = true;
    }
}

//---------------------------------------------------------------------------
//! 評価
//---------------------------------------------------------------------------
void SceneStageClear::rank()
{
    _fac_sum  = _fac_max - _fac_num;
    _time_sum = _time * 0.1f;
    _sum      = _time_sum + _fac_sum;

    if(_sum <= 3) {
        _rank = 1;
    }
    else if(_sum <= 4) {
        _rank = 2;
    }
    else if(_sum <= 7) {
        _rank = 3;
    }
    else if(_sum <= 10) {
        _rank = 4;
    }
    else {
        _rank = 5;
    }
}

void SceneStageClear::drawRank()
{
    SetFontSize(120);

    if(_rank == 1) {
        DrawString(420, 100, "S", WHITE, WHITE);
    }
    else if(_rank == 2) {
        DrawString(420, 100, "A", RED, WHITE);
    }
    else if(_rank == 3) {
        DrawString(420, 100, "B", GetColor(0, 0, 255), WHITE);
    }
    else if(_rank == 4) {
        DrawString(420, 100, "C", GetColor(0, 255, 0), WHITE);
    }
    else if(_rank == 5) {
        DrawString(420, 100, "D", BLACK, WHITE);
    }
}

//---------------------------------------------------------------------------
//! ゲームクリア
//---------------------------------------------------------------------------
void SceneStageClear::gameClear()
{
    if(_clearStage[4] == 1) {
        Scene::sceneJump(new SceneGameClear());
    }
}
