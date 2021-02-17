#pragma once
#include"Typedef.h"
#include"Vector2.h"
const s16 SELECT_MAX = 6;


//-------------------------
//!�z�F
//-------------------------

enum class SELECT
{


	BLUE,
	PURPLE,
	RED,
	PINK,
	ORANGE,
	YELLOW,
	YELLOWGREEN,
	GREEN,
	LIGHTBLUE,
	LIGHTOLANGE,
	WHITE,
	BROWN

};





//-------------------------
//!���N���X
//-------------------------

class Base
{
public:
	Base();
	virtual~Base();

	//! �o�������ɂ���Ė��̔z�F�����߂�
	virtual void setCol(SELECT &color, s16 obj, s16 &colorNum);
	//! �o�������ɂ���Ė��̔z�F����
	virtual void CheckCol(SELECT &color, u64 &setColor_);

	bool initialize();  //! ������
	void update();		//! �X�V
	void draw();		//! �`��
	void exit();		//! �j��



protected:


	s16 _que;               //! ���
	s16 _sel[SELECT_MAX];   //! �I���}
	s16 _fig[SELECT_MAX];   //! �I���}�̐}�`
	s16 _ans;				//! ����

	Vector2 _pos;				//! ���̈ʒu
	s16     _size;              //! ���̑傫��
	s16     _color[SELECT_MAX]; //! ���̐F
	
	u64		_setColor[SELECT_MAX];			//! �F�̂��Ă͂�


								// �z�F�p�񋓑�
	SELECT sel_COLOR[SELECT_MAX];
	



};

