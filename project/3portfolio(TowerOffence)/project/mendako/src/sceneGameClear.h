//---------------------------------------------------------------------------
//!	@file	sceneGame.cpp
//!	@brief	ゲームプレイ中のシーンの管理
//---------------------------------------------------------------------------
#pragma once

//===========================================================================
//!	描画テストシーン
//===========================================================================

class SceneGameClear : public Scene
{
public:
    //! コンストラクタ
    SceneGameClear();

    //! デストラクタ
    virtual ~SceneGameClear();

    //! 初期化
    virtual bool initialize() override;

    //! 更新
    virtual void update() override;

    //! 描画
    virtual void render() override;

    //! 解放
    virtual void finalize() override;

public:

    //! エンドロール描画
    void drawEndRoll();
    //! エンドロール更新
    void scrollEndRoll();

private:
    int _text_x, _text_y;

    int _back_graph;
    //! 背景の透過度
    int _alpha[2];
    int _flag;


};
