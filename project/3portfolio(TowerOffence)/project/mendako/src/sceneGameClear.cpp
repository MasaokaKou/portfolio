//---------------------------------------------------------------------------
//!	@file	sceneGameClear.cpp
//!	@brief	�Q�[���v���C���̃V�[���̊Ǘ�
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! �R���X�g���N�^
//---------------------------------------------------------------------------
SceneGameClear::SceneGameClear()
{
    _text_x   = WINDOW_W * 0.5f;
    _text_y   = WINDOW_H + 100;
    _alpha[0] = 0;
    _alpha[1] = 0;
    _flag     = false;

    SetFontSize(20);
}

//---------------------------------------------------------------------------
//! �f�X�g���N�^
//---------------------------------------------------------------------------
SceneGameClear::~SceneGameClear()
{
}
//---------------------------------------------------------------------------
//! ������
//!	@retval	true	����I��	(����)
//!	@retval	false	�G���[�I��	(���s)
//---------------------------------------------------------------------------
bool SceneGameClear::initialize()
{
    _back_graph = LoadGraph("data/stage_select_back.png");
    return true;
}

//---------------------------------------------------------------------------
//! �X�V
//---------------------------------------------------------------------------
void SceneGameClear::update()
{
    SetFontSize(20);

    //! �G���h���[���X�V
    scrollEndRoll();

    _alpha[0] += 5;

}

//---------------------------------------------------------------------------
//! �`��
//---------------------------------------------------------------------------
void SceneGameClear::render()
{
    //! �w�i�`��
    DrawRotaGraph(0, 0, 2.0f, 0, _back_graph, true);

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha[0]);
    DrawBox(0, 0, WINDOW_W, WINDOW_H, BLACK, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha[1]);
    DrawString(WINDOW_W * 0.5f - (5 * 21), WINDOW_H * 0.5f, "THANK YOU FOR PLAYING", WHITE, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    //! �G���h���[���`��
    drawEndRoll();
}

//---------------------------------------------------------------------------
//! ���
//---------------------------------------------------------------------------
void SceneGameClear::finalize()
{
}

//---------------------------------------------------------------------------
//! �G���h���[���`��
//---------------------------------------------------------------------------
void SceneGameClear::drawEndRoll()
{
    DrawString(_text_x - (5 * 14), _text_y, ":GAME PROJECT:", WHITE);
    DrawString(_text_x - (5 * 10), _text_y + 40, "KO MASAOKA", WHITE);
    DrawString(_text_x - (5 * 14), _text_y + 100, ":MODEL DESIGN:", WHITE);
    DrawString(_text_x - (5 * 8), _text_y + 160, "�`UNIT�`", WHITE);
    DrawString(_text_x - (5 * 11), _text_y + 200, "HANA MUTUDA", WHITE);
    DrawString(_text_x - (5 * 9), _text_y + 260, "�`ENEMY�`", WHITE);
    DrawString(_text_x - (5 * 8), _text_y + 300, "MATT ART", WHITE);
    DrawString(_text_x - (5 * 20), _text_y + 340, "BY UNITY ASSET STORE", WHITE);
    DrawString(_text_x - (5 * 17), _text_y + 400, "�`MOTION DESIGN�`", WHITE);
    DrawString(_text_x - (5 * 10), _text_y + 440, "KO MASAOKA", WHITE);
    DrawString(_text_x - (5 * 11), _text_y + 500, "�`PROGRAM�`", WHITE);
    DrawString(_text_x - (5 * 10), _text_y + 540, "KO MASAOKA", WHITE);
}
//---------------------------------------------------------------------------
//! �G���h���[���X�V
//---------------------------------------------------------------------------
void SceneGameClear::scrollEndRoll()
{
    _text_y -= 1;

    if(_text_y + 560 < 0) {
        _alpha[1] += 2;
        if(_alpha[1] >= 255) {
            _flag = true;
        }
    }

    if(_flag) {
        _alpha[1] -= 4;
        if(_alpha[1] <= 0) {
            Scene::sceneJump(new SceneGameTitle());
        }
    }

    if(CheckHitKey(KEY_INPUT_SPACE)) {
        _text_y -= 2;
    }
}
