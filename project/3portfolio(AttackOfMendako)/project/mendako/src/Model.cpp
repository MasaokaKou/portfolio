#include "Main.h"
#include "Model.h"

Model::Model()
{
    _handle = 0;
}

Model::~Model()
{
}

//-----------------------------------------
// モデルの読み込み
//-----------------------------------------
void Model::load(const char* fileName_)
{
    _handle = MV1LoadModel(&*fileName_);
}

//-----------------------------------------
// モデルの座標設定
//-----------------------------------------
void Model::setPos(VECTOR pos_)
{
    MV1SetPosition(_handle, pos_);
}

//-----------------------------------------
// モデルの倍率変更
//-----------------------------------------
void Model::setScale(VECTOR scale_)
{
    MV1SetScale(_handle, scale_);
}

//-----------------------------------------
// 回転
//-----------------------------------------
void Model::setRota(VECTOR rota_)
{
    MV1SetRotationXYZ(_handle, rota_);
}

//-----------------------------------------
// 描画
//-----------------------------------------
void Model::draw()
{
    MV1DrawModel(_handle);
}