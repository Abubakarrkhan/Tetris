#pragma once
#include"Tetrimino.h"

class S_Tetrimino :public Tetrimino
{
public:
	virtual void Set();
	void rotate() override;
	string getcolor() override;
};

