//---------------------------------------------------------------------------
//!	@file	sceneGame.cpp
//!	@brief	ゲームプレイ中のシーンの管理
//---------------------------------------------------------------------------
#pragma once

//===========================================================================
//!	描画テストシーン
//===========================================================================

class SceneStageClear : public Scene
{
public:
    //! コンストラクタ
    SceneStageClear(s16 stage, int fac_max_, int fac_num_, int time_);

    //! デストラクタ
    virtual ~SceneStageClear();

    //! 初期化
    virtual bool initialize() override;

    //! 更新
    virtual void update() override;

    //! 描画
    virtual void render() override;

    //! 解放
    virtual void finalize() override;

public:
    //! 背景描画
    void drawBack();

    //! スコア更新
    void updateScore();
    //! スコア描画
    void drawScore(int alpha_txst2_);

    //! 背景の黒を透過
    void decAlpha();

    //! 評価
    void rank();
    void drawRank();

    //! ゲームクリア
    void gameClear();

private:
    s16 _stage;
    int _back_graph;

    //! シーン切り替えが終わったかどうか
    bool _alpha_frag;

    //!　ステージ毎の敵の最大数
    int _fac_max;

    //!　ステージ毎の敵をたおした数
    int _fac_num;

    //! 最終的にかかった時間
    int _time;

    //!　背景の透過度
    int _alpha;

    //! ランク
    int   _rank;
    float _fac_sum;
    float _time_sum;
    float _sum;
};
