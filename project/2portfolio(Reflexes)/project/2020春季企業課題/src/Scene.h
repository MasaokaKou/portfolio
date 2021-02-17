//#pragma once
//#include <memory>
//
//
//enum class RenderMode
//{
//	Scene, //!< �V�[���`��
//	Shadow,//!< �V���h�E����
//	UI,    //!< UI�`��
//};
//
//
////---------------------------------------------------
////! �V�[�����
////---------------------------------------------------
//class Scene
//{
//public:
//
//	Scene() = default;
//	virtual ~Scene() = default;
//
//	//! ������
//	virtual bool initialize() = 0;
//
//	//! �X�V
//	virtual void update() = 0;
//
//	//! �`��
//	virtual void render(RenderMode mode) = 0;
//
//	//! ���
//	virtual void finalize() = 0;
//
//public:
//	//---------------------------------------------------
//	//! �V�[���Ǘ�
//	//---------------------------------------------------
//
//	//! �V�[���W�����v�̃��N�G�X�g
//	static void sceneJump(Scene* s);
//
//	//! �V�[���V�X�e���X�V
//	static void sceneUpdate();
//
//	//! ���݂̃V�[�����擾
//	static Scene* getScene() { return scene_.get(); }
//
//private:
//
//	// static inline ��c++/17 �ȍ~�ł����g���Ȃ��i���ꂩ��ݒ�j
//	static inline std::unique_ptr<Scene>scene_ = nullptr;     //!< ���݂̃V�[��
//	static inline std::unique_ptr<Scene>sceneNext_ = nullptr; //!< ���̃V�[�����N�G�X�g
//
//};
//
////----------------------------------------------
////  �A�N�Z�X�C���^�[�t�F�C�X
////----------------------------------------------
//inline Scene * GetScene()
//{
//	return Scene::getScene();
//}