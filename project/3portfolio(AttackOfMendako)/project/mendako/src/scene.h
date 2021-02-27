//---------------------------------------------------------------------------
//!	@file	scene.h
//!	@brief	シーンの管理
//---------------------------------------------------------------------------

#pragma once

//===========================================================================
//!	シーン基底
//===========================================================================

//! ステージの数
#define STAGE_MAX 5
//! ユニットの種類
#define UNIT_MAX 4


class Scene
{
public:
    Scene()          = default;
    virtual ~Scene() = default;

    //! 初期化
    virtual bool initialize() = 0;
    //! 更新
    virtual void update() = 0;
    //! 描画
    virtual void render() = 0;
    //! 解放
    virtual void finalize() = 0;

public:
    //-------------------------------------------------------------
    //!	@name	シーン管理
    //-------------------------------------------------------------
    //@{
    //! シーンヘジャンプリクエスト
    static void sceneJump(Scene* s);

    //! シーンシステム更新
    static void sceneUpdate();

    static Scene* getScene() { return scene_.get(); }

    //! シーンシステム終了
    //! ここで強制開放しないとバグる
    static void exit()
    {
        scene_.reset();
        sceneNext_.reset();
    }

    //}@

private:
    // static inline はc++/17 以降でしか使えない（言語から設定）
    static inline std::unique_ptr<Scene> scene_     = nullptr;   //! 現在のシーン
    static inline std::unique_ptr<Scene> sceneNext_ = nullptr;   //! 次のシーンリクエスト

protected:
    //! ステージのクリア状況
    static inline s16 _clearStage[STAGE_MAX];
    //! ステージのlock状況
    static inline bool _is_stage_lock[STAGE_MAX];
    //! ステージのlockの各透過度
    static inline int _lock_stage_alpha[STAGE_MAX];

    
    //! ユニットがアンロックされているか
    static inline bool _is_unit_lock[UNIT_MAX];

    //! 鎖の透過度
    static inline int _lock_unit_alpha[UNIT_MAX];


};

//--------------------------------------------------------------
// アクセスインターフェイス
//--------------------------------------------------------------
inline Scene* GmScene()
{
    return Scene::getScene();
}