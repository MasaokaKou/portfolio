//---------------------------------------------------------------------------
//!	@file	unitSelector.cpp
//!	@brief	unitSelector����
//---------------------------------------------------------------------------

//===========================================================================
//! ���j�b�g�Z���N�^�[
//===========================================================================

//---------------------------------------------------------------------------
//! �R���X�g���N�^
//---------------------------------------------------------------------------
unitSelector ::unitSelector()
{
    _sel_num = 0;
    //!(x,y,h&w)
    _sel_car = VGet(25, 408, 53);

    for(s16 i = 0; i < UNIT_MAX; i++) {
        _sel_box[i] = VGet(0, 0, 5);
        _is_hit[i]  = false;
        _unit_limit.push_back(i);

        if(!_is_unit_lock[i])
            _lock_unit_alpha[i] = 255;
    }

    _is_move = false;
    _timer   = 0;

    GetMousePoint(&_mouse_x, &_mouse_y);
}

//---------------------------------------------------------------------------
//! �f�X�g���N�^
//---------------------------------------------------------------------------
unitSelector ::~unitSelector()
{
}

//---------------------------------------------------------------------------
//! ������
//---------------------------------------------------------------------------
bool unitSelector::initialize()
{
    _graph[0] = LoadGraph("data/Unit/Unit.png");
    _graph[1] = LoadGraph("data/Unit/unitTypeB.png");
    _graph[2] = LoadGraph("data/Unit/unitTypeC.png");
    _graph[3] = LoadGraph("data/Unit/unitTypeD.png");

    _lock_graph = LoadGraph("data/lock.png");

    return true;
}

//---------------------------------------------------------------------------
//! �X�V
//---------------------------------------------------------------------------
void unitSelector::update()
{
    //! �J�[�\���̈ʒu��sel_num������

    for(s16 i = 0; i < UNIT_MAX; i++) {
        if(_sel_car.x == 25 + (i * 60)) {
            _sel_num = 0 + i;
        }

        lockAnim(i);
    }

    lockUnit();

    hitMouseCheck();
    setUnitFromMouse();

    limit();
    GetMousePoint(&_mouse_x, &_mouse_y);


}
//---------------------------------------------------------------------------
//! �`��
//---------------------------------------------------------------------------
void unitSelector::render()
{
    s16 frame = 20;

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 160);
    DrawBox(0, WINDOW_H * 0.8f, WINDOW_W, WINDOW_H, BLACK, true);
    DrawBox(frame, WINDOW_H * 0.8f + frame, WINDOW_W - frame, WINDOW_H - frame, WHITE, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
    for(s16 i = 0; i < UNIT_MAX; i++) {
        _sel_box[i] = VGet(25 + (60 * i), 408, 50);

        //! 0�ɂȂ����瓧�߂�����
        if(_unit_limit.at(i) == 0) {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
        }
        else {
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
        }

        DrawRotaGraph(50 + (60 * i), 433, 0.05f, 0, _graph[i], true);
        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        s16 x     = _sel_box[i].x + 25;
        s16 y     = _sel_box[i].y + 25;
        s16 space = 25;

        DrawBox(x, y, x + space, y + space, WHITE, true);

        DrawString(x, y + 11, "x", BLACK);

        SetFontSize(15);
        chengeText(_unit_limit.at(i), x + 10, y + 11, 0, 0, 0);
        SetFontSize(20);
        drawLock(i);

        textTypeOfUnit(i);
    }
    //! �J�[�\���`��
    for(s16 i = 0; i < 20; i++)
        DrawBox(_sel_car.x - (0.1f * i), _sel_car.y - (0.1f * i), _sel_car.x + _sel_car.z - (0.1f * i), _sel_car.y + _sel_car.z - (0.1f * i), GetColor(0, 0, 0), false);
}

//---------------------------------------------------------------------------
//! ���
//---------------------------------------------------------------------------
void unitSelector::finalize()
{
}

//---------------------------------------------------------------------------
//! ��x�J�[�\���𓮂����Ă��玟�ɂ���������܂�
//---------------------------------------------------------------------------
bool unitSelector::timer()
{
    if(_is_move) {
        _timer++;
    }

    if(_timer >= 10) {
        _timer   = 0;
        _is_move = false;
    }
    if(!_is_move) {
        return true;
    }

    return false;
}
//---------------------------------------------------------------------------
//! �J�[�\���̈ړ�����
//---------------------------------------------------------------------------
void unitSelector::limit()
{
    if(_sel_car.x <= 25 - 60) {
        _sel_car.x = 205;
    }
    if(_sel_car.x >= 265) {
        _sel_car.x = 25;
    }

    for(s16 i = 0; i < UNIT_MAX; i++) {
        if(_is_hit[i])
            _sel_car.x = 25 + (i * 60);
    }
}
//---------------------------------------------------------------------------
//! �e���j�b�g�̏����������Ă���
//---------------------------------------------------------------------------
void unitSelector::setUnitLimit(std::vector<s16> unit_limit_)
{
    for(s16 i = 0; i < UNIT_MAX; i++)
        _unit_limit.at(i) = unit_limit_[i];
}

//---------------------------------------------------------------------------
//! �}�E�X�ƃZ���N�g�{�b�N�X�̔���
//---------------------------------------------------------------------------
void unitSelector::hitMouseCheck()
{
    for(s16 i = 0; i < UNIT_MAX; i++) {
        if(checkHit(i)) {
            if(GetMouseInput() & MOUSE_INPUT_LEFT != 0 && _is_unit_lock[i])
                _is_hit[i] = true;
        }
        else {
            _is_hit[i] = false;
        }
    }
}

void unitSelector::setUnitFromMouse()
{
    for(s16 i = 0; i < UNIT_MAX; i++) {
        if(_is_hit[i])
            _sel_num = i;
    }
}

//---------------------------------------------------------------------------
//! �I�ׂ郆�j�b�g�̐���
//---------------------------------------------------------------------------
void unitSelector::lockUnit()
{
    for(s16 i = 0; i < UNIT_MAX; i++) {
        if(_is_stage_lock[i]) {
            _is_unit_lock[i] = true;
        }
    }
}

//---------------------------------------------------------------------------
//! ���`��
//---------------------------------------------------------------------------
void unitSelector::drawLock(int i_)
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _lock_unit_alpha[i_]);
    DrawRotaGraph(50 + (60 * i_), 435, 0.1f, 0, _lock_graph, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//---------------------------------------------------------------------------
//! �A�����b�N�A�j���[�V����
//---------------------------------------------------------------------------
void unitSelector::lockAnim(int i_)
{
    if(_is_unit_lock[i_]) {
        _lock_unit_alpha[i_] -= 5;
    }
}

//---------------------------------------------------------------------------
//! ���j�b�g�ɃJ�[�\�������������̃e�L�X�g
//---------------------------------------------------------------------------
void unitSelector::textTypeOfUnit(int i_)
{
    if(checkHit(i_)) {
        int x = _sel_box[i_].x;
        int y = _sel_box[i_].z + 300;

        SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
        DrawBox(x, y, x + 120, y + 60, WHITE, true);

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

        for(int j = 0; j < 2; j++)
            DrawBox(x + j, y + j, x + 120 - j, y + 60 - j, BLACK, false);
    }

    SetFontSize(10);
    if(checkHit(0)) {
        int x = _sel_box[0].x;
        int y = _sel_box[i_].z + 300;

        DrawString(x + 5, y + 5, "�߂������Ƃ����傤��", BLACK, true);
        DrawString(x + 5, y + 15, "�Ȃ��@�@�@�̂߂񂾂�", BLACK, true);
        DrawString(x + 26, y + 15, "�ӂ�", RED, true);
        DrawString(x + 5, y + 35, "�߂̂܂��̂Ă���", BLACK, true);
        DrawString(x + 5, y + 45, "������������", BLACK, true);
    }

    if(checkHit(1)) {
        int x = _sel_box[1].x;
        int y = _sel_box[i_].z + 300;

        DrawString(x + 5, y + 5, "�Ƃ����ւ̂��������@", RED, true);
        DrawString(x + 105, y + 5, "��", BLACK, true);
        DrawString(x + 5, y + 15, "�Ƃ����Ȃ߂񂾂�", BLACK, true);
        DrawString(x + 5, y + 35, "�ӂ��̂߂񂾂����", BLACK, true);
        DrawString(x + 5, y + 45, "������傭�������Ȃ�", BLACK, true);
    }

    if(checkHit(2)) {
        int x = _sel_box[2].x;
        int y = _sel_box[i_].z + 300;

        DrawString(x + 5, y + 5, "���߂ɂ̂����߂񂾂�", BLACK, true);
        DrawString(x + 5, y + 15, "�������͂�������", BLACK, true);
        DrawString(x + 5, y + 35, "�ӂ��̂߂񂾂����", BLACK, true);
        DrawString(x + 5, y + 45, "������傭��������", RED, true);
    }

    if(checkHit(3)) {
        int x = _sel_box[3].x;
        int y = _sel_box[i_].z + 300;

        DrawString(x + 5, y + 5, "���肨�˂ɂ̂���", BLACK, true);
        DrawString(x + 5, y + 15, "�߂񂾂�", BLACK, true);
        DrawString(x + 5, y + 25, "�ق��̂߂񂾂���", BLACK, true);
        DrawString(x + 5, y + 35, "������傭��", RED, true);
        DrawString(x + 5, y + 45, "�����ӂ����Ă����", RED, true);
    }

    SetFontSize(20);
}

bool unitSelector::checkHit(int i_)
{
    if(_mouse_x >= _sel_box[i_].x && _mouse_x <= _sel_box[i_].x + _sel_box[i_].z && _mouse_y >= _sel_box[i_].y && _mouse_y <= _sel_box[i_].y + _sel_box[i_].z) {
        return true;
    }

    return false;
}