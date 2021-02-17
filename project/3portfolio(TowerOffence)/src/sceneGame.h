//---------------------------------------------------------------------------
//!	@file	sceneGame.cpp
//!	@brief	�Q�[���v���C���̃V�[���̊Ǘ�
//---------------------------------------------------------------------------
#pragma once

//===========================================================================
//!	�`��e�X�g�V�[��
//===========================================================================
//#include "Model.h"
class SceneGamePlay : public Scene
{
public:
    //! �R���X�g���N�^(�X�e�[�W�ԍ��@�A�`���[�g���A���̗L��)
    SceneGamePlay(s16 stage_, bool is_tutorial_);

    //! �f�X�g���N�^
    virtual ~SceneGamePlay();

    //! ������
    virtual bool initialize() override;

    //! �X�V
    virtual void update() override;

    //! �`��
    virtual void render() override;

    //! ���
    virtual void finalize() override;

public:
    //! �`���[�g���A���̍X�V
    void tutorialUpdate();

    //! �`���[�g���A���̃e�L�X�g���o�Ă�����Q�[�����~�߂�
    bool isText();

    //1 �w�i�̐ݒ�
    void setBackModel();

    //! �Q�[�����n�߂��ŏ���񂾂��Ƃ���
    void tutorialOnce();

    //! �^�C�}�[
    void timerUpdate();

private:
    //! ���݂̃X�e�[�W
    s16 _stage;

    //! �n�ʂ̃��f��
    Model* _under_ground;

    //! �`���[�g���A���̗L��
    bool _is_tutorial;

    //! tutorial�̎���
    Tutorial* _tutorial;

    //! �o�ߎ���
    int _counter;
    int _timer;
};
