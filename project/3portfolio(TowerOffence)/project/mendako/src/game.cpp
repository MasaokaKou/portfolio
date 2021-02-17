//---------------------------------------------------------------------------
//!	@file	game.cpp
//!	@brief	�\�[�X�R�[�h�S�̂̊Ǘ�
//---------------------------------------------------------------------------

static int _gametimer;   //! debug

//===========================================================================
//! �Q�[�����C��
//===========================================================================

//-----------------------------
//! �R���X�g���N�^
//-----------------------------
Game::Game()
{
    // �J�����̌��݈ʒu
    _cameraPos = VGet(0, 70, -70);

    // �J�����̒����_
    _cameraTarget = VGet(0, 0, 0);
}

//-----------------------------
//�f�X�g���N�^
//-----------------------------
Game::~Game()
{
}

//-----------------------------
//! ������
//-----------------------------
void Game::initialize()
{
    // �J�����̌��݈ʒu�Ƃǂ��������Ă��邩
    SetCameraPositionAndTarget_UpVecY(_cameraPos, _cameraTarget);
}
//---------------------------------------------------------------------------
//! �X�V
//---------------------------------------------------------------------------
void Game::update()
{
    // �V�[�������Ƃ���
    Scene::sceneUpdate();

    if(_gametimer == 1) {
        //Scene::sceneJump(new StageSelector());
        Scene::sceneJump(new SceneGamePlay(2, false));

        Scene::sceneJump(new SceneGameTitle());
        //Scene::sceneJump(new SceneGameClear());
    }
    _gametimer++;

#ifdef _DEBUG
    // �J�����̈ړ�

    if(CheckHitKey(KEY_INPUT_W)) {
        _cameraPos = VGet(0, 50, 50);
    }
    if(CheckHitKey(KEY_INPUT_A)) {
        _cameraPos = VGet(-50, 50, 0);
    }
    if(CheckHitKey(KEY_INPUT_S)) {
        _cameraPos = VGet(0, 50, -50);
    }
    if(CheckHitKey(KEY_INPUT_D)) {
        _cameraPos = VGet(50, 50, 0);
    }

    if(CheckHitKey(KEY_INPUT_UP)) {
        _cameraPos.y--;
    }
    if(CheckHitKey(KEY_INPUT_DOWN)) {
        _cameraPos.y++;
    }
    if(CheckHitKey(KEY_INPUT_RIGHT)) {
        _cameraPos.x++;
    }
    if(CheckHitKey(KEY_INPUT_LEFT)) {
        _cameraPos.x--;
    }

    // �J�����̌��݈ʒu�Ƃǂ��������Ă��邩
    SetCameraPositionAndTarget_UpVecY(_cameraPos, _cameraTarget);

#endif   // _DEBUG
    VECTOR v = VScale(_cameraPos, -1);

    ChangeLightTypeDir(v);
    // �J���[��f�̐F�ɋ߂Â���
    SetGlobalAmbientLight({ 0.4, 0.4, 0.4, 1.0 });
}
//---------------------------------------------------------------------------
//! �`��
//---------------------------------------------------------------------------
void Game::render()
{
}

//---------------------------------------------------------------------------
//! ���
//---------------------------------------------------------------------------
void Game::finalize()
{
    // �V�[���V�X�e���I��
    // �����ŋ����J�����Ȃ��ƃo�O��
    Scene::exit();
}