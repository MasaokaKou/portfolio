//---------------------------------------------------------------------------
//!	@file	main.cpp
//!	@brief	メインループ管理
//---------------------------------------------------------------------------

// EffekseerForDXLib.hをインクルードします。
#include "EffekseerForDXLib.h"

char KeyBuffer[256];
char KeyBefore[256];
int  MouseBefore = 0;

//! Gameクラスのインスタンス
std::unique_ptr<Game> game;

//---------------------------------------------------------------------------------
//	WinMain
//---------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int Time;

    game = std::make_unique<Game>();

    SetOutApplicationLogValidFlag(FALSE);
    ChangeWindowMode(true);
    ChangeWindowMode(false);
    SetWindowText("TD");
    SetBackgroundColor(128, 128, 128);

    SetGraphMode(640, 480, 32);

    if(DxLib_Init() == -1)
        return -1;

   // SetUseLighting(false);
    //SetMaterialUseVertSpcColor(false);
    //SetMaterialUseVertDifColor(true);

    SetDrawScreen(DX_SCREEN_BACK);
    SetTransColor(255, 0, 255);
    srand(GetNowCount() % RAND_MAX);

    // Effekseerを使用するには必ず設定する。
    SetUseDirect3DVersion(DX_DIRECT3D_11);

    // DXライブラリを初期化する。
    if(DxLib_Init() == -1)
        return -1;

    // Effekseerを初期化する。
    // 引数には画面に表示する最大パーティクル数を設定する。
    if(Effekseer_Init(8000) == -1) {
        DxLib_End();
        return -1;
    }

    // フルスクリーンウインドウの切り替えでリソースが消えるのを防ぐ。
    // Effekseerを使用する場合は必ず設定する。
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

    // DXライブラリのデバイスロストした時のコールバックを設定する。
    // ウインドウとフルスクリーンの切り替えが発生する場合は必ず実行する。
    // ただし、DirectX11を使用する場合は実行する必要はない。
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();

    game->initialize();

    // 3D設定
    SetUseZBuffer3D(TRUE);
    //SetWriteZBuffer3D(TRUE);

    //ウインドウのサイズを自由に変更
    SetWindowSizeChangeEnableFlag(true);

    while(TRUE) {
        Time = GetNowCount();
        ClearDrawScreen();

        GetHitKeyStateAll(KeyBuffer);

        game->update();
        game->render();

        memcpy(KeyBefore, KeyBuffer, sizeof(char) * 256);
        MouseBefore = GetMouseInput();

        //OutputDebugString("==============================================\n");

        ScreenFlip();
        while(GetNowCount() - Time < 17) {
        }
        if(ProcessMessage())
            break;
        if(CheckHitKey(KEY_INPUT_ESCAPE))
            break;
    }

    game->finalize();
    game.reset();

    // Effekseerを終了する。
    Effkseer_End();

    DxLib_End();
    return 0;
}

//---------------------------------------------------------------------------------
// 描画用(テキストにしたいOBJ、描画位置、GetColor)
//---------------------------------------------------------------------------------
void chengeText(s16 obj, s16 x, s16 y, s16 r, s16 g, s16 b)
{
    //座標描画
    char text[256];
    sprintf_s(text, "%d", obj);
    DrawString(x, y, text, GetColor(r, g, b));
}
void chengeTextF(f32 obj, s16 x, s16 y, s16 r, s16 g, s16 b)
{
    //座標描画
    char text[256];
    sprintf_s(text, "%f", obj);
    DrawString(x, y, text, GetColor(r, g, b));
}

//! ベクターの掛け算
void mulVec(VECTOR& a, f32 b)
{
    a.x *= b;
    a.y *= b;
    a.z *= b;
}

//! 点滅する文字
void blinkText(int x, int y, const char* text)
{
    static int count = 0;

    if(count <= 30)
        DrawString(x, y, text, WHITE, true);

    count++;

    if(count >= 60) {
        count = 0;
    }
}