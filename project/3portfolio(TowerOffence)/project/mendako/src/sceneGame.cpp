//---------------------------------------------------------------------------
//!	@file	sceneGame.cpp
//!	@brief	�Q�[���v���C���̃V�[���̊Ǘ�
//---------------------------------------------------------------------------

// �^�X�N�}�l�[�W���[�̃��j�[�N�|�C���^�[
std::unique_ptr<TaskManager> _tMng;

//---------------------------------------------------------------------------
//! �R���X�g���N�^
//---------------------------------------------------------------------------
SceneGamePlay::SceneGamePlay(s16 stage_, bool is_tutorial_)
{
    //! ���݂̃X�e�[�W
    _stage       = stage_;
    _is_tutorial = is_tutorial_;

    //! �^�X�N�}�l�[�W���[�̎��̐���
    //if (_tMng == nullptr)
    _tMng = std::make_unique<TaskManager>(_stage);

    //! �w�i�̃��f��
    _under_ground = new Model;

    //! �`���[�g���A���̗L��
    _tutorial = nullptr;
    _timer   = 0;
    _counter = 0;
}

//---------------------------------------------------------------------------
//! �f�X�g���N�^
//---------------------------------------------------------------------------
SceneGamePlay::~SceneGamePlay()
{
    finalize();
}

//---------------------------------------------------------------------------
//! ������
//!	@retval	true	����I��	(����)
//!	@retval	false	�G���[�I��	(���s)
//---------------------------------------------------------------------------
bool SceneGamePlay::initialize()
{
    //! �^�X�N�}�l�[�W���[�̏�����
    if(_tMng)
        _tMng->initialize();

    //! �w�i�̓ǂݍ���
    if(_under_ground)
        _under_ground->load("data/sea.mqo");

    //! _is_tutorial��TRUE�Ȃ���Ԃ𐶐�
    if(_is_tutorial) {
        _tutorial = new Tutorial;
    }

    //! �`���[�g���A��������
    if(_tutorial != nullptr)
        _tutorial->initialize();

    return true;
}

//---------------------------------------------------------------------------
//! �X�V
//---------------------------------------------------------------------------
void SceneGamePlay::update()
{
    //! �`���[�g���A���̍X�V
    tutorialUpdate();

    //! �`���[�g���A���X�V
    if(_tutorial != nullptr)
        _tutorial->update();

    //! �`���[�g���A���̃e�L�X�g���o�Ă�����Q�[�����~�߂�
    if(isText()) {
        return;
    }

    //! �^�X�N�}�l�[�W���[�̍X�V
    if(_tMng)
        _tMng->update();

    //1 �w�i�̐ݒ�
    setBackModel();

    //! �Q�[�����n�߂��ŏ���񂾂��Ƃ���
    tutorialOnce();

    //! �^�C�}�[
    timerUpdate();

    //! �^�X�N�}�l�[�W���[�Ɍo�ߎ��Ԃ�n��
    if(_tMng)
        _tMng->setTime(_timer);
}

//---------------------------------------------------------------------------
//! �`��
//---------------------------------------------------------------------------
void SceneGamePlay::render()
{
    DrawString(0, 0, "PLAY", BLACK, true);

    if(_under_ground)
        _under_ground->draw();

    //! �^�X�N�}�l�[�W���[�̕`��
    if(_tMng)
        _tMng->render();

    //! �`���[�g���A���`��
    if(_tutorial != nullptr)
        _tutorial->render();
}

//---------------------------------------------------------------------------
//! ���
//---------------------------------------------------------------------------
void SceneGamePlay::finalize()
{
    //! �^�X�N�}�l�[�W���[�̉��
    if(_tMng) {
        _tMng->finalize();
        _tMng.release();
    }
}

//---------------------------------------------------------------------------
//! �`���[�g���A���̍X�V
//---------------------------------------------------------------------------
void SceneGamePlay::tutorialUpdate()
{
    //! �`���[�g���A������������Ă邩
    if(_tutorial != nullptr) {
        //! �X�e�[�W�ԍ����`���[�g���A���ɑ���
        _tutorial->setStageNum(_stage);
        //! �X�e�[�W�ԍ��ɂ���ă`���[�g���A����ς���
        if(_stage == 1 && !_tutorial->IsTypeToUnit())
            _tutorial->setFlow(FLOW::UNIT3);
    }
}

//---------------------------------------------------------------------------
//! �`���[�g���A���̃e�L�X�g���o�Ă�����Q�[�����~�߂�
//---------------------------------------------------------------------------
bool SceneGamePlay::isText()
{
    if(_tutorial != nullptr) {
        if(_tutorial->isVisible())
            return true;
    }
    return false;
}

//---------------------------------------------------------------------------
//1 �w�i�̐ݒ�
//---------------------------------------------------------------------------
void SceneGamePlay::setBackModel()
{
    //1 �w�i�̐ݒ�
    if(_under_ground) {
        _under_ground->setPos(VGet(0, -0.1, 0));
        _under_ground->setScale(VGet(2, 0.0001, 2));
    }
}

//---------------------------------------------------------------------------
//! �Q�[�����n�߂��ŏ���񂾂��Ƃ���
//---------------------------------------------------------------------------
void SceneGamePlay::tutorialOnce()
{
    if(_tutorial != nullptr) {
        if(_stage == 0 && _tutorial->getFlow() == FLOW::NONE) {
            _tutorial->setSpeech();
            _tutorial->setIsVisible(TRUE);
        }
    }
}

//---------------------------------------------------------------------------
//! �^�C�}�[
//---------------------------------------------------------------------------
void SceneGamePlay::timerUpdate()
{
    _counter++;

    if(_counter % 60 == 0) {
        _timer++;
    }
}
