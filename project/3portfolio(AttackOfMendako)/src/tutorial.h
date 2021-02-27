//!	@file	tutorial.cpp
//!	@brief	�`���[�g���A���̊Ǘ�
//---------------------------------------------------------------------------
#pragma once

//===========================================================================
//!	�`���[�g���A���̊Ǘ�
//===========================================================================

enum FLOW
{

    NONE,
    GAME_STYLE,
    UNIT1,      //�������j�b�g�̏����\�͈͐���
    UNIT_NUM,   //�����\���̐���
    UNIT2,      //�������j�b�g�̏o����
    Unit,      //�G�̊m�F�@
    BOSS,       //�Q�[���N���A�����̊m�F

    STAY,    //�`���[�g���A���t���[�ꎞ��~
    UNIT3,   //���j�b�g�̒ǉ��Ɛ���
    END

};

class Tutorial
{
public:
    Tutorial();
    ~Tutorial();

    void initialize();   //! ������
    void update();       //! �X�V
    void render();       //! �`��
    void finalize();     //! ���

public:
    //! ���f���Ɛ����o���̓o��A�j���[�V����
    void startAnimation();

    //! �����o�����o��
    void setSpeech();

    //! �`���[�g���A���̗���
    void flow();

    //! �ȒP�ȃQ�[���̏Љ�
    void firstGameStyle();

    //1 �������j�b�g�̏����\�͈͐���
    void howRangeSetUnit();

    //1 �������j�b�g�̏o����
    void howToSetUnit();

    //1 �G�̊m�F�@
    void checkUnit();

    //1 �Q�[���N���A�����̊m�F
    void checkBossUnit();

    //���j�b�g�̒ǉ��Ɛ���
    void typeToUnit();

    //! �X�e�[�W�ԍ��������Ă���
    void setStageNum(int stageNum_);

    FLOW getFlow();
    void setFlow(FLOW a_);

    //! �e�L�X�g���o�Ă��邩�ǂ����̃t���O
    bool isVisible() { return _is_visible; }
    void setIsVisible(bool a) { _is_visible = a; }

    bool IsTypeToUnit();

private:
    //! �`���[�g���A���p���f��
    Model* _mendako;

    int _graphHandle;

    //! ���f���̐����o��
    s16 _speech_graph_x, _speech_graph_y;
    s16 _speech_under_graph_y;

    //! �������ʂ̖��܂��͉~
    int _arrow_graph_x, _arrow_graph_y;

    //! �`���[�g���A�����ɐ����o���A���f���̗L��
    bool _is_visible;

    //! ����
    FLOW _flow;

    //! �Ԋu
    bool _span;

    //! �X�e�[�W�ԍ�
    int _stageNum;

    //! ���j�b�g�̐����t���O
    bool _type_to_unit;

    //! �~�̉摜
    int _g_handle;
};
