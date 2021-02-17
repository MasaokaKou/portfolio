//!	@file	tutorial.cpp
//!	@brief	チュートリアルの管理
//---------------------------------------------------------------------------
#pragma once

//===========================================================================
//!	チュートリアルの管理
//===========================================================================

enum FLOW
{

    NONE,
    GAME_STYLE,
    UNIT1,      //味方ユニットの召喚可能範囲説明
    UNIT_NUM,   //召喚可能数の説明
    UNIT2,      //味方ユニットの出し方
    Unit,      //敵の確認　
    BOSS,       //ゲームクリア条件の確認

    STAY,    //チュートリアルフロー一時停止
    UNIT3,   //ユニットの追加と説明
    END

};

class Tutorial
{
public:
    Tutorial();
    ~Tutorial();

    void initialize();   //! 初期化
    void update();       //! 更新
    void render();       //! 描画
    void finalize();     //! 解放

public:
    //! モデルと吹き出しの登場アニメーション
    void startAnimation();

    //! 吹き出しを出す
    void setSpeech();

    //! チュートリアルの流れ
    void flow();

    //! 簡単なゲームの紹介
    void firstGameStyle();

    //1 味方ユニットの召喚可能範囲説明
    void howRangeSetUnit();

    //1 味方ユニットの出し方
    void howToSetUnit();

    //1 敵の確認　
    void checkUnit();

    //1 ゲームクリア条件の確認
    void checkBossUnit();

    //ユニットの追加と説明
    void typeToUnit();

    //! ステージ番号を持ってくる
    void setStageNum(int stageNum_);

    FLOW getFlow();
    void setFlow(FLOW a_);

    //! テキストが出ているかどうかのフラグ
    bool isVisible() { return _is_visible; }
    void setIsVisible(bool a) { _is_visible = a; }

    bool IsTypeToUnit();

private:
    //! チュートリアル用モデル
    Model* _mendako;

    int _graphHandle;

    //! モデルの吹き出し
    s16 _speech_graph_x, _speech_graph_y;
    s16 _speech_under_graph_y;

    //! 説明部位の矢印または円
    int _arrow_graph_x, _arrow_graph_y;

    //! チュートリアル中に吹き出し、モデルの有無
    bool _is_visible;

    //! 流れ
    FLOW _flow;

    //! 間隔
    bool _span;

    //! ステージ番号
    int _stageNum;

    //! ユニットの説明フラグ
    bool _type_to_unit;

    //! 円の画像
    int _g_handle;
};
