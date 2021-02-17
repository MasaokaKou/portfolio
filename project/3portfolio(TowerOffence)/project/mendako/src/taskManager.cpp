//---------------------------------------------------------------------------
//!	@file	taskMaanager.cpp
//!	@brief	タスク管理
//---------------------------------------------------------------------------

//===========================================================================
//!	タスクマネージャー
//===========================================================================

//---------------------------------------------------------------------------
//! コンストラクタ
//---------------------------------------------------------------------------
TaskManager::TaskManager(s16 stage_)
{
    _stage = stage_;

    // ユニットマネージャーの実体生成
    if(_eMng == nullptr)
        _eMng = std::make_unique<UnitManager>();

    // ファクトリーマネージャーの実体生成
    if(_fMng == nullptr)
        _fMng = std::make_unique<FactoryManager>(_stage);

    // UIマネージャーの実態生成
    if(_uiMng == nullptr)
        _uiMng = std::make_unique<uiManager>();

    // 敵の索敵範囲とマウスポインタの当たり判定
    _hit_mouse_point = false;

    // 各透過度
    _alpha_back = 0;
    _alpha_text = 255;

    // クリアしたかどうか
    _is_clear = false;

    // 次のシーンへ進むキーが押されたかどうか
    _is_end = false;

    // 経過時間
    _time = 0;
}
//---------------------------------------------------------------------------
//! デストラクタ
//---------------------------------------------------------------------------
TaskManager::~TaskManager()
{
}

//---------------------------------------------------------------------------
//! 初期化
//---------------------------------------------------------------------------
bool TaskManager::initialize()
{
    //! UIマネージャーの初期化
    if(_uiMng)
        _uiMng->initialize();

    //! ユニットマネージャーの初期化
    if(_eMng)
        _eMng->initialize(_stage);

    //! ファクトリーマネージャーの初期化
    if(_fMng)
        _fMng->initialize();

    return true;
}

//! 関数化
//!　索敵してＨＩＴした敵に攻撃
void search_e(FactoryBase* factory, UnitBase* Unit, UnitManager* emng)
{
    //! unit_TYPE_A
    if(Unit->search(factory->pos(), factory->size(), factory->state())) {
        factory->setDamage();
        //! ファクトリーのダメージ処理
        if(Unit->isAtk()) {
            factory->damage(Unit->atk());
            Unit->setAtk(false);
        }

        //! ファクトリーを破壊したらユニットがMOVEに
        emng->setMove(factory->hp());
    }
}

//!search_eの関数化
void search_e_func(FactoryBase* factory, UnitManager* emng)
{
    if(emng->checkInstance_a()) {
        for(s16 j = 0; j < emng->unitTypeASize(); j++) {
            auto* Unit = emng->typeA(j);

            search_e(factory, Unit, emng);
        }
    }

    // !ユニットTYPEB
    if(emng->checkInstance_b()) {
        for(s16 j = 0; j < emng->unitTypeBSize(); j++) {
            auto* Unit = emng->typeB(j);

            search_e(factory, Unit, emng);
        }
    }
    // !ユニットTYPEC
    if(emng->checkInstance_c()) {
        for(s16 j = 0; j < emng->unitTypeCSize(); j++) {
            auto* Unit = emng->typeC(j);

            search_e(factory, Unit, emng);
        }
    }
}

//! 関数化
//!　索敵してＨＩＴした敵に攻撃
void search_f(UnitManager* emng, UnitBase* Unit, FactoryBase* factory)
{
    // factory->search(Unit->pos(), Unit->size());

    //! ファクトリーを破壊したらユニットがMOVEに
    factory->setMove(Unit->hp());
}

//! search_fの関数化
void search_f_func(FactoryBase* factory, UnitManager* emng)
{
    for(s16 j = 0; j < emng->unitTypeASize(); j++) {
        if(!emng->checkInstance_a())
            continue;

        auto* Unit = emng->typeA(j);

        search_f(emng, Unit, factory);
        // break;
    }

    //! ファクトリーの索敵TYPEB

    for(s16 j = 0; j < emng->unitTypeBSize(); j++) {
        if(!emng->checkInstance_b())
            continue;

        auto* Unit = emng->typeB(j);

        search_f(emng, Unit, factory);
    }

    //! ファクトリーの索敵TYPEC

    for(s16 j = 0; j < emng->unitTypeCSize(); j++) {
        if(!emng->checkInstance_c())
            continue;

        auto* Unit = emng->typeC(j);
        search_f(emng, Unit, factory);
    }

    //! ファクトリーの索敵TYPED

    for(s16 j = 0; j < emng->unitTypeDSize(); j++) {
        if(!emng->checkInstance_d())
            continue;

        auto* Unit = emng->typeD(j);
        search_f(emng, Unit, factory);
    }
}

//! 関数化
//!　factoryからの攻撃
bool attack_f(FactoryManager* fmng, UnitBase* Unit, FactoryBase* factory)
{
    if(factory->atkSearch(Unit->pos(), Unit->size(), Unit->hp())) {
        Unit->isDamage();
        Unit->damage(factory->isAtk(), factory->atk());
    }

    if(factory->search(Unit->pos(), Unit->size())) {
        if(Unit->getIsDamage())
            return true;
    }

    return false;
}

//---------------------------------------------------------------------------
//! 更新
//---------------------------------------------------------------------------
void TaskManager::update()
{
    //! UIマネージャーの更新
    //! unitManagerに渡したいものがあるので最上階層
    if(_uiMng)
        _uiMng->update();

    //! 一番上で本拠地を固定
    if(_eMng) {
        _eMng->setMainTarget(VGet(60, 0, 60));
    }

    //! クリアしたかどうか
    if(_is_clear)
        return;

    //! 敵の索敵範囲とマウスポインタの当たり判定
    checkHit();

    //! 敵の索敵
    unitSearch();

    //! ファクトリーの索敵
    factorySearch();

    //! ファクトリーからユニットへの攻撃
    attackToUnit();

    //! ユニットマネージャーの更新
    if(_eMng) {
        _eMng->update(_uiMng.get()->selNum(), _hit_mouse_point);
    }

    //! ユニットの上限をUIMngに渡す
    if(_uiMng) {
        for(s16 i = 0; i < UNIT_MAX; i++) {
            _uiMng->setUnitLimit(_eMng.get()->unit_limit());
        }
    }

    //! ファクトリーマネージャーの更新
    if(_fMng) {
        _fMng->update();
        stageCrear();
    }
}

//---------------------------------------------------------------------------
//! 描画
//---------------------------------------------------------------------------
void TaskManager::render()
{
    //! UIマネージャーの描画
    if(_uiMng)
        _uiMng.get()->render();

    //! ファクトリーマネージャーの描画
    if(_fMng)
        _fMng.get()->render();

    //! ユニットマネージャーの描画
    if(_eMng)
        _eMng.get()->render();

    textRender();
}

//---------------------------------------------------------------------------
//! 解放
//---------------------------------------------------------------------------
void TaskManager::finalize()
{
    //! UIマネージャーの解放
    if(_uiMng)
        _uiMng.get()->finalize();

    //! ユニットマネージャーの解放
    if(_eMng) {
        _eMng->finalize();
        _eMng.release();
    }

    //! fファクトリーマネージャーの解放
    if(_fMng) {
        _fMng->finalize();
        _fMng.release();
    }
}
//---------------------------------------------------------------------------
//! ユニットの索敵
//---------------------------------------------------------------------------
void TaskManager::unitSearch()
{
    //!(ファクトリーマネージャーの消滅処理を先にするとhp<=0をとってこれない)

    //-----------------------------------------------------------------------
    //! factory_a
    //-----------------------------------------------------------------------
    // !ユニットTYPEA
    if(_fMng->checkInstance()) {
        for(s16 i = 0; i < _fMng->factoryTypeASize(); i++) {
            auto* factory = _fMng->typeA(i);

            search_e_func(factory, _eMng.get());
            _eMng->atkMoveTypeB(factory->pos(), factory->size(), factory->state());
        }
    }

    //-----------------------------------------------------------------------
    //! factory_b
    //-----------------------------------------------------------------------

    if(_fMng->checkInstance_b()) {
        for(s16 i = 0; i < _fMng->factoryTypeBSize(); i++) {
            auto* factory = _fMng->typeB(i);
            search_e_func(factory, _eMng.get());
            _eMng->atkMoveTypeB(factory->pos(), factory->size(), factory->state());
        }
    }

    //-----------------------------------------------------------------------
    //! factory_c
    //-----------------------------------------------------------------------

    if(_fMng->checkInstance_c()) {
        for(s16 i = 0; i < _fMng->factoryTypeCSize(); i++) {
            auto* factory = _fMng->typeC(i);
            search_e_func(factory, _eMng.get());
            _eMng->atkMoveTypeB(factory->pos(), factory->size(), factory->state());
        }
    }

    _eMng->atkMoveTypeB(_fMng->typeMain()->pos(), _fMng->typeMain()->size(), _fMng->typeMain()->state());

    //! ユニットTYPED
    //! 各ユニットとの判定
    unitSearchTypeD(_eMng.get());
}
//---------------------------------------------------------------------------
//! ユニットTYPED
//! 各ユニットとの判定
//---------------------------------------------------------------------------
void TaskManager::unitSearchTypeD(UnitManager* emng_)
{
    if(emng_) {
        for(s16 i = 0; i < emng_->unitTypeASize(); i++) {
            for(s16 j = 0; j < emng_->unitTypeDSize(); j++) {
                if(!emng_->checkInstance_a() && emng_->checkInstance_d())
                    continue;
                if(emng_->search_d(emng_->pos_a(i), emng_->size_a(i), j)) {
                    emng_->damage_a(emng_->isAtk_d(j), emng_->atk_d(j), i, emng_->TYPE_D(j));
                }
            }
        }

        for(s16 i = 0; i < emng_->unitTypeBSize(); i++) {
            for(s16 j = 0; j < emng_->unitTypeDSize(); j++) {
                if(!emng_->checkInstance_b() && emng_->checkInstance_d())
                    continue;
                if(emng_->search_d(emng_->pos_b(i), emng_->size_b(i), j)) {
                    emng_->damage_b(emng_->isAtk_d(j), emng_->atk_d(j), i, emng_->TYPE_D(j));
                }
            }
        }
        for(s16 i = 0; i < emng_->unitTypeCSize(); i++) {
            for(s16 j = 0; j < emng_->unitTypeDSize(); j++) {
                if(!emng_->checkInstance_c() && emng_->checkInstance_d())
                    continue;
                if(emng_->search_d(emng_->pos_c(i), emng_->size_c(i), j)) {
                    emng_->damage_c(emng_->isAtk_d(j), emng_->atk_d(j), i, emng_->TYPE_D(j));
                }
            }
        }
    }
}
//---------------------------------------------------------------------------
//! ファクトリーの索敵
//---------------------------------------------------------------------------
void TaskManager::factorySearch()
{
    //! mainFactoryの判定------------------------------------------------

    if(_fMng->checkInstance_main()) {
        auto* factory = _fMng->typeMain();
        search_e_func(factory, _eMng.get());
    }
    //-----------------------------------------------------------------------
    //! factory_a
    //-----------------------------------------------------------------------
    //! ファクトリーの索敵TYPEA
    for(s16 i = 0; i < _fMng->factoryTypeASize(); i++) {
        auto* factory = _fMng->typeA(i);
        search_f_func(factory, _eMng.get());
    }

    //-----------------------------------------------------------------------
    //! factory_b
    //-----------------------------------------------------------------------
    //! ファクトリーの索敵TYPEB
    for(s16 i = 0; i < _fMng->factoryTypeBSize(); i++) {
        auto* factory = _fMng->typeB(i);
        search_f_func(factory, _eMng.get());
    }
    //-----------------------------------------------------------------------
    //! factory_c
    //-----------------------------------------------------------------------
    //! ファクトリーの索敵TYPEC
    for(s16 i = 0; i < _fMng->factoryTypeCSize(); i++) {
        auto* factory = _fMng->typeC(i);
        search_f_func(factory, _eMng.get());
    }
}

//---------------------------------------------------------------------------
//! ファクトリーからユニットへの攻撃
//---------------------------------------------------------------------------
void TaskManager::attackToUnit()
{
    auto* fmng = _fMng.get();
    auto* emng = _eMng.get();

    //!unit_a
    attackToUnitTypeA(emng, fmng);
    //!unit_b
    attackToUnitTypeB(emng, fmng);

    //!unit_c
    attackToUnitTypeC(emng, fmng);
    //!unit_d
    attackToUnitTypeD(emng, fmng);

}

//---------------------------------------------------------------------------
//! ファクトリーからユニットへの攻撃関数化
//---------------------------------------------------------------------------
void TaskManager::attackToUnitTypeA(UnitManager* emng_, FactoryManager* fmng_)
{
    for(s16 i = 0; i < fmng_->factoryTypeASize(); i++) {
        for(s16 j = 0; j < emng_->unitTypeASize(); j++) {
            if(!emng_->checkInstance_a())
                continue;

            auto* factory = fmng_->typeA(i);
            auto* Unit    = emng_->typeA(j);

            if(attack_f(fmng_, Unit, factory)) {
                break;
            }

            factory->setMove(Unit->hp());

        }
    }

    for(s16 i = 0; i < fmng_->factoryTypeBSize(); i++) {
        for(s16 j = 0; j < emng_->unitTypeASize(); j++) {
            if(!emng_->checkInstance_a())
                continue;

            auto* factory = fmng_->typeB(i);
            auto* Unit    = emng_->typeA(j);
            if(attack_f(fmng_, Unit, factory)) {
                break;
            }
        }
    }

    for(s16 i = 0; i < fmng_->factoryTypeCSize(); i++) {
        for(s16 j = 0; j < emng_->unitTypeASize(); j++) {
            if(!emng_->checkInstance_a())
                continue;

            auto* factory = fmng_->typeC(i);
            auto* Unit    = emng_->typeA(j);
            attack_f(fmng_, Unit, factory);
        }
    }
}
void TaskManager::attackToUnitTypeB(UnitManager* emng_, FactoryManager* fmng_)
{
    for(s16 i = 0; i < fmng_->factoryTypeASize(); i++) {
        for(s16 j = 0; j < emng_->unitTypeBSize(); j++) {
            if(!emng_->checkInstance_b())
                continue;

            auto* factory = fmng_->typeA(i);
            auto* Unit    = emng_->typeB(j);
            if(attack_f(fmng_, Unit, factory)) {
                break;
            }
        }
    }

    for(s16 i = 0; i < fmng_->factoryTypeBSize(); i++) {
        for(s16 j = 0; j < emng_->unitTypeBSize(); j++) {
            if(!emng_->checkInstance_b())
                continue;

            auto* factory = fmng_->typeB(i);
            auto* Unit    = emng_->typeB(j);
            if(attack_f(fmng_, Unit, factory)) {
                break;
            }
        }
    }

    for(s16 i = 0; i < fmng_->factoryTypeCSize(); i++) {
        for(s16 j = 0; j < emng_->unitTypeBSize(); j++) {
            if(!emng_->checkInstance_b())
                continue;

            auto* factory = fmng_->typeC(i);
            auto* Unit    = emng_->typeB(j);
            attack_f(fmng_, Unit, factory);
        }
    }
}
void TaskManager::attackToUnitTypeC(UnitManager* emng_, FactoryManager* fmng_)
{
    for(s16 i = 0; i < fmng_->factoryTypeASize(); i++) {
        for(s16 j = 0; j < emng_->unitTypeCSize(); j++) {
            if(!emng_->checkInstance_c())
                continue;

            auto* factory = fmng_->typeA(i);
            auto* Unit    = emng_->typeC(j);
            if(attack_f(fmng_, Unit, factory)) {
                break;
            }
        }
    }

    for(s16 i = 0; i < fmng_->factoryTypeBSize(); i++) {
        for(s16 j = 0; j < emng_->unitTypeCSize(); j++) {
            if(!emng_->checkInstance_c())
                continue;

            auto* factory = fmng_->typeB(i);
            auto* Unit    = emng_->typeC(j);
            if(attack_f(fmng_, Unit, factory)) {
                break;
            }
        }
    }

    for(s16 i = 0; i < fmng_->factoryTypeCSize(); i++) {
        for(s16 j = 0; j < emng_->unitTypeCSize(); j++) {
            if(!emng_->checkInstance_c())
                continue;

            auto* factory = fmng_->typeC(i);
            auto* Unit    = emng_->typeC(j);
            attack_f(fmng_, Unit, factory);
        }
    }
}
void TaskManager::attackToUnitTypeD(UnitManager* emng_, FactoryManager* fmng_)
{
    for(s16 i = 0; i < fmng_->factoryTypeASize(); i++) {
        for(s16 j = 0; j < emng_->unitTypeDSize(); j++) {
            if(!emng_->checkInstance_d())
                continue;

            auto* factory = fmng_->typeA(i);
            auto* Unit    = emng_->typeD(j);
            if(attack_f(fmng_, Unit, factory)) {
                break;
            }
        }
    }

    for(s16 i = 0; i < fmng_->factoryTypeBSize(); i++) {
        for(s16 j = 0; j < emng_->unitTypeDSize(); j++) {
            if(!emng_->checkInstance_d())
                continue;

            auto* factory = fmng_->typeB(i);
            auto* Unit    = emng_->typeD(j);
            if(attack_f(fmng_, Unit, factory)) {
                break;
            }
        }
    }

    for(s16 i = 0; i < fmng_->factoryTypeCSize(); i++) {
        for(s16 j = 0; j < emng_->unitTypeDSize(); j++) {
            if(!emng_->checkInstance_d())
                continue;

            auto* factory = fmng_->typeC(i);
            auto* Unit    = emng_->typeD(j);
            attack_f(fmng_, Unit, factory);
        }
    }
}

void TaskManager::checkHit()
{
    _hit_mouse_point = false;

    for(s16 i = 0; i < _fMng->factoryTypeASize(); i++) {
        if(hitMousePointToFactory(_fMng.get()->typeA(i))) {
            {
                _hit_mouse_point = true;
            }
        }
    }
    for(s16 i = 0; i < _fMng->factoryTypeBSize(); i++) {
        if(hitMousePointToFactory(_fMng.get()->typeB(i))) {
            {
                _hit_mouse_point = true;
            }
        }
    }
    for(s16 i = 0; i < _fMng->factoryTypeCSize(); i++) {
        if(hitMousePointToFactory(_fMng.get()->typeC(i))) {
            {
                _hit_mouse_point = true;
            }
        }
    }

    if(hitMousePointToMainFactory()) {
        _hit_mouse_point = true;
    }
}

//---------------------------------------------------------------------------
//! 敵の索敵範囲とマウスポインタの当たり判定
//---------------------------------------------------------------------------
bool TaskManager::hitMousePointToFactory(FactoryBase* type_)
{
    if(!_fMng || !_eMng)
        return false;

    auto* factory = type_;

    VECTOR v;
    // p0からp1を引いて円同士の距離を出す
    v = VSub(_eMng->GetMousePosition().Position, factory->hitPos());

    // 判定用
    f32 length = sqrtf(v.x * v.x + v.z * v.z);

    //  最初に出した距離と二つの半径を足したものを比べる
    if(length < (5 + factory->hitSize())) {
        //　p0からp1を引いて円同士の距離をのほうが小さければtrue
        return true;
    }

    return false;
}

//---------------------------------------------------------------------------
//! 敵の索敵範囲とマウスポインタの当たり判定
//---------------------------------------------------------------------------
bool TaskManager::hitMousePointToMainFactory()
{
    if(!_eMng || !_fMng || !_fMng->typeMain())
        return false;

    VECTOR v;
    // p0からp1を引いて円同士の距離を出す
    v = VSub(_eMng->GetMousePosition().Position, _fMng->hitPosMain());

    // 判定用
    f32 length = sqrtf(v.x * v.x + v.z * v.z);

    //  最初に出した距離と二つの半径を足したものを比べる
    if(length < (5 + _fMng->hitSizeMain())) {
        //　p0からp1を引いて円同士の距離をのほうが小さければtrue
        return true;
    }

    return false;
}

//---------------------------------------------------------------------------
//! ステージクリア処理
//---------------------------------------------------------------------------
void TaskManager::stageCrear()
{
    if(_is_clear)
        return;

    if(!_fMng->typeMain()) {
        //! クリアしたかどうか
        _is_clear = true;
    }
}

//---------------------------------------------------------------------------
//! ステージクリアテキストの描画
//---------------------------------------------------------------------------
void TaskManager::textRender()
{
    if(!_is_clear)
        return;

    textAnim(_alpha_back, _alpha_text);

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha_back);
    DrawBox(0, 0, WINDOW_W, WINDOW_H, BLACK, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    int x = WINDOW_W * 0.5f - 60;
    int y = WINDOW_H * 0.5f - 60;

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha_text);
    DrawString(x, y, "STAGE CLEAR", WHITE, true);

    blinkText(x + 5, y + 100, "PUSH SPACE");
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    if(_alpha_back >= 150) {
        return;
    }
    _alpha_back += 5;
}

//---------------------------------------------------------------------------
//! ステージ切り替えアニメーション
//---------------------------------------------------------------------------
void TaskManager::textAnim(int& alpha_back_, int& alpha_text_)
{
    if(CheckHitKey(KEY_INPUT_SPACE)) {
        _is_end = true;
    }
    if(alpha_back_ >= 255)
        return;

    if(_is_end) {
        alpha_back_ += 2;
        alpha_text_ -= 5;
    }

    if(alpha_back_ >= 255) {
        Scene::sceneJump(new SceneStageClear(_stage, _fMng.get()->checkMax(), _fMng.get()->checkNum(), _time));
    }
}
