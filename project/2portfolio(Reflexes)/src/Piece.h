#pragma once

#include"BasePiece.h"

//--------------------------------
//! king�̋�
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
//! Attacker�̋�
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
//! Defender�̋�
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



