#pragma once

class Game
{
public:
	Game() {};
	virtual~Game() {};

	void Init(void);		//	初期化処理
	void Exit(void);		//	終了処理
	void Update(void);	    //	更新処理
	void Render(void);	    //	描画処理


private:

	// シーンマネージャーのインスタンス
	class SceneManager * _sMngIns;
	


};



