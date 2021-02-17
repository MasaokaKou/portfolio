//---------------------------------------------------------------------------
//!	@file	scene.h
//!	@brief	�V�[���̊Ǘ�
//---------------------------------------------------------------------------

#pragma once

//===========================================================================
//!	�V�[�����
//===========================================================================

//! �X�e�[�W�̐�
#define STAGE_MAX 5
//! ���j�b�g�̎��
#define UNIT_MAX 4


class Scene
{
public:
    Scene()          = default;
    virtual ~Scene() = default;

    //! ������
    virtual bool initialize() = 0;
    //! �X�V
    virtual void update() = 0;
    //! �`��
    virtual void render() = 0;
    //! ���
    virtual void finalize() = 0;

public:
    //-------------------------------------------------------------
    //!	@name	�V�[���Ǘ�
    //-------------------------------------------------------------
    //@{
    //! �V�[���w�W�����v���N�G�X�g
    static void sceneJump(Scene* s);

    //! �V�[���V�X�e���X�V
    static void sceneUpdate();

    static Scene* getScene() { return scene_.get(); }

    //! �V�[���V�X�e���I��
    //! �����ŋ����J�����Ȃ��ƃo�O��
    static void exit()
    {
        scene_.reset();
        sceneNext_.reset();
    }

    //}@

private:
    // static inline ��c++/17 �ȍ~�ł����g���Ȃ��i���ꂩ��ݒ�j
    static inline std::unique_ptr<Scene> scene_     = nullptr;   //! ���݂̃V�[��
    static inline std::unique_ptr<Scene> sceneNext_ = nullptr;   //! ���̃V�[�����N�G�X�g

protected:
    //! �X�e�[�W�̃N���A��
    static inline s16 _clearStage[STAGE_MAX];
    //! �X�e�[�W��lock��
    static inline bool _is_stage_lock[STAGE_MAX];
    //! �X�e�[�W��lock�̊e���ߓx
    static inline int _lock_stage_alpha[STAGE_MAX];

    
    //! ���j�b�g���A�����b�N����Ă��邩
    static inline bool _is_unit_lock[UNIT_MAX];

    //! ���̓��ߓx
    static inline int _lock_unit_alpha[UNIT_MAX];


};

//--------------------------------------------------------------
// �A�N�Z�X�C���^�[�t�F�C�X
//--------------------------------------------------------------
inline Scene* GmScene()
{
    return Scene::getScene();
}