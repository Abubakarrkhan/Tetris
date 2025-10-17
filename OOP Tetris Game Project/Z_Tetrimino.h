#pragma once
#include"Tetrimino.h"

class Z_Tetrimino :public Tetrimino
{
public:
	virtual void Set();
	string getcolor() override;
};
