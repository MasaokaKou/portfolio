#pragma once
#define WINDOW_W 640
#define WINDOW_H 480



#include <windows.h>
#include <time.h>
#include <math.h>
#include <memory>



#pragma warning (disable : 4819)

#include <d3d9.h>

#include "../dxlib/DxLib.h"

#include "Game.h"

#include"Typedef.h"
#include"Scene.h"
#include"SceneTitle.h"
#include"SceneGame.h"
#include"SceneResult.h"

#include"Vector2.h"

bool PushHitKey( int key );
bool CheckMouseInput( void );
bool PushMouseInput( void );
int GetMouseX( void );
int GetMouseY( void );


//---------------------------------------
//! シーン管理
//---------------------------------------

//! シーンジャンプをリクエスト
//! 新しいシーンのインスタンス（Scene）

//void sceneJump(Scene * scene);



// 描画用
void checgeText(s16 obj, f32 x, f32 y, u64 r, u64 g, u64 b);

// 描画用
void chengeText2(s16 obj, f32 x, f32 y, u64 r, u64 g, u64 b, s64 handle);


//extern void checgeText(s16 obj, Vector2 _pos, s16 r, s16 g, s16 b);

class moveScene
{
public:
	moveScene();
	~moveScene();

	bool update();
	void draw();

	bool isDown() { return _isDown; }
	bool isEnd() { return _isEnd; }
private:
	Vector2 _pos;
	Vector2 _size;

	bool _isDown;
	bool _isEnd;
	
};


