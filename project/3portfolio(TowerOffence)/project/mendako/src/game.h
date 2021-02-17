//---------------------------------------------------------------------------
//!	@file	game.h
//!	@brief	ソースコード全体の管理
//---------------------------------------------------------------------------

#pragma once

//===========================================================================
//! ゲームメイン基底
//===========================================================================
class Game
{
public:
    Game();
    ~Game();

    void initialize();   //! 初期化
    void update();       //! 更新
    void render();       //! 描画
    void finalize();     //! 解放

public:
private:
    //! カメラ用変数
    //! カメラの現在位置
    VECTOR _cameraPos;
    //! カメラの注視点
    VECTOR _cameraTarget;
    //! カメラの向いている方向
    f32 _cameraDir;

    //! クリア情報管理用
    class StageManager* _sMng;

    //! 現在のステージ情報
    s16 _stage;
};
