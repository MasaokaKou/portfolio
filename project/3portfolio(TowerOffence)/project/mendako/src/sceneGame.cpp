//---------------------------------------------------------------------------
//!	@file	sceneGame.cpp
//!	@brief	ゲームプレイ中のシーンの管理
//---------------------------------------------------------------------------

// タスクマネージャーのユニークポインター
std::unique_ptr<TaskManager> _tMng;

//---------------------------------------------------------------------------
//! コンストラクタ
//---------------------------------------------------------------------------
SceneGamePlay::SceneGamePlay(s16 stage_, bool is_tutorial_)
{
    //! 現在のステージ
    _stage       = stage_;
    _is_tutorial = is_tutorial_;

    //! タスクマネージャーの実体生成
    //if (_tMng == nullptr)
    _tMng = std::make_unique<TaskManager>(_stage);

    //! 背景のモデル
    _under_ground = new Model;

    //! チュートリアルの有無
    _tutorial = nullptr;
    _timer   = 0;
    _counter = 0;
}

//---------------------------------------------------------------------------
//! デストラクタ
//---------------------------------------------------------------------------
SceneGamePlay::~SceneGamePlay()
{
    finalize();
}

//---------------------------------------------------------------------------
//! 初期化
//!	@retval	true	正常終了	(成功)
//!	@retval	false	エラー終了	(失敗)
//---------------------------------------------------------------------------
bool SceneGamePlay::initialize()
{
    //! タスクマネージャーの初期化
    if(_tMng)
        _tMng->initialize();

    //! 背景の読み込み
    if(_under_ground)
        _under_ground->load("data/sea.mqo");

    //! _is_tutorialがTRUEなら実態を生成
    if(_is_tutorial) {
        _tutorial = new Tutorial;
    }

    //! チュートリアル初期化
    if(_tutorial != nullptr)
        _tutorial->initialize();

    return true;
}

//---------------------------------------------------------------------------
//! 更新
//---------------------------------------------------------------------------
void SceneGamePlay::update()
{
    //! チュートリアルの更新
    tutorialUpdate();

    //! チュートリアル更新
    if(_tutorial != nullptr)
        _tutorial->update();

    //! チュートリアルのテキストが出ていたらゲームを止める
    if(isText()) {
        return;
    }

    //! タスクマネージャーの更新
    if(_tMng)
        _tMng->update();

    //1 背景の設定
    setBackModel();

    //! ゲームを始めた最初一回だけとおす
    tutorialOnce();

    //! タイマー
    timerUpdate();

    //! タスクマネージャーに経過時間を渡す
    if(_tMng)
        _tMng->setTime(_timer);
}

//---------------------------------------------------------------------------
//! 描画
//---------------------------------------------------------------------------
void SceneGamePlay::render()
{
    DrawString(0, 0, "PLAY", BLACK, true);

    if(_under_ground)
        _under_ground->draw();

    //! タスクマネージャーの描画
    if(_tMng)
        _tMng->render();

    //! チュートリアル描画
    if(_tutorial != nullptr)
        _tutorial->render();
}

//---------------------------------------------------------------------------
//! 解放
//---------------------------------------------------------------------------
void SceneGamePlay::finalize()
{
    //! タスクマネージャーの解放
    if(_tMng) {
        _tMng->finalize();
        _tMng.release();
    }
}

//---------------------------------------------------------------------------
//! チュートリアルの更新
//---------------------------------------------------------------------------
void SceneGamePlay::tutorialUpdate()
{
    //! チュートリアルが生成されてるか
    if(_tutorial != nullptr) {
        //! ステージ番号をチュートリアルに送る
        _tutorial->setStageNum(_stage);
        //! ステージ番号によってチュートリアルを変える
        if(_stage == 1 && !_tutorial->IsTypeToUnit())
            _tutorial->setFlow(FLOW::UNIT3);
    }
}

//---------------------------------------------------------------------------
//! チュートリアルのテキストが出ていたらゲームを止める
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
//1 背景の設定
//---------------------------------------------------------------------------
void SceneGamePlay::setBackModel()
{
    //1 背景の設定
    if(_under_ground) {
        _under_ground->setPos(VGet(0, -0.1, 0));
        _under_ground->setScale(VGet(2, 0.0001, 2));
    }
}

//---------------------------------------------------------------------------
//! ゲームを始めた最初一回だけとおす
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
//! タイマー
//---------------------------------------------------------------------------
void SceneGamePlay::timerUpdate()
{
    _counter++;

    if(_counter % 60 == 0) {
        _timer++;
    }
}
