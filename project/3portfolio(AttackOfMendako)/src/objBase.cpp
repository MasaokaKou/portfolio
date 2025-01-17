//---------------------------------------------------------------------------
//!	@file	objBase.cpp
//!	@brief	オブジェクトの基礎
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//! 座標設定
//---------------------------------------------------------------------------
void BaseObject::setPos(VECTOR pos_)
{
    _pos = VGet(pos_.x, pos_.y, pos_.z);
}

//---------------------------------------------------------------------------
//! ステータスを取ってくる
//---------------------------------------------------------------------------
STATE BaseObject::state()
{
    return _state;
}

//---------------------------------------------------------------------------
//! 索敵用当たり判定
//---------------------------------------------------------------------------
bool BaseObject::hit(VECTOR& p0_, f32 r0_, VECTOR& p1_, f32 r1_)
{
    VECTOR v;
    // p0からp1を引いて円同士の距離を出す
    v = VSub(p0_, p1_);

    // 判定用
    f32 length = sqrtf(v.x * v.x + v.z * v.z);

    //  最初に出した距離と二つの半径を足したものを比べる
    if(length < (r0_ + r1_)) {
        //　p0からp1を引いて円同士の距離をのほうが小さければtrue
        return true;
    }

    return false;
}

//---------------------------------------------------------------------------
//! HPの上限
//---------------------------------------------------------------------------
s16 BaseObject::HP()
{
    return _HP;
}