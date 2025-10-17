#include "Tetrimino.h"

Tetrimino::Tetrimino()
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			tetrimino[i][j] = 0;
	Blockscount = 0;
}
void Tetrimino:: Load()
{
	for (int i = 0; i < Blockscount; i++) ////blockscount = 4
	{
		sf::Sprite sprite;
		sprite.setTexture(TetrisBlock);
		tetris.push_back(sprite); // will be a vector of size 4 which will have 4 blocks of sprite (stored) 

		float a = TetrisBlocksPos[i].getX();// this will get the x-axis position of the block wrt to window
		float b = TetrisBlocksPos[i].getY();// this will get the y-axis position of the block wrt to window
		tetris[i].setPosition(a, b);// set their position 
	}
}
void Tetrimino::rotate()
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
	Point cloneP = clonePos[1]; // center of rotation
	for (int i = 0; i < Blockscount; i++)
	{
		// a formula for rotation
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
		Point p = TetrisBlocksPos[1]; // center of rotation
		for (int i = 0; i < Blockscount; i++)
		{
			float y = TetrisBlocksPos[i].getY() - p.getY();
			float x = TetrisBlocksPos[i].getX() - p.getX();
			float NewX = p.getX() - y;
			float NewY = p.getY() + x;

			TetrisBlocksPos[i].SetX(NewX);
			TetrisBlocksPos[i].SetY(NewY);
		}

		Load();// calling load to change sprite position
	}
}

void Tetrimino::MoveLeft()
{
	bool collision = false;

	// Check if any block would go out of bounds after moving left
	for (int i = 0; i < Blockscount; i++)
	{


		if (TetrisBlocksPos[i].getX() - 40 < 0)  // assuming 40 is block width
		{
			collision = true;
			break;
		}
	}
	if (!collision)
	{
		for (int i = 0; i < Blockscount; i++)
		{
			float x = TetrisBlocksPos[i].getX() - 40;//// move all block 40 px left
			TetrisBlocksPos[i].SetX(x);
		}
	}
	Load();// calling load to change sprite position
}

void Tetrimino::MoveRight()
{
	bool collision = false;

	for (int i = 0; i < Blockscount; i++)
	{
		if (TetrisBlocksPos[i].getX() +40/*width of sprite*/ + 40/*adding 40 to check if do not go out of bound on press*/ > 400)  // assuming 40 is block size
		{
			collision = true;
			break;
		}
	}
	if (!collision)
	{
		for (int i = 0; i < Blockscount; i++)
		{
			float x = TetrisBlocksPos[i].getX() + 40;// move all block 40 px right
			TetrisBlocksPos[i].SetX(x);
		}
	}
	Load();// calling load to change sprite position
}

bool Tetrimino::MoveDown()
{
	for (int i = 0; i < Blockscount; i++)
	{

		if (TetrisBlocksPos[i].getY() + 40/*hight of sprite*/ + 40/*Block size*/ > 800)  // e
		{
			return false;
		}
	}

	for (int i = 0; i < Blockscount; i++)
	{
		float y = TetrisBlocksPos[i].getY() + 40;// move all block 40 px down
		TetrisBlocksPos[i].SetY(y);
	}

	Load();// calling load to change sprite position
	return true;
}


sf::Sprite& Tetrimino::getSprite(const int& i)// used in main function for window.draw
{
	return tetris[i];
}
int Tetrimino::getTetrisPiecePosX(const int& i)
{
	return TetrisBlocksPos[i].getX();
}
int Tetrimino::getTetrisPiecePosY(const int& j)
{
	return TetrisBlocksPos[j].getY();
}
int Tetrimino::getBlocksCount()
{
	return Blockscount;
}