//---------------------------------------------------------------------------
//!	@file	sceneTest3.cpp
//!	@brief	Unitの当たり判定の動きの実装
//---------------------------------------------------------------------------

#pragma once
//#include "objBase.h"

//===========================================================================
//! ユニット
//===========================================================================



class unitSelector :public Scene
{
public:
    unitSelector();
    ~unitSelector();

    bool initialize();   //! 初期化
    void update();       //! 更新
    void render();       //! 描画
    void finalize();     //! 解放

public:
    //! 一度カーソルを動かしてから次にうごかせるまで
    bool timer();
    //! カーソルの移動制限
    void limit();

    //! 各ユニットの上限をもらってくる
    void setUnitLimit(std::vector<s16> unit_limit_);

    //! マウスとセレクトボックスの判定
    void hitMouseCheck();
    void setUnitFromMouse();
    bool checkHit(int i_);


    //! 選べるユニットの制限
    void lockUnit();

    //! 鎖描画
    void drawLock(int i_);

    //! アンロックアニメーション
    void lockAnim(int i_);


    //! ユニットにカーソルを合した時のテキスト
    void textTypeOfUnit(int i_);

public:
    s16 selNum()
    {
        return _sel_num;
    }
    
private:
    //! どのユニットを選択しているか
    //! unitManagerに渡す
    s16 _sel_num;

    //! セレクターカーソル
    //!(x,y,h&w)
    VECTOR _sel_car;
    //! セレクターボックス
    VECTOR _sel_box[UNIT_MAX];
    

    //!　カーソル移動フラグ
    bool _is_move;
    //! カーソル移動間隔
    s16 _timer;
    //! 各ユニット画像
    int _graph[UNIT_MAX];

    //! 各ユニットの上限
    std::vector<s16> _unit_limit;

    //! マウスカーソル
    int _mouse_x, _mouse_y;
    bool _is_hit[UNIT_MAX];

    //! 鎖の画像
    int _lock_graph;

    
};
