#pragma once
#include "Board.h"

class Chess
{
protected:
	Board board;
public:
	virtual void gameStart(void) = 0;
};

class Chess_1 : public Chess
{
public:
	void gameStart() {
		//начало таймера
	}
};

class Chess_2 : public Chess_1
{
private:
	unsigned PassTime; //время хода
public:
	Chess_2(unsigned pass_time = 1200) : PassTime(pass_time) {}
	void setTime(unsigned sec) {
		PassTime = sec;
	}
	//время хода вышло
	int timeEnd(void) {
		//...
	}
	void gameStart(void) {
		//...
	}
};
