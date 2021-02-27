//---------------------------------------------------------------------------
//!	@file	sceneGame.cpp
//!	@brief	�Q�[���v���C���̃V�[���̊Ǘ�
//---------------------------------------------------------------------------
#pragma once

//===========================================================================
//!	�`��e�X�g�V�[��
//===========================================================================

class SceneGameTitle : public Scene
{
public:
    //! �R���X�g���N�^
    SceneGameTitle();

    //! �f�X�g���N�^
    virtual ~SceneGameTitle();

    //! ������
    virtual bool initialize() override;

    //! �X�V
    virtual void update() override;

    //! �`��
    virtual void render() override;

    //! ���
    virtual void finalize() override;

public:
    //! �Ó]
    void blackOut();
    //! �V�[���؂�ւ�
    void switchScene();

private:
    //! �^�C�g����ʂ̃e�N�X�`��
    int _texture;
    //! �n�ʂ̃��f��
    Model* _under_ground;

    //! �V�[���؂�ւ��t���O
    bool _check;
    int  _alpha;
};
