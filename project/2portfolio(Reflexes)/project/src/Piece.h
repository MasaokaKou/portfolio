#pragma once

#include"BasePiece.h"

//--------------------------------
//! king‚Ì‹î
//--------------------------------

class KingPiece
	: public BasePiece
{
public:
	KingPiece();
	~KingPiece();

	void draw() override;

private:
	
};

//--------------------------------
//! Attacker‚Ì‹î
//--------------------------------
class Attacker
	:public BasePiece
{
public:
	Attacker();
	~Attacker();

	void draw();

private:

};

//--------------------------------
//! Defender‚Ì‹î
//--------------------------------
class Defender
	:public BasePiece
{
public:
	Defender();
	~Defender();

	void draw();

private:

};



