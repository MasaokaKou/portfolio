#pragma once
//--------------------------------------------
//!駒のマネージャー
//!ベースの駒に三種類を振り当てる
//--------------------------------------------
#include"BasePiece.h"
#include<vector>


class PieceManager
{
public:
	PieceManager();
	~PieceManager();
	
	// ベースピースを５つ生成
	void createEmpty();

	// 駒の初期座標設定
	void setPos();

	// 三種類の役割を５つの駒に振りあてる
	void setRole(int pieceNum, int role);
	void applyRole();

	// 当たり判定
	void hitCheck();

	// 駒の描画
	void DrawPiece();

	// 全体の更新
	void update();
private:
	// ベースのピース、これをほかのピースにnewする
	std::vector<BasePiece*> _pieces;

	bool _initialize; // 初期化フラグ

};

