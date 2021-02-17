//---------------------------------------------------------------------------
//!	@file	sceneGame.cpp
//!	@brief	ゲームプレイ中のシーンの管理
//---------------------------------------------------------------------------
#pragma once

//===========================================================================
//!	描画テストシーン
//===========================================================================

class SceneGameTitle : public Scene
{
public:
    //! コンストラクタ
    SceneGameTitle();

    //! デストラクタ
    virtual ~SceneGameTitle();

    //! 初期化
    virtual bool initialize() override;

    //! 更新
    virtual void update() override;

    //! 描画
    virtual void render() override;

    //! 解放
    virtual void finalize() override;

public:
    //! 暗転
    void blackOut();
    //! シーン切り替え
    void switchScene();

private:
    //! タイトル画面のテクスチャ
    int _texture;
    //! 地面のモデル
    Model* _under_ground;

    //! シーン切り替えフラグ
    bool _check;
    int  _alpha;
};
