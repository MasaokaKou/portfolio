#pragma once
// キー入力管理



void KeyInputInit();			// 初期化
int KeyInputUpdate();			// 更新
void KeyInputExit();			// 終了

bool IsKeyOn(int key_id);		// 1回だけ
bool IsKeyOnJoy(int key_id);
bool IsKeyRelese(int key_id);	// 離された
bool IsKeyRepeat(int key_id);	// 2回以上(長押し)