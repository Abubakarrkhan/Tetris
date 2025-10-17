#pragma once
#include"Tetrimino.h"

class I_Tetrimino :public Tetrimino
{
public:
	virtual void Set();
	string getcolor() override;
};
