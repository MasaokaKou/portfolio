#pragma once
//---------------------------------------------------------------------------
//!	@file	unitTypeB.h
//!	@brief	UnitTypeBฬภ
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! ฃฬG
//---------------------------------------------------------------------------

class UnitTypeB
: public UnitBase
{
public:
    UnitTypeB();
    ~UnitTypeB();

public:
    bool initialize();   //! ๚ป
    void update();       //! XV
    void render();       //! `ๆ
    void finalize();     //! ๐๚

public:
    //! ฃํฬฎซ
    void atkMove(VECTOR fac_pos_, f32 fac_size_, STATE state_);
    

private:
    //! ฃUฬfiEjj
    std::unique_ptr<Model> _model;  
    MATRIX                 _mat;

    


};
