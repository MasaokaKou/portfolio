//---------------------------------------------------------------------------
//!	@file	factoryManager.cpp
//!	@brief	FactoryClassの管理
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! コンストラクタ
//---------------------------------------------------------------------------
FactoryManager::FactoryManager(s16 stage_)
{
    _stage = stage_;

    //! ファクトリーの実体生成

    _mainFactory = std::make_unique<mainFactory>();

    _num_max   = 0;
    _num_max_a = 0;
    _num_max_b = 0;
    _num_max_c = 0;
    _num       = 0;
}

//---------------------------------------------------------------------------
//! デストラクタ
//---------------------------------------------------------------------------
FactoryManager::~FactoryManager()
{
}

//---------------------------------------------------------------------------
//! 初期化
//---------------------------------------------------------------------------
bool FactoryManager::initialize()
{
    s16 num = _stage;

    VECTOR pos_a[10];
    VECTOR pos_b[10];
    VECTOR pos_c[10];
    VECTOR main = VGet(60, 0, 60);

    switch(num) {
        case 0:
            _num_max_a = 3;

            //! 必要名分プッシュバック
            for(s16 i = 0; i < _num_max_a; i++) {
                _factory_a.push_back(std::make_unique<FactoryTypeA>());
            }

            pos_a[0] = VGet(10, 0, 10);
            pos_a[1] = VGet(25, 0, 25);
            pos_a[2] = VGet(40, 0, 40);

            _mainFactory->initialize();
            _mainFactory->setPos(main);
            for(s16 i = 0; i < _factory_a.size(); i++) {
                if(_factory_a[i]) {
                    _factory_a[i]->initialize();

                    _factory_a[i]->setPos(pos_a[i]);
                }
            }
            break;

        case 1:
            _num_max_b = 3;

            //! 必要名分プッシュバック
            for(s16 i = 0; i < _num_max_b; i++) {
                _factory_b.push_back(std::make_unique<FactoryTypeB>());
            }
            pos_b[0] = VGet(10, 0, 40);
            pos_b[1] = VGet(30, 0, 30);
            pos_b[2] = VGet(40, 0, 10);

            _mainFactory->initialize();
            _mainFactory->setPos(main);
            for(s16 i = 0; i < _factory_b.size(); i++) {
                if(_factory_b[i]) {
                    _factory_b[i]->initialize();

                    _factory_b[i]->setPos(pos_b[i]);
                }
            }
            break;
        case 2:
            _num_max_c = 3;

            //! 必要名分プッシュバック
            for(s16 i = 0; i < _num_max_c; i++) {
                _factory_c.push_back(std::make_unique<FactoryTypeC>());
            }
            pos_c[0] = VGet(10, 0, 10);
            pos_c[1] = VGet(25, 0, 25);
            pos_c[2] = VGet(40, 0, 40);

            _mainFactory->initialize();
            _mainFactory->setPos(main);
            for(s16 i = 0; i < _factory_c.size(); i++) {
                if(_factory_c[i]) {
                    _factory_c[i]->initialize();

                    _factory_c[i]->setPos(pos_c[i]);
                }
            }

            break;
        case 3:
            _num_max_a = 6;
            _num_max_b = 3;

            for(s16 i = 0; i < _num_max_a; i++) {
                _factory_a.push_back(std::make_unique<FactoryTypeA>());
            }

            for(s16 i = 0; i < _num_max_b; i++) {
                _factory_b.push_back(std::make_unique<FactoryTypeB>());
            }

            pos_a[0] = VGet(30, 0, 70);
            pos_a[1] = VGet(40, 0, 40);
            pos_a[2] = VGet(60, 0, 30);
            pos_a[3] = VGet(10, 0, 10);
            pos_a[4] = VGet(40, 0, 0);
            pos_a[5] = VGet(0, 0, 40);

            pos_b[0] = VGet(25, 0, 25);
            pos_b[1] = VGet(20, 0, 50);
            pos_b[2] = VGet(45, 0, 20);

            _mainFactory->initialize();
            _mainFactory->setPos(main);

            for(s16 i = 0; i < _factory_a.size(); i++) {
                if(_factory_a[i]) {
                    _factory_a[i]->initialize();
                    _factory_a[i]->setPos(pos_a[i]);
                }
            }

            for(s16 i = 0; i < _factory_b.size(); i++) {
                if(_factory_b[i]) {
                    _factory_b[i]->initialize();
                    _factory_b[i]->setPos(pos_b[i]);
                }
            }
            break;
        case 4:
            _num_max_a = 8;
            _num_max_b = 5;
            _num_max_c = 3;

            for(s16 i = 0; i < _num_max_a; i++) {
                _factory_a.push_back(std::make_unique<FactoryTypeA>());
            }

            for(s16 i = 0; i < _num_max_b; i++) {
                _factory_b.push_back(std::make_unique<FactoryTypeB>());
            }
            for(s16 i = 0; i < _num_max_c; i++) {
                _factory_c.push_back(std::make_unique<FactoryTypeC>());
            }

            pos_a[0] = VGet(10, 0, 10);
            pos_a[1] = VGet(40, 0, 0);
            pos_a[2] = VGet(0, 0, 40);
            pos_a[3] = VGet(-10, 0, -10);
            pos_a[4] = VGet(10, 0, -30);
            pos_a[5] = VGet(40, 0, -20);
            pos_a[6] = VGet(-30, 0, 20);
            pos_a[7] = VGet(-30, 0, 60);

            pos_b[0] = VGet(30, 0, 70);
            pos_b[1] = VGet(40, 0, 40);
            pos_b[2] = VGet(60, 0, 30);
            pos_b[3] = VGet(20, 0, -10);
            pos_b[4] = VGet(-10, 0, 30);

            pos_c[0] = VGet(25, 0, 25);
            pos_c[1] = VGet(20, 0, 50);
            pos_c[2] = VGet(45, 0, 20);

            _mainFactory->initialize();
            _mainFactory->setPos(main);

            for(s16 i = 0; i < _factory_a.size(); i++) {
                if(_factory_a[i]) {
                    _factory_a[i]->initialize();
                    _factory_a[i]->setPos(pos_a[i]);
                }
            }

            for(s16 i = 0; i < _factory_b.size(); i++) {
                if(_factory_b[i]) {
                    _factory_b[i]->initialize();
                    _factory_b[i]->setPos(pos_b[i]);
                }
            }

            for(s16 i = 0; i < _factory_c.size(); i++) {
                if(_factory_c[i]) {
                    _factory_c[i]->initialize();
                    _factory_c[i]->setPos(pos_c[i]);
                }
            }

            break;

        default:
            break;
    }

    //! 各タイプの最大数を足す
    _num_max = _num_max_a + _num_max_b + _num_max_c;

    return true;
}
//---------------------------------------------------------------------------
//! 更新
//---------------------------------------------------------------------------
void FactoryManager::update()
{
    //! ファクトリーの更新
    if(_mainFactory)
        _mainFactory->update();

    for(auto& a : _factory_a) {
        if(a)
            a->update();
    }

    for(auto& a : _factory_b) {
        if(a)
            a->update();
    }

    for(auto& a : _factory_c) {
        if(a)
            a->update();
    }


    deleteObj();
}
//---------------------------------------------------------------------------
//! 描画
//---------------------------------------------------------------------------
void FactoryManager::render()
{
    //! ファクトリーの描画
    if(_mainFactory)
        _mainFactory->render();

    for(auto& a : _factory_a) {
        if(a)
            a->render();
    }

    for(auto& a : _factory_b) {
        if(a)
            a->render();
    }

    for(auto& a : _factory_c) {
        if(a)
            a->render();
    }
}
//---------------------------------------------------------------------------
//! 解放
//---------------------------------------------------------------------------
void FactoryManager::finalize()
{
    //! ファクトリーの解放
    if(_mainFactory)
        _mainFactory->finalize();

    for(auto& a : _factory_a) {
        if(a)
            a->finalize();
    }

    for(auto& a : _factory_b) {
        if(a)
            a->finalize();
    }

    for(auto& a : _factory_c) {
        if(a)
            a->finalize();
    }
}

//---------------------------------------------------------------------------
//! 最後に残っている数を出す
//---------------------------------------------------------------------------
int FactoryManager::checkNum()
{
    return _num;
}
int FactoryManager::checkMax()
{
    return _num_max;
}

//---------------------------------------------------------------------------
//! 消滅処理
//---------------------------------------------------------------------------
void FactoryManager::deleteObj()
{
    if(_mainFactory) {
        if(_mainFactory->hp() <= 0) {
            _mainFactory.release();
        }
    }

    for(s16 i = 0; i < _factory_a.size(); i++) {
        if(_factory_a[i]) {
            if(_factory_a[i]->endAnimOfDead())

            {
                _factory_a[i].release();
                _factory_a.erase(_factory_a.begin() + i);
                _num += 1;
            }
        }
    }
    for(s16 i = 0; i < _factory_b.size(); i++) {
        if(_factory_b[i]) {
            if(_factory_b[i]->endAnimOfDead()) {
                _factory_b[i].release();
                _factory_b.erase(_factory_b.begin() + i);
                _num += 1;
            }
        }
    }
    for(s16 i = 0; i < _factory_c.size(); i++) {
        if(_factory_c[i]) {
            if(_factory_c[i]->endAnimOfDead()) {
                _factory_c[i].release();
                _factory_c.erase(_factory_c.begin() + i);
                _num += 1;
            }
        }
    }
}

//---------------------------------------------------------------------------
//! ゲッター
//---------------------------------------------------------------------------
VECTOR FactoryManager::pos(s16 i)
{
    if(!_factory_a.empty()) {
        return _factory_a[i]->pos();
    }
}

bool FactoryManager::checkInstance()
{
    if(!_factory_a.empty()) {
        return true;
    }

    return false;
}

TYPE FactoryManager::type(s16 i)
{
    if(!_factory_a.empty()) {
        return _factory_a[i]->type();
    }
}

//-----------------------------------------------------------------------
//! factory_b
//-----------------------------------------------------------------------

bool FactoryManager::checkInstance_b()
{
    if(!_factory_b.empty()) {
        return true;
    }

    return false;
}

//-----------------------------------------------------------------------
//! factory_c
//-----------------------------------------------------------------------

bool FactoryManager::checkInstance_c()
{
    if(!_factory_c.empty()) {
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
//! ゲッター（mainfactory）
//---------------------------------------------------------------------------

bool FactoryManager::checkInstance_main()
{
    if(_mainFactory) {
        return true;
    }

    return false;
}

VECTOR FactoryManager::hitPos(s16 i_)
{
    if(!_factory_a.empty()) {
        return _factory_a[i_]->hitPos();
    }
}

VECTOR FactoryManager::hitPosMain()
{
    if(_mainFactory) {
        return _mainFactory->hitPos();
    }
}
s16 FactoryManager::hitSizeMain()
{
    if(_mainFactory) {
        return _mainFactory->hitSize();
    }
}
