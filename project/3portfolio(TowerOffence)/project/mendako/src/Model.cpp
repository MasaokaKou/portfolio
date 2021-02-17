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
// ���f���̓ǂݍ���
//-----------------------------------------
void Model::load(const char* fileName_)
{
    _handle = MV1LoadModel(&*fileName_);
}

//-----------------------------------------
// ���f���̍��W�ݒ�
//-----------------------------------------
void Model::setPos(VECTOR pos_)
{
    MV1SetPosition(_handle, pos_);
}

//-----------------------------------------
// ���f���̔{���ύX
//-----------------------------------------
void Model::setScale(VECTOR scale_)
{
    MV1SetScale(_handle, scale_);
}

//-----------------------------------------
// ��]
//-----------------------------------------
void Model::setRota(VECTOR rota_)
{
    MV1SetRotationXYZ(_handle, rota_);
}

//-----------------------------------------
// �`��
//-----------------------------------------
void Model::draw()
{
    MV1DrawModel(_handle);
}