//---------------------------------------------------------------------------
//!	@file	unitManager.cpp
//!	@brief	UnitClass�̊Ǘ�
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! �R���X�g���N�^
//---------------------------------------------------------------------------
UnitManager::UnitManager()
{
    // ���ݔz�u���Ă��郆�j�b�g
    _size.TYPE_A = 0;
    _size.TYPE_B = 0;
    _size.TYPE_C = 0;
    _size.TYPE_D = 0;

    // ���I�����Ă��郆�j�b�g
    _selNum = 0;

    _count = 0;       // �z�u����Ԋu
    _span  = false;   // �z�u����Ԋu

    // �}�E�X�N���b�N�Ŕz�u
    GetMousePoint(&_mouse_x, &_mouse_y);

    // �}�E�X�̉�ʍ��W�� x, y �ɃZ�b�g
    ScreenPos.Position.x = (float)_mouse_x;
    ScreenPos.Position.z = (float)_mouse_y;

    // z �����ꂼ�� 0.0f �� 1.0f �ɂ���2�� ConvScreenPosToWorldPos ���Ă�
    ScreenPos.Position.z = 0.0f;
    Start3DPos           = ConvScreenPosToWorldPos(ScreenPos.Position);
    ScreenPos.Position.z = 1.0f;
    End3DPos             = ConvScreenPosToWorldPos(ScreenPos.Position);

    // �X�e�[�W���Ƃ̃��j�b�g�g�p���
    for(s16 i = 0; i < UNIT_MAX; i++)
        _unit_limit.push_back(i);

    // ���͏��
    _click           = GetMouseInput();
    _hit_mouse_point = false;

    // �G�̍��G�͈�
    _errorCleckUnit = false;
    _errorCleckUnit  = false;

    //! �Q�[���I�[�o�[�p�ϐ�
    _go_text_alpha = 0;
    _go_alpha      = 0;
}

//---------------------------------------------------------------------------
//! �f�X�g���N�^
//---------------------------------------------------------------------------
UnitManager::~UnitManager()
{
}

//---------------------------------------------------------------------------
//! ������
//---------------------------------------------------------------------------
bool UnitManager::initialize(s16 stage_)
{
    //! �X�e�[�W���Ƃ̃��j�b�g�̎g�p����ݒ�
    unitLimit(stage_);
    return true;
}
//---------------------------------------------------------------------------
//! �X�V
//---------------------------------------------------------------------------
void UnitManager::update(s16 selNum_, bool hit_mouse_point_)
{
    //! ���j�b�g�Z���N�^�[���烆�j�b�g�I��ԍ��擾
    _selNum = selNum_;

    _hit_mouse_point = hit_mouse_point_;

    //! �}�E�X�Ɖ�ʂ̓����蔻��
    setScreenPos();

    //! ���j�b�g�Z�b�b�g
    if(!_hit_mouse_point)
        setUnit();

    //! �X�|�[���J�E���^�[
    count();

    //! ���j�b�g�̍X�V
    for(auto& a : _units_a) {
        if(a)
            a->update();
    }
    for(auto& a : _units_b) {
        if(a)
            a->update();
    }
    for(auto& a : _units_c) {
        if(a)
            a->update();
    }
    for(auto& a : _units_d) {
        if(a)
            a->update();
    }

    deleteObj();
}
//---------------------------------------------------------------------------
//! �`��
//---------------------------------------------------------------------------
void UnitManager::render()
{
    //! ���j�b�g�̕`��

    //! ���j�b�g�̍X�V
    for(auto& a : _units_a) {
        if(a)
            a->render();
    }
    for(auto& a : _units_b) {
        if(a)
            a->render();
    }
    for(auto& a : _units_c) {
        if(a)
            a->render();
    }
    for(auto& a : _units_d) {
        if(a)
            a->render();
    }

    //! �}�E�X�̈���W�`��
    VECTOR pos = VGet(ScreenPos.Position.x, 0, ScreenPos.Position.z);

    if(_hit_mouse_point) {
        DrawSphere3D(pos, 2, 5, BLACK, BLACK, true);

        errorCleckUnit(pos);
    }
    else {
        DrawSphere3D(pos, 2, 5, GetColor(0, 255, 0), GetColor(0, 255, 0), true);
    }

    for(int i = 0; i < UNIT_MAX; i++) {
        if(_unit_limit.at(i) == 0 && _selNum == i) {
            errorCleckUnit(pos);
            DrawSphere3D(pos, 2, 5, BLACK, BLACK, true);
        }
    }

    gameOver();
}
//---------------------------------------------------------------------------
//! ���
//---------------------------------------------------------------------------
void UnitManager::finalize()
{
    //! ���j�b�g�̉��

    for(auto& a : _units_a) {
        if(a)
            a->finalize();
    }
    for(auto& a : _units_b) {
        if(a)
            a->finalize();
    }
    for(auto& a : _units_c) {
        if(a)
            a->finalize();
    }
    for(auto& a : _units_d) {
        if(a)
            a->finalize();
    }
}
//---------------------------------------------------------------------------
//! ���G(taskManager�ōX�V)
//---------------------------------------------------------------------------

bool UnitManager::search_d(VECTOR& fc_pos_, s16 f_size_, s16 i_)
{
    if(!_units_d.empty()) {
        if(_units_d[i_]->search(fc_pos_, f_size_, STATE::WAIT)) {
            return true;
        }
        else {
            return false;
        }
    }
    return false;
}

//!�@MOVE�̊ԏ�ɖ{���n�ֈړ�
void UnitManager::setMainTarget(VECTOR& main_fc_pos_)
{
    for(auto& a : _units_a) {
        if(a)
            a->setMainTarget(main_fc_pos_);
    }
    for(auto& a : _units_b) {
        if(a)
            a->setMainTarget(main_fc_pos_);
    }
    for(auto& a : _units_c) {
        if(a)
            a->setMainTarget(main_fc_pos_);
    }
    for(auto& a : _units_d) {
        if(a)
            a->setMainTarget(main_fc_pos_);
    }
}

//---------------------------------------------------------------------------
//! attack���I�������move�ɖ߂�
//---------------------------------------------------------------------------
void UnitManager::setMove(s16 hp_)
{
    for(auto& a : _units_a) {
        if(a)
            a->setMove(hp_);
    }
    for(auto& a : _units_b) {
        if(a)
            a->setMove(hp_);
    }
    for(auto& a : _units_c) {
        if(a)
            a->setMove(hp_);
    }
    for(auto& a : _units_d) {
        if(a)
            a->setMove(hp_);
    }
}

//---------------------------------------------------------------------------
//! �_���[�W����
//---------------------------------------------------------------------------
void UnitManager::damage_a(bool isAtk_, f32 atk_, s16 i_, TYPE type_)
{
    if(!_units_a[i_])
        return;

    if(type_ == TYPE::TYPE_D) {
        if(_units_a[i_]->hp() >= _units_a[i_]->HP()) {
            return;
        }
        else {
            _units_a[i_]->damage(isAtk_, atk_);
        }
    }
    else {
        _units_a[i_]->damage(isAtk_, atk_);
    }
}

void UnitManager::damage_b(bool isAtk_, f32 atk_, s16 i_, TYPE type_)
{
    if(!_units_b[i_])
        return;

    if(type_ == TYPE::TYPE_D) {
        if(_units_b[i_]->hp() >= _units_b[i_]->HP()) {
            return;
        }
        else {
            _units_b[i_]->damage(isAtk_, atk_);
        }
    }
    else {
        _units_b[i_]->damage(isAtk_, atk_);
    }
}
void UnitManager::damage_c(bool isAtk_, f32 atk_, s16 i_, TYPE type_)
{
    if(!_units_c[i_])
        return;

    if(type_ == TYPE::TYPE_D) {
        if(_units_c[i_]->hp() >= _units_c[i_]->HP()) {
            return;
        }
        else {
            _units_c[i_]->damage(isAtk_, atk_);
        }
    }
    else {
        _units_c[i_]->damage(isAtk_, atk_);
    }
}
void UnitManager::damage_d(bool isAtk_, f32 atk_, s16 i_)
{
    if(_units_d[i_])
        _units_d[i_]->damage(isAtk_, atk_);
}
//---------------------------------------------------------------------------
//! ���ŏ���
//---------------------------------------------------------------------------
void UnitManager::deleteObj_a()
{
    for(s16 i = 0; i < _units_a.size(); i++) {
        if(_units_a.at(i)->pos().y < 0)
            int a = 0;

        if(_units_a[i]) {
            if(_units_a[i]->isDead()) {
                _units_a[i].reset();
                _units_a[i] = nullptr;
                _units_a.erase(_units_a.begin() + i);
                _size.TYPE_A--;
            }
        }
    }
}

void UnitManager::deleteObj_b()
{
    for(s16 i = 0; i < _units_b.size(); i++) {
        if(_units_b[i]) {
            if(_units_b[i]->isDead()) {
                _units_b[i].reset();
                _units_b[i] = nullptr;
                _units_b.erase(_units_b.begin() + i);
                _size.TYPE_B--;
            }
        }
    }
}

void UnitManager::deleteObj_c()
{
    for(s16 i = 0; i < _units_c.size(); i++) {
        if(_units_c[i]) {
            if(_units_c[i]->isMolDead()) {
                _units_c[i].reset();
                _units_c[i] = nullptr;
                _units_c.erase(_units_c.begin() + i);
                _size.TYPE_C--;
            }
        }
    }
}
void UnitManager::deleteObj_d()
{
    for(s16 i = 0; i < _units_d.size(); i++) {
        if(_units_d[i]) {
            if(_units_d[i]->isMolDead()) {
                _units_d[i].reset();
                _units_d[i] = nullptr;
                _units_d.erase(_units_d.begin() + i);
                _size.TYPE_D--;
            }
        }
    }
}

//---------------------------------------------------------------------------
//! �}�E�X�Ɖ�ʂ̓����蔻��
//---------------------------------------------------------------------------
void UnitManager::setScreenPos()
{
    //// �}�E�X�̉�ʍ��W�� x, y �ɃZ�b�g
    GetMousePoint(&_mouse_x, &_mouse_y);
    ScreenPos.Position.x = (float)(_mouse_x);
    ScreenPos.Position.y = (float)(_mouse_y);

    // z �����ꂼ�� 0.0f �� 1.0f �ɂ���2�� ConvScreenPosToWorldPos ���Ă�
    ScreenPos.Position.z = 0.0f;
    Start3DPos           = ConvScreenPosToWorldPos(ScreenPos.Position);

    ScreenPos.Position.z = 1.0f;
    End3DPos             = ConvScreenPosToWorldPos(ScreenPos.Position);

    //! �t�B�[���h��̎O�p�`�ƃ}�E�X�̃��C�̓����蔻��
    VECTOR a = VGet(0, 0, 200);
    VECTOR b = VGet(-200, 0, -50);
    VECTOR c = VGet(200, 0, -50);

    ScreenPos = HitCheck_Line_Triangle(Start3DPos, End3DPos, a, b, c);
}
//---------------------------------------------------------------------------
//! �Q�[���t�B�[���h���O����
//---------------------------------------------------------------------------
bool UnitManager::isOut()
{
    VECTOR a = VGet(80, 0, 80);
    VECTOR b = VGet(-80, 0, -50);
    VECTOR c = VGet(80, 0, -50);

    VECTOR d = VGet(-80, 0, 80);
    VECTOR e = VGet(80, 0, 80);
    VECTOR f = VGet(-80, 0, -50);

    if(ScreenPos.Position.x > d.x && e.x > ScreenPos.Position.x &&
       ScreenPos.Position.z < d.z && c.z < ScreenPos.Position.z) {
        return true;
    }

    return false;
}

//---------------------------------------------------------------------------
//! �}�E�X�Ŕz�u
//---------------------------------------------------------------------------
void UnitManager::setUnit()
{
    //! �}�E�X�N���b�N�Ŕz�u

    if(GetMouseInput() & MOUSE_INPUT_LEFT != 0 && _span == false) {
        if(_mouse_y > WINDOW_H * 0.8f)
            return;

        if(!isOut())
            return;

        switch(_selNum) {
            case 0:

                //! ���j�b�g�̏��
                if(_unit_limit.at(0) <= 0)
                    break;

                _units_a.push_back(std::make_unique<UnitTypeA>());
                _unit_limit.at(0)--;

                for(int i = _size.TYPE_A; i < _units_a.size();) {
                    VECTOR a = VGet(ScreenPos.Position.x, 5, ScreenPos.Position.z);

                    _units_a[i]->setPos(a);

                    _units_a[i]->initialize();

                    i++;

                    _size.TYPE_A = i;
                    _span        = true;

                    break;
                }
                break;

            case 1:
                //! ���j�b�g�̏��
                if(_unit_limit.at(1) <= 0)
                    break;

                _units_b.push_back(std::make_unique<UnitTypeB>());
                _unit_limit.at(1)--;

                for(int i = _size.TYPE_B; i < _units_b.size();) {
                    _units_b[i]->initialize();
                    VECTOR a = VGet(ScreenPos.Position.x, 5, ScreenPos.Position.z);
                    _units_b[i]->setPos(a);

                    i++;
                    _size.TYPE_B = i;
                    _span        = true;
                    break;
                }

                break;

            case 2:
                //! ���j�b�g�̏��
                if(_unit_limit.at(2) <= 0)
                    break;
                _units_c.push_back(std::make_unique<UnitTypeC>());
                _unit_limit.at(2)--;
                for(int i = _size.TYPE_C; i < _units_c.size();) {
                    _units_c[i] = std::make_unique<UnitTypeC>();
                    _units_c[i]->initialize();
                    VECTOR a = VGet(ScreenPos.Position.x, 5, ScreenPos.Position.z);
                    _units_c[i]->setPos(a);

                    i++;
                    _size.TYPE_C = i;
                    _span        = true;
                    break;
                }

                break;
            case 3:

                //! ���j�b�g�̏��
                if(_unit_limit.at(3) <= 0)
                    break;
                _units_d.push_back(std::make_unique<UnitTypeD>());
                _unit_limit.at(3)--;
                for(int i = _size.TYPE_D; i < _units_d.size();) {
                    _units_d[i] = std::make_unique<UnitTypeD>();
                    _units_d[i]->initialize();
                    VECTOR a = VGet(ScreenPos.Position.x, 5, ScreenPos.Position.z);
                    _units_d[i]->setPos(a);

                    i++;
                    _size.TYPE_D = i;
                    _span        = true;
                    break;
                }

                break;
            default:

                break;
        }
    }
}

//---------------------------------------------------------------------------
//! �X�|�[���J�E���^�[
//---------------------------------------------------------------------------
void UnitManager::count()
{
    if(_span) {
        _count++;
        if(_count >= 10) {
            _span = false;
        }

        if(!_span) {
            _count = 0;
        }
    }
}
//---------------------------------------------------------------------------
//! �X�e�[�W���Ƃ̃��j�b�g�̎g�p����ݒ�
//---------------------------------------------------------------------------
void UnitManager::unitLimit(s16 stage_)
{
    switch(stage_) {
        case 0:
            _unit_limit.at(0) = 10;
            _unit_limit.at(1) = 0;
            _unit_limit.at(2) = 0;
            _unit_limit.at(3) = 0;

            break;
        case 1:
            _unit_limit.at(0) = 10;
            _unit_limit.at(1) = 5;
            _unit_limit.at(2) = 0;
            _unit_limit.at(3) = 0;

            break;
        case 2:
            _unit_limit.at(0) = 10;
            _unit_limit.at(1) = 5;
            _unit_limit.at(2) = 5;
            _unit_limit.at(3) = 0;

            break;
        case 3:
            _unit_limit.at(0) = 20;
            _unit_limit.at(1) = 10;
            _unit_limit.at(2) = 5;
            _unit_limit.at(3) = 1;

            break;
        case 4:
            _unit_limit.at(0) = 20;
            _unit_limit.at(1) = 10;
            _unit_limit.at(2) = 15;
            _unit_limit.at(3) = 2;

            break;
    }
}

//---------------------------------------------------------------------------
//ScreenPos��factory�̍��G����
//---------------------------------------------------------------------------
bool UnitManager::hit_ScreenPos_to_factory(VECTOR pos_, u32 r_)
{
    VECTOR v;
    v = VSub(ScreenPos.Position, pos_);

    // ����p
    f32 length = sqrtf(v.x * v.x + v.z * v.z);

    //  �ŏ��ɏo���������Ɠ�̔��a�𑫂������̂��ׂ�
    if(length < (5 + r_)) {
        //�@p0����p1�������ĉ~���m�̋������̂ق������������true
        return true;
    }

    return false;
}

//---------------------------------------------------------------------------
//! ���̂̃T�C�Y
//---------------------------------------------------------------------------
s16 UnitManager::unitTypeASize()
{
    if(!_units_a.empty()) {
        return _units_a.size();
    }
}
s16 UnitManager::unitTypeBSize()
{
    if(!_units_b.empty()) {
        return _units_b.size();
    }
}
s16 UnitManager::unitTypeCSize()
{
    if(!_units_c.empty()) {
        return _units_c.size();
    }
}
s16 UnitManager::unitTypeDSize()
{
    if(!_units_d.empty()) {
        return _units_d.size();
    }
}

std::vector<s16> UnitManager::unit_limit()
{
    return _unit_limit;
}

//---------------------------------------------------------------------------
//! �G�̍��G�͈͂ō��N���b�N
//---------------------------------------------------------------------------
void UnitManager::errorCleckEnemy(VECTOR pos_)
{
    if(GetMouseInput() & MOUSE_INPUT_LEFT != 0) {
        if(!_errorCleckUnit)
            _errorCleckUnit = true;
    }

    if(!_errorCleckUnit)
        return;

    //! �X�N���[�����W�ɕϊ�
    pos_ = ConvWorldPosToScreenPos(pos_);

    static int count = 30;

    count--;
    if(count > 0) {
        pos_.y += 10;
    }
    else {
        _errorCleckUnit = false;
        count            = 30;
    }

    DrawString(pos_.x + 10, pos_.y - 45, "�G�ɋ߂����܂�", WHITE, true);
}
//---------------------------------------------------------------------------
//! ���j�b�g�̎c���Ȃ���Ԃō��N���b�N
//---------------------------------------------------------------------------
void UnitManager::errorCleckUnit(VECTOR pos_)
{
    if(GetMouseInput() & MOUSE_INPUT_LEFT != 0) {
        if(!_errorCleckUnit)
            _errorCleckUnit = true;
    }

    if(!_errorCleckUnit)
        return;

    //! �X�N���[�����W�ɕϊ�
    pos_ = ConvWorldPosToScreenPos(pos_);

    static int count = 30;

    count--;
    if(count > 0) {
        pos_.y += 10;
    }
    else {
        _errorCleckUnit = false;
        count           = 30;
    }

    DrawString(pos_.x + 10, pos_.y - 45, "���j�b�g���g���؂�܂���", WHITE, true);
}

//---------------------------------------------------------------------------
//! �t�B�[���h�ɂ��郆�j�b�g�Ǝ莝���̃��j�b�g���O�ɂȂ�����Q�[���I�[�o�[
//---------------------------------------------------------------------------
void UnitManager::gameOver()
{
    for(int i = 0; i < UNIT_MAX; i++)
        if(_unit_limit[i] != 0)
            return;

    for(auto& a : _units_a) {
        if(a)
            return;
    }
    for(auto& a : _units_b) {
        if(a)
            return;
    }
    for(auto& a : _units_c) {
        if(a)
            return;
    }
    for(auto& a : _units_d) {
        if(a)
            return;
    }

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _go_alpha);
    DrawBox(0, 0, WINDOW_W, WINDOW_H, BLACK, TRUE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _go_text_alpha);
    DrawString(WINDOW_W * 0.5f - 50, WINDOW_H * 0.5f - 50, "GAME OVER", WHITE, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    _go_alpha += 2;

    if(_go_alpha >= 255) {
        _go_text_alpha += 3;
    }
    if(_go_text_alpha >= 255) {
        blinkText(WINDOW_W * 0.5f - 55, WINDOW_H * 0.5f + 50, "PUSH SPACE");
    }

    if(CheckHitKey(KEY_INPUT_SPACE)) {
        Scene::sceneJump(new StageSelector());
    }
}
//---------------------------------------------------------------------------
//! ���ŏ����܂Ƃ߂�
//---------------------------------------------------------------------------
void UnitManager::deleteObj()
{
    deleteObj_a();
    deleteObj_b();
    deleteObj_c();
    deleteObj_d();
}
//---------------------------------------------------------------------------
//! TYPEB�̍U���A�j���[�V����
//---------------------------------------------------------------------------
void UnitManager::atkMoveTypeB(VECTOR fac_pos_, f32 fac_size_, STATE state_)
{
    for(auto& a : _units_b) {
        if(a)
            a.get()->atkMove(fac_pos_, fac_size_, state_);
    }
}

//---------------------------------------------------------------------------
//! �Q�b�^�[(unit_TYPE_A)
//---------------------------------------------------------------------------
VECTOR UnitManager::pos_a(s16 i_) const
{
    if(!_units_a.empty())
        return _units_a[i_].get()->pos();
}

s16 UnitManager::size_a(s16 i_) const
{
    if(!_units_a.empty())
        return _units_a[i_].get()->size();
}

bool UnitManager::checkInstance_a()
{
    if(!_units_a.empty()) {
        return true;
    }
    return false;
}

//---------------------------------------------------------------------------
//! �Q�b�^�[(unit_TYPE_B)
//---------------------------------------------------------------------------
VECTOR UnitManager::pos_b(s16 i_) const
{
    if(!_units_b.empty())
        return _units_b[i_].get()->pos();
}

s16 UnitManager::size_b(s16 i_) const
{
    if(!_units_b.empty())
        return _units_b[i_].get()->size();
}

bool UnitManager::checkInstance_b()
{
    if(!_units_b.empty()) {
        return true;
    }
    return false;
}

//---------------------------------------------------------------------------
//! �Q�b�^�[(unit_TYPE_C)
//---------------------------------------------------------------------------
VECTOR UnitManager::pos_c(s16 i_) const
{
    if(!_units_c.empty())
        return _units_c[i_].get()->pos();
}

s16 UnitManager::size_c(s16 i_) const
{
    if(!_units_c.empty())
        return _units_c[i_].get()->size();
}

bool UnitManager::checkInstance_c()
{
    if(!_units_c.empty()) {
        return true;
    }
    return false;
}

//---------------------------------------------------------------------------
//! �Q�b�^�[(unit_TYPE_D)
//---------------------------------------------------------------------------

VECTOR UnitManager::pos_d(s16 i_) const
{
    if(!_units_d.empty())
        return _units_d[i_].get()->pos();
}

s16 UnitManager::size_d(s16 i_) const
{
    if(!_units_d.empty())
        return _units_d[i_].get()->size();
}

bool UnitManager::isAtk_d(s16 i_) const
{
    if(!_units_d.empty())
        return _units_d[i_].get()->isAtk();
}

f32 UnitManager::atk_d(s16 i_) const
{
    if(!_units_d.empty())
        return _units_d[i_].get()->atk();
}

bool UnitManager::checkInstance_d()
{
    if(!_units_d.empty()) {
        return true;
    }
    return false;
}

TYPE UnitManager::TYPE_D(s16 i_) const
{
    if(!_units_d.empty()) {
        return _units_d[i_].get()->type();
    }
}
