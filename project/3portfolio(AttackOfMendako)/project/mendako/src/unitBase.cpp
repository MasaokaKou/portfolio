//---------------------------------------------------------------------------
//!	@file	unitBase.cpp
//!	@brief	unitBase����
//---------------------------------------------------------------------------

//===========================================================================
//! ���j�b�g
//===========================================================================

//---------------------------------------------------------------------------
//! �R���X�g���N�^
//---------------------------------------------------------------------------
UnitBase ::UnitBase()
{
    _pos = VGet(0, 0, 0);

    _type = TYPE::TYPE_A;

    _oldPos = VGet(0, 0, 0);
    _dir    = TO_RADIAN(180.0f) * 0;
    _size   = 0.00f;

    par._hp     = 1;      // �ϋv�l
    par._atk    = 1;      // �U����
    par._def    = 0;      // �ϋv��
    par._movSpd = 0.2f;   // �i�R���x
    par._atkSpd = 30;     // �U�����x(_atkSpd �t���[���Ɉ�x)

    _isAtk    = false;   // �U�������ǂ���
    _atkCount = 0;       // �U���p�̃J�E���g

    _state = STATE::WAIT;   // ���݂̏��

    _targetPos = VGet(0, 0, 0);   // �������{��

    // �����蔻��p�̕ϐ�(���G)
    _hit._hcPos   = VGet(_pos.x, _pos.y, _pos.z);   // ���݈ʒu
    _hit._hcScale = 1;                              // �T�C�Y
    _hit._hcSpace = 1;                              // �Ԋu

    // �����蔻��p�̕ϐ�(�U��)
    _hitAtk._hcPos   = VGet(_pos.x, _pos.y, _pos.z);   // ���݈ʒu
    _hitAtk._hcScale = 1;                              // �T�C�Y
    _hitAtk._hcSpace = 130;                            // �Ԋu

    // ���f��
    _model = std::make_unique<Model>();   // ���ԍ쐬

    // �s��
    _matRot = MGetIdent();                            // �P�ʍs����擾
    _matRot = MGetScale(VGet(_size, _size, _size));   // �T�C�Y�w��

    _isDamage = false;   // �U������Ă��邩�ǂ���

    // �o�ꃂ�[�V�����p�ϐ�
    _startUpTimer = 30;
    _startUpTimer = 30;

    // ���f���̕s�����x
    _alpha = 1.0f;

    // ���Ń��[�V�������I����Ă��邩�ǂ���
    _is_dead = false;

    // HpBar�̎���
    _hpBar = std::make_unique<HpBar>();

    //�ŏ��̍��G���I��莟����G��؂�
    _is_search = true;
}

//---------------------------------------------------------------------------
//! �f�X�g���N�^
//---------------------------------------------------------------------------
UnitBase ::~UnitBase()
{
}

//---------------------------------------------------------------------------
//! ������
//---------------------------------------------------------------------------
bool UnitBase::initialize(const char* modelName_, const char* materialName_)
{
    SetUseTransColor(FALSE);

    //! ���f���̓ǂݍ���
    _model.get()->load(modelName_);
    //! ���f���̏������W�ݒ�(�}�g���b�N�X�ݒ�)
    //  MV1SetMatrix(_model.get()->handle(), _matRot);
    _graphHandle = LoadGraph(materialName_);

    //! ���f���Ƀe�N�X�`���𒣂�t��
    MV1SetTextureGraphHandle(_model.get()->handle(), 0, _graphHandle, false);
    //! HpBar
    if(_hpBar) {
        _hpBar.get()->initialize(par._hp);
    }

    _matRot.m[3][0] = _pos.x;
    _matRot.m[3][1] = _pos.y;
    _matRot.m[3][2] = _pos.z;

    return true;
}

//---------------------------------------------------------------------------
//! �X�V
//---------------------------------------------------------------------------
void UnitBase::update()
{
    //! ���Ń��[�V����
    checkMotion();

    //! HP�̏���ȏ�񕜂��Ȃ��悤��
    setMaxHitPoint();

    //! �T�C�Y�ύX
    setSize();

    //! �X�e�[�^�X���ƂɍX�V
    stateUpdate();

    //! HpBar�̍X�V
    hpbarUpdate();

    //! c.d�ȊO�Ȃ�5�ɌŒ�
    if(_type != TYPE::TYPE_C && _type != TYPE::TYPE_D)
        _matRot.m[3][1] = 5;

    //! �}�g���b�N�X�ݒ�
    MV1SetMatrix(_model.get()->handle(), _matRot);
}
//---------------------------------------------------------------------------
//! �`��
//---------------------------------------------------------------------------
void UnitBase::render()
{
    _model.get()->draw();

    //! HpBar
    if(_hpBar)
        _hpBar.get()->render();

    //! �����蔻��p�̋�
    //DrawSphere3D(_hit._hcPos, _hit._hcScale, 5, WHITE, WHITE, false);
    //DrawSphere3D(_hitAtk._hcPos, _hitAtk._hcScale, 5, RED, RED, false);
}

//---------------------------------------------------------------------------
//! ���
//---------------------------------------------------------------------------
void UnitBase::finalize()
{
    //! HpBar
    if(_hpBar)
        _hpBar.get()->finalize();
}

//---------------------------------------------------------------------------
//! �����_�R�̓o�ꃂ�[�V����
//---------------------------------------------------------------------------
void UnitBase::startUp()
{
    //! unit����v���C���[�̕����x�N�g���쐬
    VECTOR dir;

    //! unit�̍��W����h�q�{�݂̍��W������
    dir = VSub(_targetPos, _pos);
    dir = VNorm(dir);

    // �E�����Ȃ̂�90.0��
    float side_rot = _dir + TO_RADIAN(180.0f);

    _side.x += cosf(side_rot);
    _side.z -= sinf(side_rot);

    _side = VNorm(_side);

    //! �Q�̃x�N�g���̓��ς��擾
    //! (unit����v���C���[�̕����x�N�g���쐬 , unit�̉E�����̃x�N�g�����쐬)
    float side_dot = VDot(_side, dir);

    //! �}�g���b�N�X���g�������f���̉�]
    _matRot = MGetRotY(_dir);
    //! MGetRotY�łȂ���scale��1�ɂȂ�̂ŋ����ύX
    _matRot = MScale(_matRot, _size);

    //! �}�g���b�N�X�̍��W�Ɍ��݈ʒu������
    setMat();

    //! �J�n��b�̊ԉ�]����
    startRotation(side_dot);

    _startUpTimer--;
}
//---------------------------------------------------------------------------
//! �}�g���b�N�X�̂��Ă͂�
//---------------------------------------------------------------------------
void UnitBase::setMat()
{
    _matRot.m[3][0] = _pos.x;
    _matRot.m[3][1] = _pos.y;
    _matRot.m[3][2] = _pos.z;
}

//---------------------------------------------------------------------------
//! �J�n��b�̊ԉ�]����
//---------------------------------------------------------------------------
void UnitBase::startRotation(float side_dot)
{
    //! �J�n��b�̊ԉ�]����
    if(_startUpTimer <= 0) {
        _state = STATE::MOVE;

        // ���ς̒l���v���X���}�C�i�X�ŉ�]���������߂�
        if(side_dot > 0.0f) {
            _dir += TO_RADIAN(2.0f);
        }
        // ���ς̒l���}�C�i�X�̎���
        if(side_dot < 0.0f) {
            _dir -= TO_RADIAN(2.0f);
        }
    }
    else {
        _dir += TO_RADIAN(20.0f);
    }
}

//---------------------------------------------------------------------------
//! �X�e�[�^�X���ƂɍX�V
//---------------------------------------------------------------------------
void UnitBase::stateUpdate()
{
    switch(_state) {
        case STATE::WAIT:

            startUp();

            //! �����蔻��̓���
            movHit();

            break;

        case STATE::MOVE:

            //! �ړ�
            move(_targetPos);
            //! �����蔻��̓���
            movHit();

            break;
        case STATE::ATTACK:

            attack();
            movHit();

            break;

        case STATE::DEATH:

            deadMotion();
            break;
        default:
            break;
    }
}

//---------------------------------------------------------------------------
//! HpBar�̍X�V
//---------------------------------------------------------------------------
void UnitBase::hpbarUpdate()
{
    if(_hpBar) {
        _hpBar.get()->prPos(_pos);

        _hpBar.get()->setHp(par._hp);

        _hpBar.get()->type(_type);

        _hpBar.get()->update();

        _hpBar.get()->setPos(VGet(-25, -30, 0));
    }
}

//---------------------------------------------------------------------------
//! ���G(taskManager�ōX�V)  (isDamage ��factory�ɓn��)
//---------------------------------------------------------------------------
bool UnitBase::search(VECTOR& fc_pos, f32 f_size, STATE _f_state)
{
    //! �G������ł�����X���[
    if(_f_state == STATE::DEATH) {
        return false;
    }

    //! �o�ꃂ�[�V��������retrun false
    if(_state == STATE::WAIT)
        return false;

    if(hit(_hit._hcPos, _hit._hcScale, fc_pos, f_size)) {
        //! ���G�͈͂ɖh�q�{�݂�����΂�����
        if(_is_search) {
            _fc_pos = fc_pos;
            if(_type != TYPE::TYPE_D)
                _is_search = false;
        }

        //! �U���p�����蔻��ɓ����Ă���U���J�n

        if(hit(_hitAtk._hcPos, _hitAtk._hcScale, fc_pos, f_size)) {
            _state = STATE::ATTACK;   //! ���݂̏��

            return true;
        }
        else {
            if(_type == TYPE::TYPE_D) {
                _state = STATE::MOVE;
                _isAtk = false;
            }
        }
    }

    if(!_is_search) {
        _targetPos = _fc_pos;
    }

    return false;
}

//---------------------------------------------------------------------------
//!�@MOVE�̊ԏ�ɖ{���n�ֈړ�
//---------------------------------------------------------------------------
void UnitBase::setMainTarget(VECTOR& main_fc_pos)
{
    _targetPos = main_fc_pos;
}

//---------------------------------------------------------------------------
//! �ړ�
//!���G���Ĕ͈͓��Ɏ{�݂��������炻�̍��W��ړI�n�ɂ��Ĉړ�
//---------------------------------------------------------------------------
void UnitBase::move(VECTOR& fc_pos)
{
    //! unit����v���C���[�̕����x�N�g���쐬
    VECTOR dir;

    //! unit�̍��W����h�q�{�݂̍��W������
    dir = VSub(fc_pos, _pos);

    // ���K��
    dir = VNorm(dir);

    //! ���K�������x�N�g���ɑ��x��������
    dir = VScale(dir, par._movSpd);

    //! unit�̍��W�ɐ��K�����������x�N�g��������
    //! ���K�������x�N�g���ɑ��x��������

    _pos = VAdd(_pos, dir);

    //! �����]��
    direction(fc_pos);

    //! ��t���[���O�̍��W
    _oldPos = VGet(_pos.x, _pos.y, _pos.z);
}

//---------------------------------------------------------------------------
//! �����]��
//---------------------------------------------------------------------------
void UnitBase::direction(VECTOR& fc_pos)
{
    //! unit����v���C���[�̕����x�N�g���쐬
    VECTOR dir;

    //! unit�̍��W����h�q�{�݂̍��W������
    dir = VSub(fc_pos, _pos);

    // ���K��
    dir = VNorm(dir);

    // unit�̉E�����̃x�N�g�����쐬
    // �E�����Ȃ̂�90.0��
    float side_rot = _dir + TO_RADIAN(180.0f);

    _side.x += cosf(side_rot);
    _side.z -= sinf(side_rot);

    //! ���K��
    _side = VNorm(_side);

    //! �Q�̃x�N�g���̓��ς��擾
    //! (unit����v���C���[�̕����x�N�g���쐬 , unit�̉E�����̃x�N�g�����쐬)
    float side_dot = VDot(_side, dir);

    // ���ς̒l���݂ĉ�]���������߂�
    if(side_dot > 0.0f) {
        _dir += TO_RADIAN(2.0f);
    }
    if(side_dot < 0.0f) {
        _dir -= TO_RADIAN(2.0f);
    }

    //! �}�g���b�N�X���g�������f���̉�]
    _matRot = MGetRotY(_dir);
    //! MGetRotY�łȂ���scale��1�ɂȂ�̂ŋ����ύX
    _matRot = MScale(_matRot, _size);

    //! �}�g���b�N�X�̍��W�Ɍ��݈ʒu������
    _matRot.m[3][0] = _pos.x;
    _matRot.m[3][1] = _pos.y;
    _matRot.m[3][2] = _pos.z;
}

//---------------------------------------------------------------------------
//! �����蔻��̓���
//---------------------------------------------------------------------------
void UnitBase::movHit()
{
    //! �}�g���b�N�X��Z���
    VECTOR vec     = VGet(_matRot.m[2][0], _matRot.m[2][1], _matRot.m[2][2]);
    VECTOR vec_atk = VGet(_matRot.m[2][0], _matRot.m[2][1], _matRot.m[2][2]);

    //! ���K��
    vec = VNorm(vec);

    //!  �Ԋu��������
    mulVec(vec, _hit._hcSpace);
    mulVec(vec_atk, _hitAtk._hcSpace);

    //!  Z�����Ɣ��΂ɂȂ�̂Ŕ��]������
    mulVec(vec, -1.0f);
    mulVec(vec_atk, -1.0f);

    //! unit�̃|�W�V�����ƃ}�g���b�N�X��Z���𑫂�
    _hit._hcPos    = VAdd(_pos, vec);
    _hitAtk._hcPos = VAdd(_pos, vec_atk);
}

//---------------------------------------------------------------------------
//! ��葬�x�Ńt�@�N�g���[�Ƀ_���[�W��^����
//---------------------------------------------------------------------------
void UnitBase::attack()
{
    if(_atkCount % par._atkSpd == 0) {
        _isAtk = true;
    }
    else {
        _isAtk = false;
    }

    _atkCount++;
    if(_atkCount >= par._atkSpd)
        _atkCount = 0;
}

//---------------------------------------------------------------------------
//! attack���I�������move�ɖ߂�
//---------------------------------------------------------------------------
void UnitBase::setMove(s16 hp)
{
    if(hp <= 0) {
        _state = STATE::MOVE;
        _isAtk = false;

        isSearch();
    }
}

//---------------------------------------------------------------------------
//! �_���[�W����
//---------------------------------------------------------------------------
void UnitBase::damage(bool isAtk, f32 atk)
{
    if(isAtk && _isDamage) {
        par._hp -= atk;
        isAtk = false;
    }
}

//---------------------------------------------------------------------------
//! ���S���̃��[�V����
//---------------------------------------------------------------------------
void UnitBase::checkMotion()
{
    if(par._hp <= 0) {
        _state = STATE::DEATH;
    }
}

void UnitBase::deadMotion()
{
    //! matrix��Y��������������
    if(_matRot.m[1][1] >= 0.00f) {
        _matRot.m[1][1] -= 0.005;
    }
    else {
        _alpha -= 0.02f;
    }

    if(_alpha <= 0.0f) {
        _is_dead = true;
    }

    //! ���f���̕s�����x��ς���
    MV1SetMeshOpacityRate(_model.get()->handle(), 0, _alpha);
}
//---------------------------------------------------------------------------
//! HP�̏���ȏ�񕜂��Ȃ��悤��
//---------------------------------------------------------------------------
void UnitBase::setMaxHitPoint()
{
    if(par._hp > _HP) {
        par._hp = _HP;
    }
}
//---------------------------------------------------------------------------
//! �T�C�Y�ύX
//---------------------------------------------------------------------------
void UnitBase::setSize()
{
    if(_size <= 0.04f) {
        _size += 0.002;
    }
}

//!---------------------------
//! �Q�b�^�[
//!---------------------------

//---------------------------------------------------------------------------
//! ���j�b�g�̎��
//---------------------------------------------------------------------------
TYPE UnitBase::type()
{
    return _type;
}
