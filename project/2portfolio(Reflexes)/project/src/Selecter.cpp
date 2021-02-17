#include"Selecter.h"
#include"main.h"

//--------------------------------------------
//! �I���}���o�����߂̃N���X
//--------------------------------------------


//------------------------------------
//! �R���X�g���N�^
//------------------------------------
Selecter::Selecter()
{
	_pos.set(200, 100);

	for (int i = 0; i < SELECT_MAX; i++) {
		_color[i] = 0;
		_fig[i] = 0;
		//! �I���}�̔��̃C���X�^���X
		_selBox[i] = new SelectBox;
	}


	_colorNum = 0;

}

//------------------------------------
//! �f�X�g���N�^
//------------------------------------
Selecter::~Selecter()
{
}

//------------------------------------
//! �I�������o��
//------------------------------------
void Selecter::setSel()
{
	////! �z��ɗ����̃T�C�Y�������
	//s16 values[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 , 11, 12};
	////! ���۔z��ɓ����Ă���T�C�Y���o��
	//s16 size = sizeof(values) / sizeof(s16);
	//
	//shuffle(values, size);
	//
	//for (int i = 0; i < SELECT_MAX; i++)
	//_sel[i] = values[i];
	for (int i = 0; i < SELECT_MAX; i++)
		_sel[i] = rand() % 12;
}

//! �}�`�������_���Ō��߂�
void Selecter::setFig()
{
	for (int i = 0; i < SELECT_MAX; i++) {
		_fig[i] = rand() % 3;

	}

}



//! �����������o�Ȃ��悤�ɏ�������	
void Selecter::shuffle(s16 ary[], s16 size)
{

	{
		for (int i = 0; i < size; i++) {
			int j = rand() % size;
			int t = ary[i];
			ary[i] = ary[j];
			ary[j] = t;
		}
	}
}

//------------------------------------
//! �o�������ɂ���Ė��̔z�F�����߂�
//------------------------------------
void Selecter::setCol()
{
	for (int i = 0; i < SELECT_MAX; i++) {
		Base::setCol(sel_color[i], _sel[i], Selecter::_color[i]);
		
	}
}

//------------------------------------
//!	�}�l�[�W���[�ň�������ƈ�v������
//------------------------------------
void Selecter::matchToQue(s16 &que_color, s16 &que_figure)
{
	//! ���������I�����ɓ���������ΏI�� 
	for (int i = 0; i < SELECT_MAX; i++) {
		if (_color[i] == que_color && _fig[i] == que_figure) {
			return;
		}
	}


	//! �l�̑I�����̂Ȃ�����1�����_���őI��
	int i = rand() % SELECT_MAX;
	Base::setCol(sel_color[i], que_color, _color[i]);
	_fig[i] = que_figure;



	////! �����F�Ɛ}�`���d������̂�h��
	//for (int i = 0; i < SELECT_MAX; i++) {
	//	if (_color[i] == que_color && _fig[i] == que_figure) {
	//
	//	}
	//}

}

//------------------------------------
//! �����蔻��p
//------------------------------------
bool Selecter::hit()
{
	//! debug�\���p
	s16 color = 0;
	s16 figure = 0;

	//! debug�\���p�@
	bool isHit = false;

	for (int i = 0; i < SELECT_MAX; i++)
	{
		if (_selBox[i]->hit())
		{
			isHit = true;
			color = _selBox[i]->getColor();
			figure = _selBox[i]->getFigureNum();
		
			_colorNum = color;
			_figureNum = figure;



#ifdef _DEBUG //! debug�p�\��

			//! �����蔻��̕\��
			DrawString(0, 240, "�����蔻��", GetColor(255, 255, 255));
			if (isHit)
				DrawString(0, 260, " hit ", GetColor(255, 255, 255));

			//! �z�F�ԍ��̕\��
			DrawString(0, 280, "�I�𒆂̐F�ԍ�", GetColor(255, 255, 255));
			checgeText(color, 0, 300, 255, 255, 255);

#endif // DEBUG



			return true;
		}

	}
	






	return false;
}

//!--------------------------------------
//! �}�`���m���d�Ȃ�Ȃ��悤�ɂ���
//! �}�`�̏㉺���E�ɃT�C�Y���̋󂫂����
//!--------------------------------------
bool Selecter::notOverlap(Vector2 &p0, Vector2 &p1)
{

	{
		Vector2 v;
		// p0����p1�������ĉ~���m�̋������o��
		v.subtract(p0, p1);

		// ����p
		float length = v.length();

		s16 _size = _selBox[0]->getSize();

		//  �ŏ��ɏo���������Ɠ�̔��a�𑫂������̂��ׂ�
		if (length < _size + _size) {
			//�@p0����p1�������ĉ~���m�̋������̂ق������������true
			return true;
		}

		return false;
	}

}
//------------------------------------
//! �����F�Ɠ����`�������ȊO�ɂ����Set���Ȃ���
//------------------------------------
void Selecter::check(s16 &que_color, s16 &que_figure)
{
	s16 hit = 0;
	for (s16 i = 0; i < SELECT_MAX; i++)
	{
		if (hit >= 1 && _color[i] == que_color && _fig[i] == que_figure)
		{
			while (true)
			{
				Base::setCol(sel_color[i], _sel[i], Selecter::_color[i]);
				_fig[i] = rand() % 3;
				if (_color[i] != que_color || _fig[i] != que_figure) {
					break;
				}
			}
		
		}

		if (_color[i] == que_color && _fig[i] == que_figure)
		{
			hit++;
			
		}
		

	}

}

//------------------------------------
//! �X�V(selBox)
//------------------------------------
void Selecter::updateSelBox()
{
	if (_selBox != nullptr)// nullCheck
	{

		s16 size = _selBox[0]->getSize();


		for (int i = 0; i < SELECT_MAX; ++i) {
			_selBox[i]->setPos();
		}

		// atarihantei,itisettei
		for (int i = 0; i < SELECT_MAX; ++i) {
			for (int j = 0; j < SELECT_MAX; ++j) {
				if (i == j)  continue;
				if (notOverlap(_selBox[i]->getPos(), _selBox[j]->getPos())) {
					_selBox[i]->setPos();
					_selBox[j]->setPos();
					i = j = 0;
				}
			}
		}

		/*while (true)
		{
			for (int i = 0; i < SELECT_MAX; i++)
				_selBox[i]->setPos();

			if (!notOverlap(_selBox[0]->getPos(), _selBox[1]->getPos()) &&
				!notOverlap(_selBox[0]->getPos(), _selBox[2]->getPos()) &&
				!notOverlap(_selBox[0]->getPos(), _selBox[3]->getPos()) &&
				!notOverlap(_selBox[0]->getPos(), _selBox[4]->getPos()) &&
				!notOverlap(_selBox[0]->getPos(), _selBox[5]->getPos()) &&

				!notOverlap(_selBox[1]->getPos(), _selBox[2]->getPos()) &&
				!notOverlap(_selBox[1]->getPos(), _selBox[3]->getPos()) &&
				!notOverlap(_selBox[1]->getPos(), _selBox[4]->getPos()) &&
				!notOverlap(_selBox[1]->getPos(), _selBox[5]->getPos()) &&

				!notOverlap(_selBox[2]->getPos(), _selBox[3]->getPos()) &&
				!notOverlap(_selBox[2]->getPos(), _selBox[4]->getPos()) &&
				!notOverlap(_selBox[2]->getPos(), _selBox[5]->getPos()) &&

				!notOverlap(_selBox[3]->getPos(), _selBox[4]->getPos()) &&
				!notOverlap(_selBox[3]->getPos(), _selBox[5]->getPos()) &&

				!notOverlap(_selBox[4]->getPos(), _selBox[5]->getPos())
				)
				break;

		}*/




		//! �����_���Ō��܂�������n��
		for (int i = 0; i < SELECT_MAX; i++) {
			//! �z��ԍ�
			_selBox[i]->setCol(_color[i]);
			//! �}�`�ԍ�
			_selBox[i]->setFigure(_fig[i]);
			//! �F���
			_selBox[i]->setColor(Selecter::_setColor[i]);

		}

	}
}

//------------------------------------
//! �`��(selBox)
//------------------------------------
void Selecter::drawSelBox()
{
	if (_selBox)// nullCheck
	{
		for (int i = 0; i < SELECT_MAX; i++)
			_selBox[i]->Draw();
	}

}

//------------------------------------
//! ������
//------------------------------------
bool Selecter::initialize()
{

	for (int i = 0; i < SELECT_MAX; i++)
	{
		_sel[i] = 0;
	}

	return true;

}

//------------------------------------
//! �X�V
//------------------------------------
void Selecter::update(s16 &que_color, s16 &que_figure)
{
	setSel(); //! �I�������o��
	setFig(); //! �I�����̐}�`�ݒ�
	setCol(); //! �o�������ɂ���Ė��̔z�F�����߂�
	matchToQue(que_color, que_figure);
	check(que_color, que_figure);
	for (int i = 0; i < SELECT_MAX; i++)
	Base::CheckCol(sel_color[i], Selecter::_setColor[i]);

	
	updateSelBox();
}

//------------------------------------
//! �`��
//------------------------------------
void Selecter::draw()
{
	drawSelBox();
}

//------------------------------------
//! �j��
//------------------------------------
void Selecter::exit()
{
}

//! �I���}�̔�-------------------------------------------
//------------------------------------
//! �R���X�g���N�^
//------------------------------------

SelectBox::SelectBox()
{
	_pos.clear();
	_size = 50;
	_color = 0;
	_isFrame = false;
	_figure = 0;
	_setColor = GetColor(0, 0, 0);

}
//------------------------------------
//! �f�X�g���N�^
//------------------------------------
SelectBox::~SelectBox()
{
	
	
}

//------------------------------------
//! �l�̔��̈ʒu�����߂�
//------------------------------------
//void SelectBox::setPos(s16 x, s16 y)
//{
//	_pos.set(x, y);
//}


//�x�N�g�������Z(a-b)
Vector2 sub_vector(const Vector2& a, const Vector2& b)
{
	Vector2 ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	return ret;
}

// �O�p�`�Ɠ_�̓����蔻��(2D�̏ꍇ)
// �߂�l    0:�O�p�`�̓����ɓ_������    1:�O�p�`�̊O���ɓ_������
int hittest_point_polygon_2d(Vector2 A, Vector2 B, Vector2 C, Vector2 P) {

	//����͊O�Ƃ݂Ȃ��܂��B
	//ABC���O�p�`���ǂ����̃`�F�b�N�͏ȗ�...

	Vector2 AB = sub_vector(B, A);
	Vector2 BP = sub_vector(P, B);

	Vector2 BC = sub_vector(C, B);
	Vector2 CP = sub_vector(P, C);

	Vector2 CA = sub_vector(A, C);
	Vector2 AP = sub_vector(P, A);

	//�O��    Z���������v�Z����΂悢�ł�
	double c1 = AB.x * BP.y - AB.y * BP.x;
	double c2 = BC.x * CP.y - BC.y * CP.x;
	double c3 = CA.x * AP.y - CA.y * AP.x;

	if ((c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0)) {
		//�O�p�`�̓����ɓ_������
		return 0;
	}

	//�O�p�`�̊O���ɓ_������
	return 1;

}
//------------------------------------
//! �����蔻�� 
//------------------------------------
s16 SelectBox::hit()
{
	//! �}�E�X�̍��W
	s16 mouse_x = GetMouseX();
	s16 mouse_y = GetMouseY();
	Vector2 mouse;
	mouse.set(mouse_x, mouse_y);
	//! �O�p�p
	Vector2 tpos1;
	Vector2 tpos2;
	Vector2 tpos3;
	tpos1.set(_pos.x, _pos.y - _size / 2);
	tpos2.set(_pos.x - (_size * 0.8), _pos.y + (_size * 0.8));
	tpos3.set(_pos.x + (_size * 0.8), _pos.y + (_size * 0.8));

	


	//! �}�`�ݒ�p
	switch (_figure)
	{
	case 0:  //! �~
		if(mouse_x <= _pos.x + (_size * 0.8) && mouse_x >= _pos.x - (_size * 0.8) &&
			mouse_y>= _pos.y - (_size * 0.8) && mouse_y <= _pos.y + (_size * 0.8))
		{
			_isFrame = true;
			return true;
		}
		else
		{
			_isFrame = false;
		}
		break;

	case 1:  //! �O�p
		if (hittest_point_polygon_2d(tpos1, tpos2, tpos3, mouse))
		{
			_isFrame = false;
		}
		else
		{
			
			_isFrame = true;
			return true;
		}

	case 2:  //! �l�p

		//! �������Ă邩�ǂ���
		if (_pos.x <= mouse_x && _pos.x + _size >= mouse_x
			&& _pos.y <= mouse_y && _pos.y + _size >= mouse_y)
		{
			_isFrame = true;
			return true;
		}
		else
		{
			_isFrame = false;
		}

		break;

	default:
		break;
	}




	

#ifdef _DEBUG //! debug�p�\��

	//! �}�E�X���W�̕\��
	DrawString(0, 180, "�}�E�X���W�i���A���j", GetColor(255, 255, 255));
	checgeText(mouse_x, 0, 200, 255, 255, 255);
	checgeText(mouse_y, 0, 220, 255, 255, 255);

#endif // DEBUG

	return false;
}

//------------------------------------
//! �F����������
//------------------------------------
void SelectBox::setCol(s16 color)
{
	_color = color;
}

//----------------------------------------
//! �����_���ň�ݒ肷��Ƃ��̘g���߂�
//!�i�͈͓��Ȃ�TRUE�j
//----------------------------------------
bool SelectBox::frameChecker(Vector2 pos_)
{

	s16 x1 = 170;
	s16 y1 = 70;

	s16 x2 = 570;
	s16 y2 = 400;

	if (pos_.x >= x1 && pos_.x <= x2
		&& pos_.y >= y1 && pos_.y <= y2)
	{
		return true;
	}

	return false;
}





//------------------------------------
//! �ꏊ�������_���Őݒ� 
//------------------------------------
void SelectBox::setPos()
{

	while (true)
	{
		_pos.x = rand() % 640;
		_pos.y = rand() % 480;

		if (frameChecker(_pos)) {

			break;
		}
	}


}

//------------------------------------
//! �`�� 
//------------------------------------
void SelectBox::Draw()
{

	

	//! �}�`�ݒ�p
	switch (_figure)
	{
	case 0:  //! �~
		DrawCircle(_pos.x, _pos.y, (_size * 0.8) ,_setColor);
		if (_isFrame)
			DrawCircle(_pos.x, _pos.y, (_size * 0.8), GetColor(0, 255, 0) , false);

		break;

	case 1:  //! �O�p
		DrawTriangle(_pos.x, _pos.y - _size / 2, _pos.x - (_size * 0.8), _pos.y + (_size * 0.8), _pos.x + (_size * 0.8), _pos.y + (_size * 0.8), _setColor, true);
		if (_isFrame)
			DrawTriangle(_pos.x, _pos.y - _size / 2, _pos.x - (_size * 0.8), _pos.y + (_size * 0.8), _pos.x + (_size * 0.8), _pos.y + (_size * 0.8), GetColor(0, 255, 0), false);
		break;

	case 2:  //! �l�p
		DrawBox(_pos.x, _pos.y, _pos.x + _size, _pos.y + _size, _setColor, true);
		if (_isFrame)
			DrawBox(_pos.x, _pos.y, _pos.x + _size, _pos.y + _size, GetColor(0, 255, 0), false);
		break;

	default:
		break;
	}


#ifdef _DEBUG

	//! �������p
	s16 text_x = _pos.x + _size / 2;
	s16 text_y = _pos.y + _size / 2;
	checgeText(_color, text_x, text_y, 255, 255, 255);
#endif // _DEBUG


}

