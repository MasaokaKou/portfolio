//---------------------------------------------------------------------------
//!	@file	TestEffect.h
//!	@brief	ソースコード全体の管理
//---------------------------------------------------------------------------

#pragma once


//===========================================================================
//! TestEffect
//===========================================================================
class TestEffect : public Scene
{
public:
	TestEffect();
	~TestEffect();

	bool initialize();     //! 初期化
	void update();		   //! 更新
	void render();         //! 描画
	void finalize();       //! 解放

public:
	

private:

};



