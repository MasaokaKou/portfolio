//---------------------------------------------------------------------------
//!	@file	sceneGame.cpp
//!	@brief	�Q�[���v���C���̃V�[���̊Ǘ�
//---------------------------------------------------------------------------
#pragma once

//===========================================================================
//!	�`��e�X�g�V�[��
//===========================================================================

class SceneGameClear : public Scene
{
public:
    //! �R���X�g���N�^
    SceneGameClear();

    //! �f�X�g���N�^
    virtual ~SceneGameClear();

    //! ������
    virtual bool initialize() override;

    //! �X�V
    virtual void update() override;

    //! �`��
    virtual void render() override;

    //! ���
    virtual void finalize() override;

public:

    //! �G���h���[���`��
    void drawEndRoll();
    //! �G���h���[���X�V
    void scrollEndRoll();

private:
    int _text_x, _text_y;

    int _back_graph;
    //! �w�i�̓��ߓx
    int _alpha[2];
    int _flag;


};
