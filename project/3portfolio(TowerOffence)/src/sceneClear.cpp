//---------------------------------------------------------------------------
//!	@file	sceneGame.cpp
//!	@brief	�Q�[���v���C���̃V�[���̊Ǘ�
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! �R���X�g���N�^
//---------------------------------------------------------------------------
SceneStageClear::SceneStageClear(s16 stage, int fac_max_, int fac_num_, int time_)
{
    _stage      = stage;
    _alpha_frag = false;

    //�@�X�e�[�W���̓G�̍ő吔
    _fac_max = fac_max_;
    //�@�X�e�[�W���̓G������������
    _fac_num = fac_num_;

    // �o�ߎ���
    _time = time_;
    // ���ߓx
    _alpha = 255;

    //! �����N
    _rank     = 0;
    _fac_sum  = 0;
    _time_sum = 0;
    _sum      = 0;
}

//---------------------------------------------------------------------------
//! �f�X�g���N�^
//---------------------------------------------------------------------------
SceneStageClear::~SceneStageClear()
{
}
//---------------------------------------------------------------------------
//! ������
//!	@retval	true	����I��	(����)
//!	@retval	false	�G���[�I��	(���s)
//---------------------------------------------------------------------------
bool SceneStageClear::initialize()
{
    _back_graph = LoadGraph("data/stage_select_back.png");
    return true;
}

//---------------------------------------------------------------------------
//! �X�V
//---------------------------------------------------------------------------
void SceneStageClear::update()
{
    //! �X�y�[�X�ŃV�[���ړ�
    if(CheckHitKey(KEY_INPUT_SPACE)) {
        Scene::sceneJump(new StageSelector());
        gameClear();
    }

    //! �w�i�̍��𓧉�
    decAlpha();
    rank();

    //! �X�e�[�W���N���A�������ǂ����̃t���O�𗧂Ă�
    if(_rank != 5)
        _clearStage[_stage] = 1;
}

//---------------------------------------------------------------------------
//! �`��
//---------------------------------------------------------------------------
void SceneStageClear::render()
{
    // ���ߓx
    static int alpha_txst1 = 0;
    static int alpha_txst2 = 0;
    static int alpha_txst3 = 0;

    //! �w�i�`��
    DrawRotaGraph(0, 0, 2.0f, 0, _back_graph, true);

    //! �����`��
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_txst1);
    SetFontSize(50);
    DrawString(120, 100, "RESULT", WHITE, WHITE);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    //! �X�R�A�`��
    drawScore(alpha_txst2);

    //! ���X�ɓ��ߓx�ύX
    if(_alpha_frag)
        alpha_txst1 += 5;

    if(alpha_txst1 >= 255) {
        alpha_txst2 += 5;
    }
    if(alpha_txst2 >= 255) {
        alpha_txst3 += 5;
    }

    if(alpha_txst3 >= 255)
        blinkText(400, 350, "PUSH SPACE");

    drawBack();

    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_txst3);
    drawRank();
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    

}

//---------------------------------------------------------------------------
//! ���
//---------------------------------------------------------------------------
void SceneStageClear::finalize()
{
}

//---------------------------------------------------------------------------
//! �w�i�`��
//---------------------------------------------------------------------------
void SceneStageClear::drawBack()
{
    //! �w�i�̍���`��
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, _alpha);
    DrawBox(0, 0, WINDOW_W, WINDOW_H, BLACK, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//---------------------------------------------------------------------------
//! �X�R�A�X�V
//---------------------------------------------------------------------------
void SceneStageClear::updateScore()
{
}

//---------------------------------------------------------------------------
//! �X�R�A�`��
//---------------------------------------------------------------------------
void SceneStageClear::drawScore(int alpha_txst2_)
{
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha_txst2_);
    SetFontSize(30);
    DrawString(120, 200, "TIME", WHITE, WHITE);
    chengeText(_time, 200, 200, 255, 255, 255);

    DrawString(120, 250, "SCORE", WHITE, WHITE);
    chengeText(_fac_num, 240, 250, 255, 255, 255);
    DrawString(270, 250, "/", WHITE, WHITE);
    chengeText(_fac_max, 300, 250, 255, 255, 255);

    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

//---------------------------------------------------------------------------
//! �w�i�̍��𓧉�
//---------------------------------------------------------------------------
void SceneStageClear::decAlpha()
{
    //! �w�i�̍��𓧉�
    _alpha -= 5;
    if(_alpha <= 0) {
        _alpha_frag = true;
    }
}

//---------------------------------------------------------------------------
//! �]��
//---------------------------------------------------------------------------
void SceneStageClear::rank()
{
    _fac_sum  = _fac_max - _fac_num;
    _time_sum = _time * 0.1f;
    _sum      = _time_sum + _fac_sum;

    if(_sum <= 3) {
        _rank = 1;
    }
    else if(_sum <= 4) {
        _rank = 2;
    }
    else if(_sum <= 7) {
        _rank = 3;
    }
    else if(_sum <= 10) {
        _rank = 4;
    }
    else {
        _rank = 5;
    }
}

void SceneStageClear::drawRank()
{
    SetFontSize(120);

    if(_rank == 1) {
        DrawString(420, 100, "S", WHITE, WHITE);
    }
    else if(_rank == 2) {
        DrawString(420, 100, "A", RED, WHITE);
    }
    else if(_rank == 3) {
        DrawString(420, 100, "B", GetColor(0, 0, 255), WHITE);
    }
    else if(_rank == 4) {
        DrawString(420, 100, "C", GetColor(0, 255, 0), WHITE);
    }
    else if(_rank == 5) {
        DrawString(420, 100, "D", BLACK, WHITE);
    }
}

//---------------------------------------------------------------------------
//! �Q�[���N���A
//---------------------------------------------------------------------------
void SceneStageClear::gameClear()
{
    if(_clearStage[4] == 1) {
        Scene::sceneJump(new SceneGameClear());
    }
}
