#pragma once
// �L�[���͊Ǘ�



void KeyInputInit();			// ������
int KeyInputUpdate();			// �X�V
void KeyInputExit();			// �I��

bool IsKeyOn(int key_id);		// 1�񂾂�
bool IsKeyOnJoy(int key_id);
bool IsKeyRelese(int key_id);	// �����ꂽ
bool IsKeyRepeat(int key_id);	// 2��ȏ�(������)