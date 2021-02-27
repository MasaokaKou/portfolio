//---------------------------------------------------------------------------
//!	@file	factoryManager.h
//!	@brief	FactoryClassの管理
//---------------------------------------------------------------------------

#pragma once

#include "factoryBase.h"
#include "factoryTypeA.h"
#include "factoryTypeB.h"
#include "factoryTypeC.h"
#include "mainFactory.h"

class FactoryManager
{
public:
    FactoryManager(s16 stage_);
    ~FactoryManager();

    //! 初期化
    bool initialize();
    //! 更新
    void update();
    //! 描画
    void render();
    //! 解放
    void finalize();

public:
    //! 最後に残っている数
    int checkNum();
    int checkMax();

    //! 消滅処理
    void deleteObj();

    //! ゲッター
    VECTOR pos(s16 i);

    TYPE type(s16 i);

    bool checkInstance();
    bool checkInstance_b();
    bool checkInstance_c();
    bool checkInstance_main();

    VECTOR hitPos(s16 i_);

    VECTOR hitPosMain();
    s16    hitSizeMain();

    bool setAtk() {}

    size_t factoryTypeASize() { return _factory_a.size(); }
    size_t factoryTypeBSize() { return _factory_b.size(); }
    size_t factoryTypeCSize() { return _factory_c.size(); }

    FactoryTypeA* typeA(u32 index_) const { return _factory_a[index_].get(); }
    FactoryTypeB* typeB(u32 index_) const { return _factory_b[index_].get(); }
    FactoryTypeC* typeC(u32 index_) const { return _factory_c[index_].get(); }
    mainFactory*  typeMain() const { return _mainFactory.get(); }

private:
    //! ファクトリーのユニークポインター
    std::vector<std::unique_ptr<FactoryTypeA>> _factory_a;
    std::vector<std::unique_ptr<FactoryTypeB>> _factory_b;
    std::vector<std::unique_ptr<FactoryTypeC>> _factory_c;

    std::unique_ptr<mainFactory> _mainFactory;
    s16                          _stage;

    //! ステージごとの敵の最大数(TYPE)
    int _num_max_a, _num_max_b, _num_max_c;
    //! ステージごとの敵の最大数
    int _num_max;
    //! 最終スコア用
    int _num;
};
