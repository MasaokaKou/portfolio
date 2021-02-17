
#pragma once
#include"Base.h"

//------------------------------------
//! �I���}���o�����߂̃N���X
//------------------------------------

// �I���}�̔�
class SelectBox
{
public:
	SelectBox();
	~SelectBox();

	////! �l�̔��̈ʒu�����߂�
	//void setPos(s16 x, s16 y);
	
	
	//! �����_���ň�ݒ肷��Ƃ��̘g���߂�
	bool  frameChecker(Vector2 pos_);

	
	//! �ꏊ�������_���Őݒ� 
	void setPos();




	//! �����蔻�� 
	s16 hit();

	//! �`��
	void Draw();

	// BOX�̈ʒu�擾�p
	Vector2 getPos() { return _pos; }

	// BOX�̃T�C�Y�擾�p
	s16 getSize() { return _size; }

	// �F����������
	void setCol(s16 color);
	// �F��Ԃ�
	s16 getColor() { return _color; }

	//! �}�`�̃Z�b�g
	void setFigure(s16 figure_) { _figure = figure_; }
	void setColor(u64 color_) { _setColor = color_; }

	//! �}�`�̃Q�b�^�[
	s16 getFigureNum() { return _figure; }


private:
	Vector2  _pos;
	s16      _size; //! �}�`�̃T�C�Y
	s16      _color;//! �z�F�ԍ�

	s16      _figure; //! �}�`�ݒ�p�ϐ�
	u64      _setColor; //! �F���

	//! �I��p�t���[���̗L��
	bool    _isFrame;
};


class Selecter
	:Base
	
{
public:
	Selecter();
	~Selecter();

	bool initialize();									//! ������
	void update(s16 &que_color, s16 &que_figure);		//! �X�V
	void draw();										//! �`��
	void exit();										//! �j��

	void updateSelBox();	//! selBox�`��
	void drawSelBox();	    //! selBox�`��


	//! �I�������o��
	void setSel();
	//! �����������o�Ȃ��悤�ɏ�������	
	void shuffle(s16 ary[], s16 size);
	
	//! �o�������ɂ���Ė��̔z�F�����߂�
	void setCol();

	//! �}�`�������_���Ō��߂�
	void setFig();

	//! ��������ƈ�v������
	void matchToQue(s16 &que_color, s16 &que_figure);

	//! �����蔻��p
	bool hit();

	//! �}�`���m���d�Ȃ�Ȃ��悤�ɂ���
//! �}�`�̏㉺���E�ɃT�C�Y���̋󂫂����
	bool notOverlap(Vector2 &p0, Vector2 &p1);

	//! �����F�Ɠ����`�������ȊO�ɂ����Set���Ȃ���
	void check(s16 &que_color, s16 &que_figure);

	s16 getColorNum() { return _colorNum; }
	s16 getFigureNum() { return _figureNum; }
	
private:
	//! �z�F�ԍ���Ԃ�
	s16 _colorNum;
	//! �}�`�ԍ���Ԃ�
	s16 _figureNum;

	SELECT sel_color[SELECT_MAX];


	//! �I���}�̔��̃C���X�^���X
	SelectBox * _selBox[SELECT_MAX];

	
};


