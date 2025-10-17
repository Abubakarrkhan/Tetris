#pragma once
#include"Tetrimino.h"

class L_Tetrimino :public Tetrimino
{
public:
	virtual void Set();
	string getcolor() override;
};
