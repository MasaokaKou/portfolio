#include "Main.h"
#include"Game.h"


char KeyBuffer[256];
char KeyBefore[256];
int MouseBefore = 0;

// ゲームそのもののインスタンス
Game game;

//! 初期化時のカスタマイズ
extern bool onInitialize();

//! 更新時のカスタマイズ
extern void onUpdate();

//! 解放時のカスタマイズ
extern void onFinalize();


//---------------------------------------------------------------------------------
//	WinMain
//---------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int Time;

	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);
	SetWindowText("サンプル");
	SetBackgroundColor(157, 204, 224);

	SetGraphMode(640, 480, 32);

	if (DxLib_Init() == -1)	return -1;

	SetDrawScreen(DX_SCREEN_BACK);
	SetTransColor(255, 0, 255);
	srand(GetNowCount() % RAND_MAX);

	game.Init();

	// シーンっ切り替えわからん
	// シーンの切り替えと実行
	//Scene::sceneUpdate();
	//Scene::sceneJump(new SceneGame());



	while (TRUE)
	{
		Time = GetNowCount();
		ClearDrawScreen();

		GetHitKeyStateAll(KeyBuffer);

		game.Update();
		game.Render();



		memcpy(KeyBefore, KeyBuffer, sizeof(char) * 256);
		MouseBefore = GetMouseInput();

		ScreenFlip();
		while (GetNowCount() - Time < 17) {}
		if (ProcessMessage())	break;
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;
	}

	game.Exit();

	DxLib_End();
	return 0;
}

//---------------------------------------------------------------------------------
//	キーが押された瞬間を取得する
//---------------------------------------------------------------------------------
bool PushHitKey(int key)
{
	int buffer = KeyBuffer[key];
	int before = KeyBefore[key];
	if (buffer == 1 && before == 0) {
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	マウスが押されているかを取得する
//---------------------------------------------------------------------------------
bool CheckMouseInput(void)
{
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		return true;
	}
	return false;
}
//---------------------------------------------------------------------------------
//	マウスが押された瞬間を取得する
//---------------------------------------------------------------------------------
bool PushMouseInput(void)
{
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		if (MouseBefore == 0) {
			return true;
		}
	}
	return false;
}
//---------------------------------------------------------------------------------
//	マウスの座標を取得する
//---------------------------------------------------------------------------------
int GetMouseX(void)
{
	int mouse_x;
	int mouse_y;
	GetMousePoint(&mouse_x, &mouse_y);
	return mouse_x;
}
int GetMouseY(void)
{
	int mouse_x;
	int mouse_y;
	GetMousePoint(&mouse_x, &mouse_y);
	return mouse_y;
}
//---------------------------------------------------------------------------------
// 描画用(テキストにしたいOBJ、描画位置、GetColor)
//---------------------------------------------------------------------------------
void checgeText(s16 obj, f32 x, f32 y, u64 r, u64 g, u64 b)
{
	//座標描画
	char text[256];
	sprintf_s(text, "%d", obj);
	DrawString(x, y, text, GetColor(r, g, b));

}

void chengeText2(s16 obj, f32 x, f32 y, u64 r, u64 g, u64 b, s64 handle)
{
	//座標描画
	char text[256];
	sprintf_s(text, "%d", obj);
	DrawStringToHandle(x, y, text, GetColor(r, g, b), handle);

}


//! シーン移動用の垂れ幕
moveScene::moveScene()
{
	_pos.set(0,0);
	_size.set(WINDOW_W,0);

	_isDown = true;
	_isEnd = false;

}

moveScene::~moveScene()
{
}

bool moveScene::update()
{
	if (_size.y >= WINDOW_H)
		_isDown = false;
		
	if (_isDown)
		_size.y += 5;

	if (!_isDown)
		_size.y -= 5;

	if (_size.y < 0) {
		_isEnd = true;
		return true;

	}
	return false;
}
void moveScene::draw()
{
	DrawBox(_pos.x, _pos.y, _pos.x + _size.x, _pos.y + _size.y, GetColor(255, 255, 255), true);
}