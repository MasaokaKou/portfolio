//---------------------------------------------------------------------------
//!	@file	sceneGame.cpp
//!	@brief	ゲームプレイ中のシーンの管理
//---------------------------------------------------------------------------
#pragma once

//===========================================================================
//!	描画テストシーン
//===========================================================================
//#include "Model.h"
class SceneGamePlay : public Scene
{
public:
    //! コンストラクタ(ステージ番号　、チュートリアルの有無)
    SceneGamePlay(s16 stage_, bool is_tutorial_);

    //! デストラクタ
    virtual ~SceneGamePlay();

    //! 初期化
    virtual bool initialize() override;

    //! 更新
    virtual void update() override;

    //! 描画
    virtual void render() override;

    //! 解放
    virtual void finalize() override;

public:
    //! チュートリアルの更新
    void tutorialUpdate();

    //! チュートリアルのテキストが出ていたらゲームを止める
    bool isText();

    //1 背景の設定
    void setBackModel();

    //! ゲームを始めた最初一回だけとおす
    void tutorialOnce();

    //! タイマー
    void timerUpdate();

private:
    //! 現在のステージ
    s16 _stage;

    //! 地面のモデル
    Model* _under_ground;

    //! チュートリアルの有無
    bool _is_tutorial;

    //! tutorialの実態
    Tutorial* _tutorial;

    //! 経過時間
    int _counter;
    int _timer;
};
