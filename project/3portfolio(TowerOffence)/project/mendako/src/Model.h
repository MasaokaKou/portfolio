#pragma once

class Model
{
public:
	Model();
	~Model();

	// モデルの読み込み
	void load( const  char * fileName_);
	// モデルの削除
	void exit();
	// モデルの座標設定
	void setPos(VECTOR pos_);
	// モデルの回転
	void setRota(VECTOR rota_);

	// モデルの倍率変更
	void setScale(VECTOR scale_);

	void init();
	// モデルの描画
	void draw();

	// モデルハンドル取得
	int handle() { return _handle; }


private:
	// モデルのハンドル
	int _handle;
	// ファイル名
	const  char * _fileName;


};
