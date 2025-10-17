#include "O_Tetrimino.h"
void O_Tetrimino::Set()
{
	int Structure[4][4] =
	{
		{ 1, 1, 0, 0 },
		{ 1, 1, 0, 0 },
		{ 0, 0, 0, 0 },
		{ 0, 0, 0, 0 }
	};
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			tetrimino[i][j] = Structure[i][j];

	if (!(TetrisBlock.loadFromFile("O_Tetrimino.png")))
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
void O_Tetrimino::rotate()
{

}
string O_Tetrimino::getcolor()
{
	return "yellow";
}