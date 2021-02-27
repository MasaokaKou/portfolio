#pragma once
//---------------------------------------------------------------------------
//!	@file	stageSelector.h
//!	@brief	ステージ選択画面管理
//---------------------------------------------------------------------------

//! ステージの選択画面をすべて管理
//! ステージの上限はとりあえず五個
//! ステージをクリアしたらセレクト画面に戻る

class StageSelector : public Scene
{
public:
    StageSelector();
    ~StageSelector();

    //! 初期化
    virtual bool initialize() override;

    //! 更新
    virtual void update() override;

    //! 描画
    virtual void render() override;

    //! 解放
    virtual void finalize() override;

public:
    s16 stage();

    //! 全体の透過度を下げる
    void decAlpha();
    //! ステージ名の透過度をあげて、下げる
    void addAlpha();

    //! チュートリアル機能選択
    bool isTutorial();

    //! チュートリアルオンオフ説明
    void drawTextToTutorial();


    //! 前のステージがクリアされてなければそれ以降選択できない
    void lockStage();

    //! ステージのアンロック
    void unlock();

    //! 鎖が消えるアニメーション
    void unlockAnim();

    //! ステージセレクターからタイトルへ
    void gameReset();

    //! 暗転
    void blackOut();

private:
    //! ステージの上限（どのステージにいるか）
    s16 _stage;

    //! ステージ選択用変数
    s16 _cube_x[STAGE_MAX], _cube_y[STAGE_MAX];

    //! 選択されているかどうかのフラグ
    bool _flag[STAGE_MAX];

    //! 高さと横幅
    s16 high, wide;

    //! マウスの座標
    int _mouse_x, _mouse_y;

    //! 選択後のアニメーションが始まったかどうか
    bool _isAnim;
    bool _isAnimEnd;

    //!　透過度
    s16 _alpha[2];

    //! チュートリアル機能選択
    s16  _tutorial_x, _tutorial_y;
    bool _is_tutorial;
    s16  _tutorial_timer;
    bool _timer;

    //! 鎖の座標
    int _lock_x, _lock_y;
    //! 鎖の画像
    int _lock_graph;

    //! 背景
    int _back_graph;

    int  _reset_timer;
    bool _check;
    int _back_alpha;
    
};
