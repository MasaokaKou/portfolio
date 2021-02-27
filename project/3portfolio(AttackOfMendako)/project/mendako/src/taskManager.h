#pragma once
//---------------------------------------------------------------------------
//!	@file	taskMaanager.h
//!	@brief	�^�X�N�Ǘ�
//---------------------------------------------------------------------------
#include "unitManager.h"
#include "factoryManager.h"
//===========================================================================
//!	�^�X�N�}�l�[�W���[
//===========================================================================

class TaskManager
{
public:
    TaskManager(s16 stage_);
    ~TaskManager();

    //! ������
    bool initialize();

    //! �X�V
    void update();

    //! �`��
    void render();

    //! ���
    void finalize();

public:
    //! ���j�b�g�̍��G
    void unitSearch();
    void unitSearchTypeD(UnitManager* emng_);

    //! �t�@�N�g���[�̍��G
    void factorySearch();

    //! �t�@�N�g���[���烆�j�b�g�ւ̍U��
    void attackToUnit();
    void attackToUnitTypeA(UnitManager* emng_, FactoryManager* fmng_);
    void attackToUnitTypeB(UnitManager* emng_, FactoryManager* fmng_);
    void attackToUnitTypeC(UnitManager* emng_, FactoryManager* fmng_);
    void attackToUnitTypeD(UnitManager* emng_, FactoryManager* fmng_);

    //! �G�̍��G�͈͂ƃ}�E�X�|�C���^�̓����蔻��
    void checkHit();

    //! �G�̍��G�͈͂ƃ}�E�X�|�C���^�̓����蔻��
    bool hitMousePointToFactory( FactoryBase* type_);
    //! �G�̍��G�͈͂ƃ}�E�X�|�C���^�̓����蔻��
    bool hitMousePointToMainFactory();

    //! �X�e�[�W�N���A����
    void stageCrear();
    //! �X�e�[�W�N���A�e�L�X�g�̃A�j���[�V����
    void textAnim(int& alpha_back_, int& alpha_text_);

    //! �X�e�[�W�N���A�e�L�X�g�̕`��
    void textRender();

    void setTime(int time_) { _time = time_; }

private:
    // ���j�b�g�}�l�[�W���[�̃��j�[�N�|�C���^�[
    std::unique_ptr<UnitManager> _eMng;

    // �t�@�N�g���[�l�[�W���[�̃��j�[�N�|�C���^�[
    std::unique_ptr<FactoryManager> _fMng;
    s16                             _stage;

    //! UI�}�l�[�W���[�̃��j�[�N�|�C���^
    std::unique_ptr<uiManager> _uiMng;

    //! �G�̍��G�͈͂ƃ}�E�X�|�C���^�̓����蔻��
    bool _hit_mouse_point;

    //! �e���ߓx
    int _alpha_back;
    int _alpha_text;

    //! ���̃V�[���֐i�ރL�[�������ꂽ���ǂ���
    bool _is_end;

    //! �N���A�������ǂ���
    bool _is_clear;

    int _time;
};
