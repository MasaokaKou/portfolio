#pragma once


class Player;

class Block {
public:
	Block();
	~Block();

    void Draw();
    void Hit(Player *player);
	void Set(int x, int y,int num);

private:
	int _x,_y;
	int _x2, _y2;



};