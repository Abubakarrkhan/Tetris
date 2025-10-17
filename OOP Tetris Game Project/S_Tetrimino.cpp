#include "S_Tetrimino.h"
void S_Tetrimino::Set()
{
	int Structure[4][4] =
	{
		{ 0, 1, 1, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	};
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			tetrimino[i][j] = Structure[i][j];

	if (!(TetrisBlock.loadFromFile("S_Tetrimino.png")))
	{
		cerr << "Error loading file !!!";
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (tetrimino[i][j] == 1)
			{
				//convert matrix points to the point to window format
				TetrisBlocksPos[Blockscount++].SetPoint((float)i, (float)j);//this will store the Position of all 4 block that makes a whole tetris piece 
			}
		}
	}
	Load();// call load to display sprites
}
void S_Tetrimino::rotate()
{
	//first making a clone rotation to check that after rotation any position gets out of bound
	bool Rotation = true;
	Point clonePos[4];
	for (int i = 0; i < Blockscount; i++)
	{
		float x = TetrisBlocksPos[i].getX();
		float y = TetrisBlocksPos[i].getY();
		clonePos[i].SetX(x);
		clonePos[i].SetY(y);
	}
	Point cloneP = clonePos[0]; // center of rotation is point 0
	for (int i = 0; i < Blockscount; i++)
	{
		float y = clonePos[i].getY() - cloneP.getY();
		float x = clonePos[i].getX() - cloneP.getX();
		float NewX = cloneP.getX() - y;
		float NewY = cloneP.getY() + x;
		if (NewX < 0 || NewX>360 || NewY < 0 || NewY>760)
		{
			Rotation = false;
			break;
		}
	}
	if (Rotation)
	{
		Point p = TetrisBlocksPos[0]; // center of rotation
		for (int i = 0; i < Blockscount; i++)
		{
			float y = TetrisBlocksPos[i].getY() - p.getY();
			float x = TetrisBlocksPos[i].getX() - p.getX();
			float NewX = p.getX() - y;
			float NewY = p.getY() + x;

			TetrisBlocksPos[i].SetX(NewX);
			TetrisBlocksPos[i].SetY(NewY);
		}
		Load();
	}
}
string S_Tetrimino::getcolor() 
{
	return "green";
}