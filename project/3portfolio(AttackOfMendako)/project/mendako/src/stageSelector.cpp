//---------------------------------------------------------------------------
//!	@file	stageSelector.cpp
//!	@brief	�^�X�N�Ǘ�
//---------------------------------------------------------------------------
//#include "stageSelector.h"

//---------------------------------------------------------------------------
//! �R���X�g���N�^
//---------------------------------------------------------------------------
StageSelector::StageSelector()
{
    for(s16 i = 0; i < STAGE_MAX; i++) {
        _cube_x[i] = 0 + (i * 135);
        _cube_y[i] = 200;

        _flag[i] = false;

        // _is_clear[i] = false;
    }
    _stage = 0;
    //! �����Ɖ���
    high = wide = 100;

    //! �I����̃A�j���[�V�������n�܂������ǂ���
    _isAnim    = false;
    _isAnimEnd = false;

    //!�@���ߓx
    _alpha[0] = 255;
    _alpha[1] = 0;

    //! �`���[�g���A���@�\�I��
    _tutorial_x     = 270;
    _tutorial_y     = 350;
    _is_tutorial    = true;
    _tutorial_timer = 30;
    _timer          = false;

    //! �}�E�X�̍��W
    GetMousePoint(&_mouse_x, &_mouse_y);

    //! ���̉摜
    _lock_graph = 0;
    _lock_x     = 50;
    _lock_y     = 250;

    for(int i = 0; i < STAGE_MAX; i++) {
        if(!_is_stage_lock[i])
            _lock_stage_alpha[i] = 255;
    }
    _is_stage_lock[0] = true;

    _back_alpha  = 255;
    _check       = false;
    _reset_timer = 0;
}

//---------------------------------------------------------------------------
//! �f�X�g���N�^
//---------------------------------------------------------------------------

StageSelector::~StageSelector()
{
}

//---------------------------------------------------------------------------
//! ������
//---------------------------------------------------------------------------
bool StageSelector::initialize()
{
    _lock_graph = LoadGraph("data/lock.png");
    _back_graph = LoadGraph("data/stage_select_back.png");

    return false;
}

//---------------------------------------------------------------------------
//! �X�V
//---------------------------------------------------------------------------
void StageSelector::update()
{
    _reset_timer++;

    blackOut();

    //! �X�e�[�W�A�����b�N
    unlock();
    unlockAnim();

    //! �}�E�X�̍��W
    GetMousePoint(&_mouse_x, &_mouse_y);
    for(s16 i = 0; i < STAGE_MAX; i++) {
        if(_cube_x[i] < _mouse_x && _cube_x[i] + wide > _mouse_x && _cube_y[i] < _mouse_y && _cube_y[i] + high > _mouse_y) {
            _flag[i] = true;
            if(GetMouseInput() && _is_stage_lock[i]) {
                if(_isAnim)
                    return;
                _stage  = i;
                _isAnim = true;
            }
        }
        else {
            _flag[i] = false;
        }
    }

    //! �`���[�g���A��
    if(_tutorial_x < _mouse_x && _tutorial_x + wide > _mouse_x && _tutorial_y < _mouse_y && _tutorial_y + high > _mouse_y) {
        if(GetMouseInput()) {
            if(_timer)
                return;
            if(!_is_tutorial) {
                _is_tutorial = true;
                _timer       = true;
            }
            else {
                _is_tutorial = false;
                _timer       = true;
            }
        }
    }

    if(_timer) {
        _tutorial_timer--;
        if(_tutorial_timer <= 0) {
            _tutorial_timer = 30;
            _timer          = false;
        }
    }

    decAlpha();
    addAlpha();

    gameReset();

    if(CheckHitKey(KEY_INPUT_1))
        _clearStage[0] = 1;

    if(CheckHitKey(KEY_INPUT_2))
        _clearStage[1] = 1;
    if(CheckHitKey(KEY_INPUT_3))
        _clearStage[2] = 1;
    if(CheckHitKey(KEY_INPUT_4))
        _clearStage[3] = 1;
}

//---------------------------------------------------------------------------
//! �`��
//---------------------------------------------------------------------------
void StageSelector::render()
{
    DrawRotaGraph(0, 0, 2.0f, 0, _back_graph, true);

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha[0]);
    for(s16 i = 0; i < STAGE_MAX; i++) {
        if(!_flag[i]) {
            DrawBox(_cube_x[i], _cube_y[i], _cube_x[i] + high, _cube_y[i] + wide, WHITE, false);
        }
        else {
            DrawBox(_cube_x[i], _cube_y[i], _cube_x[i] + high, _cube_y[i] + wide, RED, false);
        }
        SetFontSize(80);
        char text[256];
        sprintf_s(text, "%d", i + 1);
        DrawString(_cube_x[i] + 30, _cube_y[i] + 15, text, WHITE, WHITE);

        SetFontSize(40);
        if(_clearStage[i] == 1) {
            // �f�t�H���g�t�H���g�n���h�����g�p���ĕ��������]�`�悷��
            DrawRotaString(_cube_x[i] + 15, _cube_y[i] + 5, 1.0f, 1.0f, 0, 0, 0.5f, RED, WHITE, 0, "CLEAR");
        }
    }

    if(_is_tutorial) {
        DrawBox(_tutorial_x, _tutorial_y, _tutorial_x + high, _tutorial_y + wide * 0.5f, RED, false);
    }
    else {
        DrawBox(_tutorial_x, _tutorial_y, _tutorial_x + high, _tutorial_y + wide * 0.5f, WHITE, false);
    }

    SetFontSize(12);
    if(_tutorial_x < _mouse_x && _tutorial_x + wide > _mouse_x && _tutorial_y < _mouse_y && _tutorial_y + high > _mouse_y) {
        drawTextToTutorial();
    }
    DrawString(_tutorial_x + 5, _tutorial_y + 19, "����[�Ƃ肠��", WHITE, true);

    SetFontSize(80);
    DrawString(70, 100, "STAGE SELECT", WHITE, WHITE);

    //! ���̕`��
    lockStage();

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha[1]);
    SetFontSize(100);
    char text[256];
    sprintf_s(text, "%d", _stage + 1);
    DrawString(100, 100, "STAGE", WHITE, WHITE);
    DrawString(400, 100, text, WHITE, WHITE);
    SetFontSize(20);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    //! �}�E�X�̏ꏊ��`��
    DrawCircle(_mouse_x, _mouse_y, 5, WHITE, true);

    DrawString(300, 450, "BACK TITLE[RESET]  ", WHITE);
    blinkText(500, 450, "PUSH SPACE");

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _back_alpha);
    DrawBox(0, 0, WINDOW_W, WINDOW_H, BLACK, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//---------------------------------------------------------------------------
//! ���
//---------------------------------------------------------------------------
void StageSelector::finalize()
{
}

//---------------------------------------------------------------------------
//! �S�̂̓��ߓx��������
//---------------------------------------------------------------------------
void StageSelector::decAlpha()
{
    if(_isAnim) {
        if(!_alpha <= 0)
            _alpha[0] -= 3;
    }
}

void StageSelector::addAlpha()
{
    if(_alpha[0] <= 0) {
        _alpha[1] += 3;
    }
    if(_alpha[1] >= 255) {
        _isAnimEnd = true;
    }
    if(_isAnimEnd) {
        _alpha[1] -= 7;
    }
    if(_alpha[1] <= 0 && _isAnimEnd) {
        Scene::sceneJump(new SceneGamePlay(_stage, _is_tutorial));
    }
}

s16 StageSelector::stage()
{
    return _stage;
}

//---------------------------------------------------------------------------
//! �`���[�g���A���@�\�I��
//---------------------------------------------------------------------------
bool StageSelector::isTutorial()
{
    return _is_tutorial;
}

//---------------------------------------------------------------------------
//! �X�e�[�W���b�N
//---------------------------------------------------------------------------
void StageSelector::lockStage()
{
    for(int i = 0; i < STAGE_MAX; i++) {
        //  if(_is_lock[i])
        //      break;

        //! �A�j���[�V�������n�܂��Ă��邩�ǂ����ł���alpha�l��ύX

        if(_is_stage_lock[i]) {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, _lock_stage_alpha[i]);
        }
        else if(_isAnim) {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha[0]);
        }

        DrawRotaGraph(_lock_x + (135 * i), _lock_y, 0.2f, 0, _lock_graph, true);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    }
}

//---------------------------------------------------------------------------
//! �X�e�[�W�A�����b�N
//---------------------------------------------------------------------------
void StageSelector::unlock()
{
    for(int i = 0; i < STAGE_MAX; i++) {
        if(_clearStage[i] == 1) {
            _is_stage_lock[i + 1] = true;
        }
    }
}

//---------------------------------------------------------------------------
//! ����������A�j���[�V����
//---------------------------------------------------------------------------
void StageSelector::unlockAnim()
{
    for(int i = 0; i < STAGE_MAX; i++) {
        if(_is_stage_lock[i]) {
            _lock_stage_alpha[i] -= 5;
        }
    }
}

//---------------------------------------------------------------------------
//! �`���[�g���A���I���I�t����
//---------------------------------------------------------------------------
void StageSelector::drawTextToTutorial()
{
    DrawString(_tutorial_x, _tutorial_y + 50, " �N���b�N��ON,OFF��؂�ւ���܂�", WHITE, true);
    if(_is_tutorial) {
        DrawString(_tutorial_x + 100, _tutorial_y + 20, " ON", WHITE, true);
    }
    else {
        DrawString(_tutorial_x + 100, _tutorial_y + 20, " OFF", WHITE, true);
    }
}

//---------------------------------------------------------------------------
//! �Ó]
//---------------------------------------------------------------------------
void StageSelector::blackOut()
{
    if(_back_alpha <= 0) {
        _back_alpha = 0;
    }

    if(_check)
        return;

    _back_alpha -= 5;
}

//---------------------------------------------------------------------------
//! �X�e�[�W�Z���N�^�[����^�C�g����
//---------------------------------------------------------------------------
void StageSelector::gameReset()
{
    if(_reset_timer < 120) {
        return;
    }

    if(CheckHitKey(KEY_INPUT_SPACE)) {
        _check = true;
    }

    if(!_check)
        return;

    if(_check) {
        _back_alpha += 3;
    }

    if(_back_alpha >= 255) {
        Scene::sceneJump(new SceneGameTitle());
    }
}
