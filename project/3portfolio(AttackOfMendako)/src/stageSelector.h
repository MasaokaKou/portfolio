#pragma once
//---------------------------------------------------------------------------
//!	@file	stageSelector.h
//!	@brief	�X�e�[�W�I����ʊǗ�
//---------------------------------------------------------------------------

//! �X�e�[�W�̑I����ʂ����ׂĊǗ�
//! �X�e�[�W�̏���͂Ƃ肠�����܌�
//! �X�e�[�W���N���A������Z���N�g��ʂɖ߂�

class StageSelector : public Scene
{
public:
    StageSelector();
    ~StageSelector();

    //! ������
    virtual bool initialize() override;

    //! �X�V
    virtual void update() override;

    //! �`��
    virtual void render() override;

    //! ���
    virtual void finalize() override;

public:
    s16 stage();

    //! �S�̂̓��ߓx��������
    void decAlpha();
    //! �X�e�[�W���̓��ߓx�������āA������
    void addAlpha();

    //! �`���[�g���A���@�\�I��
    bool isTutorial();

    //! �`���[�g���A���I���I�t����
    void drawTextToTutorial();


    //! �O�̃X�e�[�W���N���A����ĂȂ���΂���ȍ~�I���ł��Ȃ�
    void lockStage();

    //! �X�e�[�W�̃A�����b�N
    void unlock();

    //! ����������A�j���[�V����
    void unlockAnim();

    //! �X�e�[�W�Z���N�^�[����^�C�g����
    void gameReset();

    //! �Ó]
    void blackOut();

private:
    //! �X�e�[�W�̏���i�ǂ̃X�e�[�W�ɂ��邩�j
    s16 _stage;

    //! �X�e�[�W�I��p�ϐ�
    s16 _cube_x[STAGE_MAX], _cube_y[STAGE_MAX];

    //! �I������Ă��邩�ǂ����̃t���O
    bool _flag[STAGE_MAX];

    //! �����Ɖ���
    s16 high, wide;

    //! �}�E�X�̍��W
    int _mouse_x, _mouse_y;

    //! �I����̃A�j���[�V�������n�܂������ǂ���
    bool _isAnim;
    bool _isAnimEnd;

    //!�@���ߓx
    s16 _alpha[2];

    //! �`���[�g���A���@�\�I��
    s16  _tutorial_x, _tutorial_y;
    bool _is_tutorial;
    s16  _tutorial_timer;
    bool _timer;

    //! ���̍��W
    int _lock_x, _lock_y;
    //! ���̉摜
    int _lock_graph;

    //! �w�i
    int _back_graph;

    int  _reset_timer;
    bool _check;
    int _back_alpha;
    
};
