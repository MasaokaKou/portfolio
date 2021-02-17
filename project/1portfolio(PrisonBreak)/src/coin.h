#pragma once
class Coin {
private:
	int coin_image;
	int coin_x;
	int coin_y;
	
	bool score;

	float collect_x;
	float collect_y;

	int orbit_image;

	int orbit_alpha;

	int p_x;
	int p_y;
	int p0_x;
	int p0_y;
	int p1_x;
	int p1_y;
	int p2_x;
	int p2_y;
	float t;
	float orbit_v;
	float orbit_gravity;
	int coin_point;
	int orbit_counter;
	bool orbit_check;
	const int coin_max;
	const int coin_W;
	const int coin_H;

	float size;
	float rota;
	int counter_in_result;

	//集計用のコインポイント変数
	int sum_point;

public:
	Coin();
	~Coin();
	void Load();
	void SetOrbit();
	void SetOrbit2();
	void SetOrbit3(int i);
	void DrawOrbit();

	void SetCoin(int x,int y);
	void DrawCoin();
	void CoinMove();
	
	void AddOrbitCount();
	void AddCoinPoint();
	void AddMoveCounterInResult();
	void GettedCoin();
	
	void DrawCollect();
	void DrawCollected(int i);
	void DrawInResult(int i);
	void MoveInResult();
	int GetResultCounter() { return counter_in_result; };


	bool GetScore();
	void  SetScore(bool sc);
	void ChengeScore();

	bool is_get;
	void ChengeCollectSpeed();
	void SetCollectBox();
	void ResetPoint();
	float orbit_x;
	float orbit_y;

	void ResetAlpha() { orbit_alpha = 255; }

	void SeInResult(int i);
	void ResetInResult() { counter_in_result = 0; size = 1.8f;rota = 0.0f;}

	void SumPoint();
	int GetSum() { return sum_point; }
	void ResetSum() { sum_point = 0; }

	//debug
	int GetC() { return orbit_counter; }



	int GetCoinPoint() { return coin_point; }

};