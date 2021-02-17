#pragma once

class Score {
public:
	Score();
	~Score();

	void AddCount();
	void Add();
	void AddTime();


	void Reset();
	void Show();
	void ShowResult();
	void AddEnemyScore();
	void AddCoinScore();
	void GiveData1();
	void ResetData();

	int GetScore() { return _score; }
	int GetTime() { return _time; }
	void SetScore(int num) { _score = num; }
private:
	int _score;
	int _counter;
	int _time;

	int _re_score;
	int _re_time;

};