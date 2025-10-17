#pragma once
#include"Tetrimino.h"

class T_Tetrimino :public Tetrimino
{
public:
	virtual void Set();
	string getcolor() override;
};
