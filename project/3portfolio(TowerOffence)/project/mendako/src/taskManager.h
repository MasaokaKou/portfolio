#pragma once
//---------------------------------------------------------------------------
//!	@file	taskMaanager.h
//!	@brief	タスク管理
//---------------------------------------------------------------------------
#include "unitManager.h"
#include "factoryManager.h"
//===========================================================================
//!	タスクマネージャー
//===========================================================================

class TaskManager
{
public:
    TaskManager(s16 stage_);
    ~TaskManager();

    //! 初期化
    bool initialize();

    //! 更新
    void update();

    //! 描画
    void render();

    //! 解放
    void finalize();

public:
    //! ユニットの索敵
    void unitSearch();
    void unitSearchTypeD(UnitManager* emng_);

    //! ファクトリーの索敵
    void factorySearch();

    //! ファクトリーからユニットへの攻撃
    void attackToUnit();
    void attackToUnitTypeA(UnitManager* emng_, FactoryManager* fmng_);
    void attackToUnitTypeB(UnitManager* emng_, FactoryManager* fmng_);
    void attackToUnitTypeC(UnitManager* emng_, FactoryManager* fmng_);
    void attackToUnitTypeD(UnitManager* emng_, FactoryManager* fmng_);

    //! 敵の索敵範囲とマウスポインタの当たり判定
    void checkHit();

    //! 敵の索敵範囲とマウスポインタの当たり判定
    bool hitMousePointToFactory( FactoryBase* type_);
    //! 敵の索敵範囲とマウスポインタの当たり判定
    bool hitMousePointToMainFactory();

    //! ステージクリア処理
    void stageCrear();
    //! ステージクリアテキストのアニメーション
    void textAnim(int& alpha_back_, int& alpha_text_);

    //! ステージクリアテキストの描画
    void textRender();

    void setTime(int time_) { _time = time_; }

private:
    // ユニットマネージャーのユニークポインター
    std::unique_ptr<UnitManager> _eMng;

    // ファクトリーネージャーのユニークポインター
    std::unique_ptr<FactoryManager> _fMng;
    s16                             _stage;

    //! UIマネージャーのユニークポインタ
    std::unique_ptr<uiManager> _uiMng;

    //! 敵の索敵範囲とマウスポインタの当たり判定
    bool _hit_mouse_point;

    //! 各透過度
    int _alpha_back;
    int _alpha_text;

    //! 次のシーンへ進むキーが押されたかどうか
    bool _is_end;

    //! クリアしたかどうか
    bool _is_clear;

    int _time;
};
