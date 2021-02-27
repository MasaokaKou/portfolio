#pragma once
//---------------------------------------------------------------------------
//!	@file	unitTypeB.h
//!	@brief	UnitTypeB�̎���
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! �������̓G
//---------------------------------------------------------------------------

class UnitTypeC
: public UnitBase
{
public:
    UnitTypeC();
    ~UnitTypeC();

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

private:
    //! ��蕨�̃��f��
    std::unique_ptr<Model> _model;
    MATRIX                 _mat;

    int _graphHandle;
    bool _modelDead;

    //! ���f���̓��ߓx
    f32 _alpha;

    //! �J���̃��f���̓����悤�^�C�}�[
    int _dead_timer;
};
