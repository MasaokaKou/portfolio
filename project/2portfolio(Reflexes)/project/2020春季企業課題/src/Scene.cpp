//#include"Scene.h"
//
////-----------------------------------
////! シーン基盤
////-----------------------------------
//void Scene::sceneJump(Scene *s)
//{
//	sceneNext_.reset(s);
//}
//
////---------------------------------- 
////! シーンシステム更新 
////---------------------------------- 
//void Scene::sceneUpdate() 
//{
//	// シーン切り替えリクエストがあったら現在のシーンを解放し
//	// 新しく初期化
//	if (sceneNext_) {
//		if (scene_) 
//			scene_->finalize(); // 解放
//		scene_ = std::move(sceneNext_);
//		scene_->initialize();   // 初期化
//
//	}
//
//	if (scene_) {
//		// 更新
//		scene_->update();
//    }
//
//
//}
