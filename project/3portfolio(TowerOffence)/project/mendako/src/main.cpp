//---------------------------------------------------------------------------
//!	@file	main.cpp
//!	@brief	���C�����[�v�Ǘ�
//---------------------------------------------------------------------------

// EffekseerForDXLib.h���C���N���[�h���܂��B
#include "EffekseerForDXLib.h"

char KeyBuffer[256];
char KeyBefore[256];
int  MouseBefore = 0;

//! Game�N���X�̃C���X�^���X
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

    // Effekseer���g�p����ɂ͕K���ݒ肷��B
    SetUseDirect3DVersion(DX_DIRECT3D_11);

    // DX���C�u����������������B
    if(DxLib_Init() == -1)
        return -1;

    // Effekseer������������B
    // �����ɂ͉�ʂɕ\������ő�p�[�e�B�N������ݒ肷��B
    if(Effekseer_Init(8000) == -1) {
        DxLib_End();
        return -1;
    }

    // �t���X�N���[���E�C���h�E�̐؂�ւ��Ń��\�[�X��������̂�h���B
    // Effekseer���g�p����ꍇ�͕K���ݒ肷��B
    SetChangeScreenModeGraphicsSystemResetFlag(FALSE);

    // DX���C�u�����̃f�o�C�X���X�g�������̃R�[���o�b�N��ݒ肷��B
    // �E�C���h�E�ƃt���X�N���[���̐؂�ւ�����������ꍇ�͕K�����s����B
    // �������ADirectX11���g�p����ꍇ�͎��s����K�v�͂Ȃ��B
    Effekseer_SetGraphicsDeviceLostCallbackFunctions();

    game->initialize();

    // 3D�ݒ�
    SetUseZBuffer3D(TRUE);
    //SetWriteZBuffer3D(TRUE);

    //�E�C���h�E�̃T�C�Y�����R�ɕύX
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

    // Effekseer���I������B
    Effkseer_End();

    DxLib_End();
    return 0;
}

//---------------------------------------------------------------------------------
// �`��p(�e�L�X�g�ɂ�����OBJ�A�`��ʒu�AGetColor)
//---------------------------------------------------------------------------------
void chengeText(s16 obj, s16 x, s16 y, s16 r, s16 g, s16 b)
{
    //���W�`��
    char text[256];
    sprintf_s(text, "%d", obj);
    DrawString(x, y, text, GetColor(r, g, b));
}
void chengeTextF(f32 obj, s16 x, s16 y, s16 r, s16 g, s16 b)
{
    //���W�`��
    char text[256];
    sprintf_s(text, "%f", obj);
    DrawString(x, y, text, GetColor(r, g, b));
}

//! �x�N�^�[�̊|���Z
void mulVec(VECTOR& a, f32 b)
{
    a.x *= b;
    a.y *= b;
    a.z *= b;
}

//! �_�ł��镶��
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