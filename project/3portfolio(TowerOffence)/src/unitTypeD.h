#pragma once
//---------------------------------------------------------------------------
//!	@file	unitTypeB.h
//!	@brief	UnitTypeB�̎���
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! �񕜗p���j�b�g
//---------------------------------------------------------------------------

class UnitTypeD
: public UnitBase
{
public:
    UnitTypeD();
    ~UnitTypeD();

public:
    bool initialize();   //! ������
    void update();       //! �X�V
    void render();       //! �`��
    void finalize();     //! ���

public:
    //! ���f�����̂��̂̓���
    void modelMove();
    //! ���f���̏��Ń��[�V����
    void modelDead();

    bool isMolDead() { return _modelDead; }
    //! ���f���̕����]��
    void direction(VECTOR dir_);

    //! �񕜃��[�V�����X�V
    void atkAnimUpdate();

    //! �񕜃��[�V�����`��
    void atkAnimDraw();

private:
    //! ��蕨�̃��f��
    std::unique_ptr<Model> _ride_model;
    MATRIX                 _mat;

    //! �U���p�̃��f��
    std::unique_ptr<Model> _atk_circle;
    int                    _atk_alpha;
    f32                    _atk_scale;


    int  _graphHandle;
    bool _modelDead;

    //! �N���I�l�̃��f���̓����悤�^�C�}�[
    int _dead_timer;
};
