//---------------------------------------------------------------------------
//!	@file	tutorial.h
//!	@brief	チュートリアルの管理
//---------------------------------------------------------------------------

//------------------------------------
//! コンストラクタ
//------------------------------------
Tutorial::Tutorial()
{
    // メンタロウ
    _mendako = new Model;

    // メンタロウの吹き出し
    _speech_graph_x       = 50;
    _speech_graph_y       = 170;
    _speech_under_graph_y = 190;

    // 説明部位の矢印または円
    _arrow_graph_x = 0;
    _arrow_graph_y = 0;

    // 吹き出しの有無
    _is_visible = false;

    _flow = FLOW::NONE;

    _span = true;

    _stageNum = 0;

    _type_to_unit = false;
}

//------------------------------------
//! デストラクタ
//------------------------------------
Tutorial::~Tutorial()
{
}

//------------------------------------
//! 初期化
//------------------------------------
void Tutorial::initialize()
{
    //! モデルの読み込み
    _mendako->load("data/Unit/Unit.mqo");

    _graphHandle = LoadGraph("data/Unit/Unit.png");

    _mendako->setPos(VGet(40, 10, -20));
    _mendako->setScale(VGet(0.1f, 0.1f, 0.1f));
    _mendako->setRota(VGet(0.1f, 1.0, 0));

    _g_handle = LoadGraph("data/circle.png");

    //! モデルにテクスチャを張り付け
    MV1SetTextureGraphHandle(_mendako->handle(), 0, _graphHandle, false);
}
//------------------------------------
//! 更新
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
//! 描画
//------------------------------------
void Tutorial::render()
{
    // if(!_is_visible)
    //     return;

    //! 透明にする
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 155);
    DrawBox(_speech_graph_x, _speech_graph_y, (WINDOW_W - _speech_graph_x), _speech_under_graph_y, BLACK, true);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

    if(_is_visible)
    _mendako->draw();

    flow();
}
//------------------------------------
//! 解放
//------------------------------------
void Tutorial::finalize()
{
}

//-------------------------------------
//! モデルと吹き出しの登場アニメーション
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
//! 吹き出しを出す
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
//! チュートリアルの流れ
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
            //味方ユニットの出し方
            if(_stageNum == 0)
                howToSetUnit();

            break;
        case UNIT1:
            if(_stageNum == 0)
                howRangeSetUnit();
            break;
        case Unit:
            //敵の確認　
            if(_stageNum == 0)
                checkUnit();
            break;
        case BOSS:
            //ゲームクリア条件の確認
            if(_stageNum == 0)
                checkBossUnit();
            break;

        case UNIT3:
            //ユニットの追加と説明
            typeToUnit();

            break;

        default:
            break;
    }
}

//-------------------------------------
//! 簡単なゲームの紹介
//-------------------------------------
void Tutorial::firstGameStyle()
{
    if(_is_visible) {
        DrawString(100, 170, "味方ユニットを配置して敵を倒しましょう", WHITE, true);
        blinkText(270, 260, "PUSH SPACE");
    }
}

//-------------------------------------
//1 味方ユニットの出し方
//-------------------------------------
void Tutorial::howToSetUnit()
{
    if(_span)
        _is_visible = true;

    if(_is_visible) {
        DrawString(100, 150, "味方ユニットは左クリックで配置できます", WHITE, true);
        DrawString(100, 170, "試しに配置してみましょう", WHITE, true);
        blinkText(270, 260, "PUSH SPACE");
    }
}

//-------------------------------------
//1 味方ユニットの召喚可能範囲説明
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
//1 敵の確認　
//-------------------------------------
void Tutorial::checkUnit()
{
    static int count = 120;

    count--;

    if(count < 0) {
        _is_visible = true;
    }

    if(_is_visible) {
        DrawString(100, 150, "味方ユニットは敵の塔に向かっていどうし、", WHITE, true);
        DrawString(100, 170, "一定距離近づくと攻撃を始めます", WHITE, true);
        blinkText(270, 260, "PUSH SPACE");
    }
}

//-------------------------------------
//1 ゲームクリア条件の確認
//-------------------------------------
void Tutorial::checkBossUnit()
{
    if(_span)
        _is_visible = true;

    if(_is_visible) {
        DrawString(100, 150, "右上の巨大な塔を壊せばステージクリアです!", WHITE, true);
        blinkText(270, 260, "PUSH SPACE");
    }
}

//-------------------------------------
//ユニットの追加と説明
//-------------------------------------
void Tutorial::typeToUnit()
{
    if(_span)
        _is_visible = true;

    if(_is_visible) {
        DrawString(100, 130, "ステージをクリアするごとに使えるユニット", WHITE, true);
        DrawString(240, 150, "の種類が増えます", WHITE, true);
        DrawString(100, 190, "下の絵をクリックすることでユニットの切り", WHITE, true);
        DrawString(170, 210, "替えと能力の確認ができます", WHITE, true);
        _type_to_unit = true;

        blinkText(270, 260, "PUSH SPACE");
    }
}

//-------------------------------------
//! ステージ番号を持ってくる
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
