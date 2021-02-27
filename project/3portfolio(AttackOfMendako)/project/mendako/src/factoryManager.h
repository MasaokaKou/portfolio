//---------------------------------------------------------------------------
//!	@file	factoryManager.h
//!	@brief	FactoryClass�̊Ǘ�
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

    //! ������
    bool initialize();
    //! �X�V
    void update();
    //! �`��
    void render();
    //! ���
    void finalize();

public:
    //! �Ō�Ɏc���Ă��鐔
    int checkNum();
    int checkMax();

    //! ���ŏ���
    void deleteObj();

    //! �Q�b�^�[
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
    //! �t�@�N�g���[�̃��j�[�N�|�C���^�[
    std::vector<std::unique_ptr<FactoryTypeA>> _factory_a;
    std::vector<std::unique_ptr<FactoryTypeB>> _factory_b;
    std::vector<std::unique_ptr<FactoryTypeC>> _factory_c;

    std::unique_ptr<mainFactory> _mainFactory;
    s16                          _stage;

    //! �X�e�[�W���Ƃ̓G�̍ő吔(TYPE)
    int _num_max_a, _num_max_b, _num_max_c;
    //! �X�e�[�W���Ƃ̓G�̍ő吔
    int _num_max;
    //! �ŏI�X�R�A�p
    int _num;
};
