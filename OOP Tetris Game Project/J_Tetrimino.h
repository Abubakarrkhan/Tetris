#pragma once
#include"Tetrimino.h"

class J_Tetrimino :public Tetrimino
{
public:
	virtual void Set();
	string getcolor() override;
};

