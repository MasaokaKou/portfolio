//#pragma once
//#include <memory>
//
//
//enum class RenderMode
//{
//	Scene, //!< シーン描画
//	Shadow,//!< シャドウ生成
//	UI,    //!< UI描画
//};
//
//
////---------------------------------------------------
////! シーン基底
////---------------------------------------------------
//class Scene
//{
//public:
//
//	Scene() = default;
//	virtual ~Scene() = default;
//
//	//! 初期化
//	virtual bool initialize() = 0;
//
//	//! 更新
//	virtual void update() = 0;
//
//	//! 描画
//	virtual void render(RenderMode mode) = 0;
//
//	//! 解放
//	virtual void finalize() = 0;
//
//public:
//	//---------------------------------------------------
//	//! シーン管理
//	//---------------------------------------------------
//
//	//! シーンジャンプのリクエスト
//	static void sceneJump(Scene* s);
//
//	//! シーンシステム更新
//	static void sceneUpdate();
//
//	//! 現在のシーンを取得
//	static Scene* getScene() { return scene_.get(); }
//
//private:
//
//	// static inline はc++/17 以降でしか使えない（言語から設定）
//	static inline std::unique_ptr<Scene>scene_ = nullptr;     //!< 現在のシーン
//	static inline std::unique_ptr<Scene>sceneNext_ = nullptr; //!< 次のシーンリクエスト
//
//};
//
////----------------------------------------------
////  アクセスインターフェイス
////----------------------------------------------
//inline Scene * GetScene()
//{
//	return Scene::getScene();
//}