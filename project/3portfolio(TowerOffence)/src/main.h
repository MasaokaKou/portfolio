//---------------------------------------------------------------------------
//!	@file	main.h
//!	@brief	���C�����[�v�Ǘ�
//---------------------------------------------------------------------------

#pragma once
#define WINDOW_W 640
#define WINDOW_H 480

#include <windows.h>
#include <time.h>
#include <math.h>

#pragma warning(disable : 4819)

#include <d3d9.h>

#include "../dxlib/DxLib.h"
#include "typedef.h"

//!�@�F���
const u32 WHITE = GetColor(255, 255, 255);
const u32 BLACK = GetColor(0, 0, 0);
const u32 RED   = GetColor(255, 0, 0);

#define TO_RADIAN(degree) (((degree)*3.14159265f) / 180.0f)

// �`��p
void chengeText(s16 obj, s16 x, s16 y, s16 r, s16 g, s16 b);
void chengeTextF(f32 obj, s16 x, s16 y, s16 r, s16 g, s16 b);

//! �x�N�^�[�̊|���Z
void mulVec(VECTOR& a, f32 b);

//! �_�ł��镶��
void blinkText(int x, int y, const char * text);

