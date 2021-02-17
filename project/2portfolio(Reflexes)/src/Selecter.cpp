#include"Selecter.h"
#include"main.h"

//--------------------------------------------
//! 選択枝を出すためのクラス
//--------------------------------------------


//------------------------------------
//! コンストラクタ
//------------------------------------
Selecter::Selecter()
{
	_pos.set(200, 100);

	for (int i = 0; i < SELECT_MAX; i++) {
		_color[i] = 0;
		_fig[i] = 0;
		//! 選択枝の箱のインスタンス
		_selBox[i] = new SelectBox;
	}


	_colorNum = 0;

}

//------------------------------------
//! デストラクタ
//------------------------------------
Selecter::~Selecter()
{
}

//------------------------------------
//! 選択肢を出す
//------------------------------------
void Selecter::setSel()
{
	////! 配列に乱数のサイズ分入れる
	//s16 values[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 , 11, 12};
	////! 実際配列に入っているサイズを出す
	//s16 size = sizeof(values) / sizeof(s16);
	//
	//shuffle(values, size);
	//
	//for (int i = 0; i < SELECT_MAX; i++)
	//_sel[i] = values[i];
	for (int i = 0; i < SELECT_MAX; i++)
		_sel[i] = rand() % 12;
}

//! 図形をランダムで決める
void Selecter::setFig()
{
	for (int i = 0; i < SELECT_MAX; i++) {
		_fig[i] = rand() % 3;

	}

}



//! 同じ数字が出ないように処理する	
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
//! 出た乱数によって問題の配色を決める
//------------------------------------
void Selecter::setCol()
{
	for (int i = 0; i < SELECT_MAX; i++) {
		Base::setCol(sel_color[i], _sel[i], Selecter::_color[i]);
		
	}
}

//------------------------------------
//!	マネージャーで一つだけ問題と一致させる
//------------------------------------
void Selecter::matchToQue(s16 &que_color, s16 &que_figure)
{
	//! そもそも選択肢に答えがあれば終了 
	for (int i = 0; i < SELECT_MAX; i++) {
		if (_color[i] == que_color && _fig[i] == que_figure) {
			return;
		}
	}


	//! 四つの選択肢のなかから1つランダムで選ぶ
	int i = rand() % SELECT_MAX;
	Base::setCol(sel_color[i], que_color, _color[i]);
	_fig[i] = que_figure;



	////! 同じ色と図形が重複するのを防ぐ
	//for (int i = 0; i < SELECT_MAX; i++) {
	//	if (_color[i] == que_color && _fig[i] == que_figure) {
	//
	//	}
	//}

}

//------------------------------------
//! 当たり判定用
//------------------------------------
bool Selecter::hit()
{
	//! debug表示用
	s16 color = 0;
	s16 figure = 0;

	//! debug表示用　
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



#ifdef _DEBUG //! debug用表示

			//! 当たり判定の表示
			DrawString(0, 240, "当たり判定", GetColor(255, 255, 255));
			if (isHit)
				DrawString(0, 260, " hit ", GetColor(255, 255, 255));

			//! 配色番号の表示
			DrawString(0, 280, "選択中の色番号", GetColor(255, 255, 255));
			checgeText(color, 0, 300, 255, 255, 255);

#endif // DEBUG



			return true;
		}

	}
	






	return false;
}

//!--------------------------------------
//! 図形同士が重ならないようにする
//! 図形の上下左右にサイズ分の空きを作る
//!--------------------------------------
bool Selecter::notOverlap(Vector2 &p0, Vector2 &p1)
{

	{
		Vector2 v;
		// p0からp1を引いて円同士の距離を出す
		v.subtract(p0, p1);

		// 判定用
		float length = v.length();

		s16 _size = _selBox[0]->getSize();

		//  最初に出した距離と二つの半径を足したものを比べる
		if (length < _size + _size) {
			//　p0からp1を引いて円同士の距離をのほうが小さければtrue
			return true;
		}

		return false;
	}

}
//------------------------------------
//! 同じ色と同じ形が答え以外にあればSetしなおす
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
//! 更新(selBox)
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




		//! ランダムで決まった情報を渡す
		for (int i = 0; i < SELECT_MAX; i++) {
			//! 配列番号
			_selBox[i]->setCol(_color[i]);
			//! 図形番号
			_selBox[i]->setFigure(_fig[i]);
			//! 色情報
			_selBox[i]->setColor(Selecter::_setColor[i]);

		}

	}
}

//------------------------------------
//! 描画(selBox)
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
//! 初期化
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
//! 更新
//------------------------------------
void Selecter::update(s16 &que_color, s16 &que_figure)
{
	setSel(); //! 選択肢を出す
	setFig(); //! 選択肢の図形設定
	setCol(); //! 出た乱数によって問題の配色を決める
	matchToQue(que_color, que_figure);
	check(que_color, que_figure);
	for (int i = 0; i < SELECT_MAX; i++)
	Base::CheckCol(sel_color[i], Selecter::_setColor[i]);

	
	updateSelBox();
}

//------------------------------------
//! 描画
//------------------------------------
void Selecter::draw()
{
	drawSelBox();
}

//------------------------------------
//! 破棄
//------------------------------------
void Selecter::exit()
{
}

//! 選択枝の箱-------------------------------------------
//------------------------------------
//! コンストラクタ
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
//! デストラクタ
//------------------------------------
SelectBox::~SelectBox()
{
	
	
}

//------------------------------------
//! 四つの箱の位置を決める
//------------------------------------
//void SelectBox::setPos(s16 x, s16 y)
//{
//	_pos.set(x, y);
//}


//ベクトル引き算(a-b)
Vector2 sub_vector(const Vector2& a, const Vector2& b)
{
	Vector2 ret;
	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	return ret;
}

// 三角形と点の当たり判定(2Dの場合)
// 戻り値    0:三角形の内側に点がある    1:三角形の外側に点がある
int hittest_point_polygon_2d(Vector2 A, Vector2 B, Vector2 C, Vector2 P) {

	//線上は外とみなします。
	//ABCが三角形かどうかのチェックは省略...

	Vector2 AB = sub_vector(B, A);
	Vector2 BP = sub_vector(P, B);

	Vector2 BC = sub_vector(C, B);
	Vector2 CP = sub_vector(P, C);

	Vector2 CA = sub_vector(A, C);
	Vector2 AP = sub_vector(P, A);

	//外積    Z成分だけ計算すればよいです
	double c1 = AB.x * BP.y - AB.y * BP.x;
	double c2 = BC.x * CP.y - BC.y * CP.x;
	double c3 = CA.x * AP.y - CA.y * AP.x;

	if ((c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0)) {
		//三角形の内側に点がある
		return 0;
	}

	//三角形の外側に点がある
	return 1;

}
//------------------------------------
//! 当たり判定 
//------------------------------------
s16 SelectBox::hit()
{
	//! マウスの座標
	s16 mouse_x = GetMouseX();
	s16 mouse_y = GetMouseY();
	Vector2 mouse;
	mouse.set(mouse_x, mouse_y);
	//! 三角用
	Vector2 tpos1;
	Vector2 tpos2;
	Vector2 tpos3;
	tpos1.set(_pos.x, _pos.y - _size / 2);
	tpos2.set(_pos.x - (_size * 0.8), _pos.y + (_size * 0.8));
	tpos3.set(_pos.x + (_size * 0.8), _pos.y + (_size * 0.8));

	


	//! 図形設定用
	switch (_figure)
	{
	case 0:  //! 円
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

	case 1:  //! 三角
		if (hittest_point_polygon_2d(tpos1, tpos2, tpos3, mouse))
		{
			_isFrame = false;
		}
		else
		{
			
			_isFrame = true;
			return true;
		}

	case 2:  //! 四角

		//! 当たってるかどうか
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




	

#ifdef _DEBUG //! debug用表示

	//! マウス座標の表示
	DrawString(0, 180, "マウス座標（ｘ、ｙ）", GetColor(255, 255, 255));
	checgeText(mouse_x, 0, 200, 255, 255, 255);
	checgeText(mouse_y, 0, 220, 255, 255, 255);

#endif // DEBUG

	return false;
}

//------------------------------------
//! 色を持たせる
//------------------------------------
void SelectBox::setCol(s16 color)
{
	_color = color;
}

//----------------------------------------
//! ランダムで一設定するときの枠を定める
//!（範囲内ならTRUE）
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
//! 場所をランダムで設定 
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
//! 描画 
//------------------------------------
void SelectBox::Draw()
{

	

	//! 図形設定用
	switch (_figure)
	{
	case 0:  //! 円
		DrawCircle(_pos.x, _pos.y, (_size * 0.8) ,_setColor);
		if (_isFrame)
			DrawCircle(_pos.x, _pos.y, (_size * 0.8), GetColor(0, 255, 0) , false);

		break;

	case 1:  //! 三角
		DrawTriangle(_pos.x, _pos.y - _size / 2, _pos.x - (_size * 0.8), _pos.y + (_size * 0.8), _pos.x + (_size * 0.8), _pos.y + (_size * 0.8), _setColor, true);
		if (_isFrame)
			DrawTriangle(_pos.x, _pos.y - _size / 2, _pos.x - (_size * 0.8), _pos.y + (_size * 0.8), _pos.x + (_size * 0.8), _pos.y + (_size * 0.8), GetColor(0, 255, 0), false);
		break;

	case 2:  //! 四角
		DrawBox(_pos.x, _pos.y, _pos.x + _size, _pos.y + _size, _setColor, true);
		if (_isFrame)
			DrawBox(_pos.x, _pos.y, _pos.x + _size, _pos.y + _size, GetColor(0, 255, 0), false);
		break;

	default:
		break;
	}


#ifdef _DEBUG

	//! 微調整用
	s16 text_x = _pos.x + _size / 2;
	s16 text_y = _pos.y + _size / 2;
	checgeText(_color, text_x, text_y, 255, 255, 255);
#endif // _DEBUG


}

