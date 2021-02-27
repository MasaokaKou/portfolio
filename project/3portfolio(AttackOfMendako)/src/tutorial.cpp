//---------------------------------------------------------------------------
//!	@file	tutorial.h
//!	@brief	�`���[�g���A���̊Ǘ�
//---------------------------------------------------------------------------

//------------------------------------
//! �R���X�g���N�^
//------------------------------------
Tutorial::Tutorial()
{
    // �����^���E
    _mendako = new Model;

    // �����^���E�̐����o��
    _speech_graph_x       = 50;
    _speech_graph_y       = 170;
    _speech_under_graph_y = 190;

    // �������ʂ̖��܂��͉~
    _arrow_graph_x = 0;
    _arrow_graph_y = 0;

    // �����o���̗L��
    _is_visible = false;

    _flow = FLOW::NONE;

    _span = true;

    _stageNum = 0;

    _type_to_unit = false;
}

//------------------------------------
//! �f�X�g���N�^
//------------------------------------
Tutorial::~Tutorial()
{
}

//------------------------------------
//! ������
//------------------------------------
void Tutorial::initialize()
{
    //! ���f���̓ǂݍ���
    _mendako->load("data/Unit/Unit.mqo");

    _graphHandle = LoadGraph("data/Unit/Unit.png");

    _mendako->setPos(VGet(40, 10, -20));
    _mendako->setScale(VGet(0.1f, 0.1f, 0.1f));
    _mendako->setRota(VGet(0.1f, 1.0, 0));

    _g_handle = LoadGraph("data/circle.png");

    //! ���f���Ƀe�N�X�`���𒣂�t��
    MV1SetTextureGraphHandle(_mendako->handle(), 0, _graphHandle, false);
}
//------------------------------------
//! �X�V
//------------------------------------
void Tutorial::update()
{
    startAnimation();

    if(CheckHitKey(KEY_INPUT_SPACE) && _span) {
        _is_visible = false;
        setSpeech();
        _span = false;
    }
}
//------------------------------------
//! �`��
//------------------------------------
void Tutorial::render()
{
    // if(!_is_visible)
    //     return;

    //! �����ɂ���
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
    DrawBox(_speech_graph_x, _speech_graph_y, (WINDOW_W - _speech_graph_x), _speech_under_graph_y, BLACK, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    if(_is_visible)
    _mendako->draw();

    flow();
}
//------------------------------------
//! ���
//------------------------------------
void Tutorial::finalize()
{
}

//-------------------------------------
//! ���f���Ɛ����o���̓o��A�j���[�V����
//--------------------------------------
void Tutorial::startAnimation()
{
    static int anim_speed = 10;

    if(_is_visible) {
        if(_speech_graph_y >= 50) {
            _speech_graph_y -= anim_speed;
        }

        if(_speech_under_graph_y <= 300) {
            _speech_under_graph_y += anim_speed;
        }
    }

    if(!_is_visible) {
        if(_speech_graph_y <= 175) {
            _speech_graph_y += anim_speed;
        }

        if(_speech_under_graph_y >= 190) {
            _speech_under_graph_y -= anim_speed;
        }
        else {
            _span = true;
        }
    }
}

//-------------------------------------
//! �����o�����o��
//-------------------------------------
void Tutorial::setSpeech()
{
    switch(_flow) {
        case NONE:
            _flow = FLOW::GAME_STYLE;
            break;

        case GAME_STYLE:
            _flow = FLOW::UNIT2;
            break;

        case UNIT_NUM:

            break;

        case UNIT2:
            _flow = FLOW::UNIT1;
            break;

        case UNIT1:
            _flow = FLOW::Unit;
            break;

        case Unit:
            _flow = FLOW::BOSS;
            break;
        case BOSS:
            _flow = FLOW::STAY;
            break;
        case UNIT3:
            _flow = FLOW::END;
            break;

        case STAY:
            break;

        case END:

            break;

        default:
            break;
    }
}

//-------------------------------------
//! �`���[�g���A���̗���
//-------------------------------------
void Tutorial::flow()
{
    switch(_flow) {
        case NONE:

            break;
        case GAME_STYLE:
            if(_stageNum == 0)
                firstGameStyle();
            break;
        case UNIT2:
            //�������j�b�g�̏o����
            if(_stageNum == 0)
                howToSetUnit();

            break;
        case UNIT1:
            if(_stageNum == 0)
                howRangeSetUnit();
            break;
        case Unit:
            //�G�̊m�F�@
            if(_stageNum == 0)
                checkUnit();
            break;
        case BOSS:
            //�Q�[���N���A�����̊m�F
            if(_stageNum == 0)
                checkBossUnit();
            break;

        case UNIT3:
            //���j�b�g�̒ǉ��Ɛ���
            typeToUnit();

            break;

        default:
            break;
    }
}

//-------------------------------------
//! �ȒP�ȃQ�[���̏Љ�
//-------------------------------------
void Tutorial::firstGameStyle()
{
    if(_is_visible) {
        DrawString(100, 170, "�������j�b�g��z�u���ēG��|���܂��傤", WHITE, true);
        blinkText(270, 260, "PUSH SPACE");
    }
}

//-------------------------------------
//1 �������j�b�g�̏o����
//-------------------------------------
void Tutorial::howToSetUnit()
{
    if(_span)
        _is_visible = true;

    if(_is_visible) {
        DrawString(100, 150, "�������j�b�g�͍��N���b�N�Ŕz�u�ł��܂�", WHITE, true);
        DrawString(100, 170, "�����ɔz�u���Ă݂܂��傤", WHITE, true);
        blinkText(270, 260, "PUSH SPACE");
    }
}

//-------------------------------------
//1 �������j�b�g�̏����\�͈͐���
//-------------------------------------
void Tutorial::howRangeSetUnit()
{
    _arrow_graph_x = 40;
    _arrow_graph_y = 80;

    static int count     = 0;
    const int  count_max = 20;
    count++;

    if(count > 0 && count < count_max * 0.5f) {
        DrawGraph(_arrow_graph_x, _arrow_graph_y, _g_handle, true);
    }

    if(count > count_max) {
        count = 0;
    }

    if(GetMouseInput() & MOUSE_INPUT_LEFT != 0) {
        setSpeech();
    }
}

//-------------------------------------
//1 �G�̊m�F�@
//-------------------------------------
void Tutorial::checkUnit()
{
    static int count = 120;

    count--;

    if(count < 0) {
        _is_visible = true;
    }

    if(_is_visible) {
        DrawString(100, 150, "�������j�b�g�͓G�̓��Ɍ������Ă��ǂ����A", WHITE, true);
        DrawString(100, 170, "��苗���߂Â��ƍU�����n�߂܂�", WHITE, true);
        blinkText(270, 260, "PUSH SPACE");
    }
}

//-------------------------------------
//1 �Q�[���N���A�����̊m�F
//-------------------------------------
void Tutorial::checkBossUnit()
{
    if(_span)
        _is_visible = true;

    if(_is_visible) {
        DrawString(100, 150, "�E��̋���ȓ����󂹂΃X�e�[�W�N���A�ł�!", WHITE, true);
        blinkText(270, 260, "PUSH SPACE");
    }
}

//-------------------------------------
//���j�b�g�̒ǉ��Ɛ���
//-------------------------------------
void Tutorial::typeToUnit()
{
    if(_span)
        _is_visible = true;

    if(_is_visible) {
        DrawString(100, 130, "�X�e�[�W���N���A���邲�ƂɎg���郆�j�b�g", WHITE, true);
        DrawString(240, 150, "�̎�ނ������܂�", WHITE, true);
        DrawString(100, 190, "���̊G���N���b�N���邱�ƂŃ��j�b�g�̐؂�", WHITE, true);
        DrawString(170, 210, "�ւ��Ɣ\�͂̊m�F���ł��܂�", WHITE, true);
        _type_to_unit = true;

        blinkText(270, 260, "PUSH SPACE");
    }
}

//-------------------------------------
//! �X�e�[�W�ԍ��������Ă���
//-------------------------------------
void Tutorial::setStageNum(int stageNum_)
{
    _stageNum = stageNum_;
}

FLOW Tutorial::getFlow()
{
    return _flow;
}

void Tutorial::setFlow(FLOW a_)
{
    _flow = a_;
}

bool Tutorial::IsTypeToUnit()
{
    return _type_to_unit;
}
