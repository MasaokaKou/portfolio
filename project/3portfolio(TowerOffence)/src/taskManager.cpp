//---------------------------------------------------------------------------
//!	@file	taskMaanager.cpp
//!	@brief	�^�X�N�Ǘ�
//---------------------------------------------------------------------------

//===========================================================================
//!	�^�X�N�}�l�[�W���[
//===========================================================================

//---------------------------------------------------------------------------
//! �R���X�g���N�^
//---------------------------------------------------------------------------
TaskManager::TaskManager(s16 stage_)
{
    _stage = stage_;

    // ���j�b�g�}�l�[�W���[�̎��̐���
    if(_eMng == nullptr)
        _eMng = std::make_unique<UnitManager>();

    // �t�@�N�g���[�}�l�[�W���[�̎��̐���
    if(_fMng == nullptr)
        _fMng = std::make_unique<FactoryManager>(_stage);

    // UI�}�l�[�W���[�̎��Ԑ���
    if(_uiMng == nullptr)
        _uiMng = std::make_unique<uiManager>();

    // �G�̍��G�͈͂ƃ}�E�X�|�C���^�̓����蔻��
    _hit_mouse_point = false;

    // �e���ߓx
    _alpha_back = 0;
    _alpha_text = 255;

    // �N���A�������ǂ���
    _is_clear = false;

    // ���̃V�[���֐i�ރL�[�������ꂽ���ǂ���
    _is_end = false;

    // �o�ߎ���
    _time = 0;
}
//---------------------------------------------------------------------------
//! �f�X�g���N�^
//---------------------------------------------------------------------------
TaskManager::~TaskManager()
{
}

//---------------------------------------------------------------------------
//! ������
//---------------------------------------------------------------------------
bool TaskManager::initialize()
{
    //! UI�}�l�[�W���[�̏�����
    if(_uiMng)
        _uiMng->initialize();

    //! ���j�b�g�}�l�[�W���[�̏�����
    if(_eMng)
        _eMng->initialize(_stage);

    //! �t�@�N�g���[�}�l�[�W���[�̏�����
    if(_fMng)
        _fMng->initialize();

    return true;
}

//! �֐���
//!�@���G���Ăg�h�s�����G�ɍU��
void search_e(FactoryBase* factory, UnitBase* Unit, UnitManager* emng)
{
    //! unit_TYPE_A
    if(Unit->search(factory->pos(), factory->size(), factory->state())) {
        factory->setDamage();
        //! �t�@�N�g���[�̃_���[�W����
        if(Unit->isAtk()) {
            factory->damage(Unit->atk());
            Unit->setAtk(false);
        }

        //! �t�@�N�g���[��j�󂵂��烆�j�b�g��MOVE��
        emng->setMove(factory->hp());
    }
}

//!search_e�̊֐���
void search_e_func(FactoryBase* factory, UnitManager* emng)
{
    if(emng->checkInstance_a()) {
        for(s16 j = 0; j < emng->unitTypeASize(); j++) {
            auto* Unit = emng->typeA(j);

            search_e(factory, Unit, emng);
        }
    }

    // !���j�b�gTYPEB
    if(emng->checkInstance_b()) {
        for(s16 j = 0; j < emng->unitTypeBSize(); j++) {
            auto* Unit = emng->typeB(j);

            search_e(factory, Unit, emng);
        }
    }
    // !���j�b�gTYPEC
    if(emng->checkInstance_c()) {
        for(s16 j = 0; j < emng->unitTypeCSize(); j++) {
            auto* Unit = emng->typeC(j);

            search_e(factory, Unit, emng);
        }
    }
}

//! �֐���
//!�@���G���Ăg�h�s�����G�ɍU��
void search_f(UnitManager* emng, UnitBase* Unit, FactoryBase* factory)
{
    // factory->search(Unit->pos(), Unit->size());

    //! �t�@�N�g���[��j�󂵂��烆�j�b�g��MOVE��
    factory->setMove(Unit->hp());
}

//! search_f�̊֐���
void search_f_func(FactoryBase* factory, UnitManager* emng)
{
    for(s16 j = 0; j < emng->unitTypeASize(); j++) {
        if(!emng->checkInstance_a())
            continue;

        auto* Unit = emng->typeA(j);

        search_f(emng, Unit, factory);
        // break;
    }

    //! �t�@�N�g���[�̍��GTYPEB

    for(s16 j = 0; j < emng->unitTypeBSize(); j++) {
        if(!emng->checkInstance_b())
            continue;

        auto* Unit = emng->typeB(j);

        search_f(emng, Unit, factory);
    }

    //! �t�@�N�g���[�̍��GTYPEC

    for(s16 j = 0; j < emng->unitTypeCSize(); j++) {
        if(!emng->checkInstance_c())
            continue;

        auto* Unit = emng->typeC(j);
        search_f(emng, Unit, factory);
    }

    //! �t�@�N�g���[�̍��GTYPED

    for(s16 j = 0; j < emng->unitTypeDSize(); j++) {
        if(!emng->checkInstance_d())
            continue;

        auto* Unit = emng->typeD(j);
        search_f(emng, Unit, factory);
    }
}

//! �֐���
//!�@factory����̍U��
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
//! �X�V
//---------------------------------------------------------------------------
void TaskManager::update()
{
    //! UI�}�l�[�W���[�̍X�V
    //! unitManager�ɓn���������̂�����̂ōŏ�K�w
    if(_uiMng)
        _uiMng->update();

    //! ��ԏ�Ŗ{���n���Œ�
    if(_eMng) {
        _eMng->setMainTarget(VGet(60, 0, 60));
    }

    //! �N���A�������ǂ���
    if(_is_clear)
        return;

    //! �G�̍��G�͈͂ƃ}�E�X�|�C���^�̓����蔻��
    checkHit();

    //! �G�̍��G
    unitSearch();

    //! �t�@�N�g���[�̍��G
    factorySearch();

    //! �t�@�N�g���[���烆�j�b�g�ւ̍U��
    attackToUnit();

    //! ���j�b�g�}�l�[�W���[�̍X�V
    if(_eMng) {
        _eMng->update(_uiMng.get()->selNum(), _hit_mouse_point);
    }

    //! ���j�b�g�̏����UIMng�ɓn��
    if(_uiMng) {
        for(s16 i = 0; i < UNIT_MAX; i++) {
            _uiMng->setUnitLimit(_eMng.get()->unit_limit());
        }
    }

    //! �t�@�N�g���[�}�l�[�W���[�̍X�V
    if(_fMng) {
        _fMng->update();
        stageCrear();
    }
}

//---------------------------------------------------------------------------
//! �`��
//---------------------------------------------------------------------------
void TaskManager::render()
{
    //! UI�}�l�[�W���[�̕`��
    if(_uiMng)
        _uiMng.get()->render();

    //! �t�@�N�g���[�}�l�[�W���[�̕`��
    if(_fMng)
        _fMng.get()->render();

    //! ���j�b�g�}�l�[�W���[�̕`��
    if(_eMng)
        _eMng.get()->render();

    textRender();
}

//---------------------------------------------------------------------------
//! ���
//---------------------------------------------------------------------------
void TaskManager::finalize()
{
    //! UI�}�l�[�W���[�̉��
    if(_uiMng)
        _uiMng.get()->finalize();

    //! ���j�b�g�}�l�[�W���[�̉��
    if(_eMng) {
        _eMng->finalize();
        _eMng.release();
    }

    //! f�t�@�N�g���[�}�l�[�W���[�̉��
    if(_fMng) {
        _fMng->finalize();
        _fMng.release();
    }
}
//---------------------------------------------------------------------------
//! ���j�b�g�̍��G
//---------------------------------------------------------------------------
void TaskManager::unitSearch()
{
    //!(�t�@�N�g���[�}�l�[�W���[�̏��ŏ������ɂ����hp<=0���Ƃ��Ă���Ȃ�)

    //-----------------------------------------------------------------------
    //! factory_a
    //-----------------------------------------------------------------------
    // !���j�b�gTYPEA
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

    //! ���j�b�gTYPED
    //! �e���j�b�g�Ƃ̔���
    unitSearchTypeD(_eMng.get());
}
//---------------------------------------------------------------------------
//! ���j�b�gTYPED
//! �e���j�b�g�Ƃ̔���
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
//! �t�@�N�g���[�̍��G
//---------------------------------------------------------------------------
void TaskManager::factorySearch()
{
    //! mainFactory�̔���------------------------------------------------

    if(_fMng->checkInstance_main()) {
        auto* factory = _fMng->typeMain();
        search_e_func(factory, _eMng.get());
    }
    //-----------------------------------------------------------------------
    //! factory_a
    //-----------------------------------------------------------------------
    //! �t�@�N�g���[�̍��GTYPEA
    for(s16 i = 0; i < _fMng->factoryTypeASize(); i++) {
        auto* factory = _fMng->typeA(i);
        search_f_func(factory, _eMng.get());
    }

    //-----------------------------------------------------------------------
    //! factory_b
    //-----------------------------------------------------------------------
    //! �t�@�N�g���[�̍��GTYPEB
    for(s16 i = 0; i < _fMng->factoryTypeBSize(); i++) {
        auto* factory = _fMng->typeB(i);
        search_f_func(factory, _eMng.get());
    }
    //-----------------------------------------------------------------------
    //! factory_c
    //-----------------------------------------------------------------------
    //! �t�@�N�g���[�̍��GTYPEC
    for(s16 i = 0; i < _fMng->factoryTypeCSize(); i++) {
        auto* factory = _fMng->typeC(i);
        search_f_func(factory, _eMng.get());
    }
}

//---------------------------------------------------------------------------
//! �t�@�N�g���[���烆�j�b�g�ւ̍U��
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
//! �t�@�N�g���[���烆�j�b�g�ւ̍U���֐���
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
//! �G�̍��G�͈͂ƃ}�E�X�|�C���^�̓����蔻��
//---------------------------------------------------------------------------
bool TaskManager::hitMousePointToFactory(FactoryBase* type_)
{
    if(!_fMng || !_eMng)
        return false;

    auto* factory = type_;

    VECTOR v;
    // p0����p1�������ĉ~���m�̋������o��
    v = VSub(_eMng->GetMousePosition().Position, factory->hitPos());

    // ����p
    f32 length = sqrtf(v.x * v.x + v.z * v.z);

    //  �ŏ��ɏo���������Ɠ�̔��a�𑫂������̂��ׂ�
    if(length < (5 + factory->hitSize())) {
        //�@p0����p1�������ĉ~���m�̋������̂ق������������true
        return true;
    }

    return false;
}

//---------------------------------------------------------------------------
//! �G�̍��G�͈͂ƃ}�E�X�|�C���^�̓����蔻��
//---------------------------------------------------------------------------
bool TaskManager::hitMousePointToMainFactory()
{
    if(!_eMng || !_fMng || !_fMng->typeMain())
        return false;

    VECTOR v;
    // p0����p1�������ĉ~���m�̋������o��
    v = VSub(_eMng->GetMousePosition().Position, _fMng->hitPosMain());

    // ����p
    f32 length = sqrtf(v.x * v.x + v.z * v.z);

    //  �ŏ��ɏo���������Ɠ�̔��a�𑫂������̂��ׂ�
    if(length < (5 + _fMng->hitSizeMain())) {
        //�@p0����p1�������ĉ~���m�̋������̂ق������������true
        return true;
    }

    return false;
}

//---------------------------------------------------------------------------
//! �X�e�[�W�N���A����
//---------------------------------------------------------------------------
void TaskManager::stageCrear()
{
    if(_is_clear)
        return;

    if(!_fMng->typeMain()) {
        //! �N���A�������ǂ���
        _is_clear = true;
    }
}

//---------------------------------------------------------------------------
//! �X�e�[�W�N���A�e�L�X�g�̕`��
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
//! �X�e�[�W�؂�ւ��A�j���[�V����
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
