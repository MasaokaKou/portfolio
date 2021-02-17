//---------------------------------------------------------------------------
//!	@file	sceneGame.cpp
//!	@brief	�Q�[���v���C���̃V�[���̊Ǘ�
//---------------------------------------------------------------------------
#pragma once

//===========================================================================
//!	�`��e�X�g�V�[��
//===========================================================================

class SceneStageClear : public Scene
{
public:
    //! �R���X�g���N�^
    SceneStageClear(s16 stage, int fac_max_, int fac_num_, int time_);

    //! �f�X�g���N�^
    virtual ~SceneStageClear();

    //! ������
    virtual bool initialize() override;

    //! �X�V
    virtual void update() override;

    //! �`��
    virtual void render() override;

    //! ���
    virtual void finalize() override;

public:
    //! �w�i�`��
    void drawBack();

    //! �X�R�A�X�V
    void updateScore();
    //! �X�R�A�`��
    void drawScore(int alpha_txst2_);

    //! �w�i�̍��𓧉�
    void decAlpha();

    //! �]��
    void rank();
    void drawRank();

    //! �Q�[���N���A
    void gameClear();

private:
    s16 _stage;
    int _back_graph;

    //! �V�[���؂�ւ����I��������ǂ���
    bool _alpha_frag;

    //!�@�X�e�[�W���̓G�̍ő吔
    int _fac_max;

    //!�@�X�e�[�W���̓G������������
    int _fac_num;

    //! �ŏI�I�ɂ�����������
    int _time;

    //!�@�w�i�̓��ߓx
    int _alpha;

    //! �����N
    int   _rank;
    float _fac_sum;
    float _time_sum;
    float _sum;
};
