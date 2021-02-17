#include"Main.h"
#include"Game.h"
#include"Keyinput.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);
	ChangeWindowMode(TRUE);
	SetGraphMode(WINDOW_W, WINDOW_H, 32);
	
	
		SetBackgroundColor(0,0,0);

	

	SetMainWindowText("��Ɖۑ�");

	if (DxLib_Init
	() == -1) {
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	const unsigned int BALL_COLOR = GetColor(255, 182, 193);



	GameInit();
	//�E�C���h�E�̃T�C�Y�����R�ɕύX
	SetWindowSizeChangeEnableFlag(true);


	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();
		clsDx();



		GameUpdate();
		GameRender();
		// ----------------------------------------------------


		ScreenFlip();
	}
	GameExit();
	DxLib_End();

	return 0;
}