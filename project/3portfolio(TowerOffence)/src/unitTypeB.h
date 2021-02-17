#pragma once
//---------------------------------------------------------------------------
//!	@file	unitTypeB.h
//!	@brief	UnitTypeB�̎���
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! �������̓G
//---------------------------------------------------------------------------

class UnitTypeB
: public UnitBase
{
public:
    UnitTypeB();
    ~UnitTypeB();

public:
    bool initialize();   //! ������
    void update();       //! �X�V
    void render();       //! �`��
    void finalize();     //! ���

public:
    //! ����������̓���
    void atkMove(VECTOR fac_pos_, f32 fac_size_, STATE state_);
    

private:
    //! �������U���̃��f���i�E�j�j
    std::unique_ptr<Model> _model;  
    MATRIX                 _mat;

    


};
