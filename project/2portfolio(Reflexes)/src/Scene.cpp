//#include"Scene.h"
//
////-----------------------------------
////! �V�[�����
////-----------------------------------
//void Scene::sceneJump(Scene *s)
//{
//	sceneNext_.reset(s);
//}
//
////---------------------------------- 
////! �V�[���V�X�e���X�V 
////---------------------------------- 
//void Scene::sceneUpdate() 
//{
//	// �V�[���؂�ւ����N�G�X�g���������猻�݂̃V�[���������
//	// �V����������
//	if (sceneNext_) {
//		if (scene_) 
//			scene_->finalize(); // ���
//		scene_ = std::move(sceneNext_);
//		scene_->initialize();   // ������
//
//	}
//
//	if (scene_) {
//		// �X�V
//		scene_->update();
//    }
//
//
//}
