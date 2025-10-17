#include "GameBoard.h"
GameBoard::GameBoard() :currentLevel(0),TotalLinesCleared(0), rows(20), cols(10), BackgroundSprites(rows, vector<sf::Sprite>(cols))// constructor assign data members values
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            BackgroundMatrix[i][j] = 0;// initialize all gameboard occupied location to 0 
        }
    }
    BackgroundDefaultTexture.loadFromFile("BackGroundGrid.png");


	//filling the texture vector array
    TextureStore.push_back(sf::Texture());
    TextureStore.back().loadFromFile("I_Tetrimino.png");

    TextureStore.push_back(sf::Texture());
    TextureStore.back().loadFromFile("J_Tetrimino.png");

    TextureStore.push_back(sf::Texture());
    TextureStore.back().loadFromFile("L_Tetrimino.png");

    TextureStore.push_back(sf::Texture());
    TextureStore.back().loadFromFile("O_Tetrimino.png");

    TextureStore.push_back(sf::Texture());
    TextureStore.back().loadFromFile("S_Tetrimino.png");

    TextureStore.push_back(sf::Texture());
    TextureStore.back().loadFromFile("T_Tetrimino.png");

    TextureStore.push_back(sf::Texture());
    TextureStore.back().loadFromFile("Z_Tetrimino.png");

}

void GameBoard::BackgroundSet()//adds the texture to 2d Vector of sprites(data member) and set their position
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (BackgroundMatrix[i][j] == 0)
			{
				BackgroundSprites[i][j].setTexture(BackgroundDefaultTexture);
				BackgroundSprites[i][j].setPosition((float)j * 40, (float)i * 40);// becuase for example i =0 ; j = 1 it should load at 0th row and 1st col which is point(40,0) on terminal so we do j*40 and i*40 in this texture are loaded according to matrix
			}
		}
	}
}

void GameBoard::PlaceTetriminoOnBoard(Tetrimino*& t)// gets a tetrimino and place it on gameboard 
{

	for (int i = 0; i < t->getBlocksCount(); i++)//blockscount=4
	{
		int x = t->getTetrisPiecePosX(i) / 40;// get the x-axis position and dividing by 40 to get matrix[20][10] position
		int y = t->getTetrisPiecePosY(i) / 40;// get the y-axis position and dividing by 40 to get matrix[20][10] position


		// check the color type and then set the sprites texture accordingly
		if (t->getcolor() == "cyan")
		{
			BackgroundSprites[y][x].setTexture(TextureStore[0]);
		}
		else if (t->getcolor() == "blue")
		{
			BackgroundSprites[y][x].setTexture(TextureStore[1]);
		}
		else if (t->getcolor() == "orange")
		{
			BackgroundSprites[y][x].setTexture(TextureStore[2]);
		}
		else if (t->getcolor() == "yellow")
		{
			BackgroundSprites[y][x].setTexture(TextureStore[3]);
		}
		else if (t->getcolor() == "green")
		{
			BackgroundSprites[y][x].setTexture(TextureStore[4]);
		}
		else if (t->getcolor() == "purple")
		{
			BackgroundSprites[y][x].setTexture(TextureStore[5]);
		}
		else if (t->getcolor() == "red")
		{
			BackgroundSprites[y][x].setTexture(TextureStore[6]);
		}

		BackgroundMatrix[y][x] = 1;// set that location ( position on matrix ) 1 indicating it is occupied 
	}
}


bool GameBoard::GameBoardDownMovementCheck(Tetrimino*& t)// gets the tetris check all its four points of blocks location and whether there is another tetris below it
{
	for (int i = 0; i < t->getBlocksCount(); i++)
	{
		int x = t->getTetrisPiecePosX(i);// get the x-axis position and dividing by 40 to get matrix[20][10] position
		int y = t->getTetrisPiecePosY(i);// get the y-axis position and dividing by 40 to get matrix[20][10] position
		x = x / 40;
		y = (y + 40) / 40;//because we are checking one cell down which has 40px height so we add 40

		if (BackgroundMatrix[y][x] == 1)// if down movement overlap the placed tetrimino pieces we prevent the movement
		{
			return false;
		}
	}
	return true;
}


bool GameBoard::GameBoardRightMovementCheck(Tetrimino*& t)// gets the tetris check all its four points of blocks location and whether there is another tetris right to it
{
	for (int i = 0; i < t->getBlocksCount(); i++)
	{
		int x = t->getTetrisPiecePosX(i);// get the x-axis position and dividing by 40 to get matrix[20][10] position
		int y = t->getTetrisPiecePosY(i);// get the y-axis position and dividing by 40 to get matrix[20][10] position

		x = (x + 40) / 40;//because we are checking one cell right which has 40px width so we add 40
		y = y / 40;

		if (BackgroundMatrix[y][x] == 1)// if right movement overlap the placed tetrimino pieces we prevent the movement
		{
			return false;
		}
	}
	return true;
}

bool GameBoard::GameBoardLeftMovementCheck(Tetrimino*& t)// gets the tetris check all its four points of blocks location and whether there is another tetris left to it
{
	for (int i = 0; i < t->getBlocksCount(); i++)
	{
		int x = t->getTetrisPiecePosX(i);// get the x-axis position and dividing by 40 to get matrix[20][10] position
		int y = t->getTetrisPiecePosY(i);// get the y-axis position and dividing by 40 to get matrix[20][10] position

		x = (x - 40) / 40;//because we are checking one cell left which has 40px width so we subtract 40 divide by 40 to get matrix position
		y = y / 40;

		if (BackgroundMatrix[y][x] == 1)// if left movement overlap the placed tetrimino pieces we prevent the movement
		{
			return false;
		}
	}
	return true;
}

bool GameBoard::GameBoardRotationMovementCheck(Tetrimino*& t)// gets the tetris check make a rotation and check whether after rotation there is any collision between a placed tetris piece
{
	Point CurrentPoints[4];// used to store current position of all 4 tetris block
	for (int i = 0; i < t->getBlocksCount(); i++)
	{
		int x = t->getTetrisPiecePosX(i);
		int y = t->getTetrisPiecePosY(i);
		CurrentPoints[i].SetX((float)x);
		CurrentPoints[i].SetY((float)y);
	}
	Point center = CurrentPoints[1];//axis of rotation

	Point CloneRotation[4];//cloning to see if after rotation there is any cell which overlaps placed tetris
	for (int j = 0; j < t->getBlocksCount(); j++)
	{
		// a formula for rotation which works for all except O and S pieces 
		int x = (int)CurrentPoints[j].getX() - (int)center.getX();
		int y = (int)CurrentPoints[j].getY() - (int) center.getY();
		int NewX = (int)center.getX() - y;
		int NewY = (int)center.getY() + x;
		NewX = NewX / 40;
		NewY = NewY / 40;

		if (NewX < 0 || NewX >= 10 || NewY < 0 || NewY >= 20)// prevent going out of bound
			return false;

		if (BackgroundMatrix[NewY][NewX] == 1)// if rotated tetris has any overlap return false to prevent
		{
			return false;
		}
	}
	return true;
}
void GameBoard::LineClear()// checks whether any line is filled with tetris piece
{
	for (int i = rows - 1; i >= 0; i--)// starts from bottom row
	{
		bool LineFull = true;
		for (int j = 0; j < cols; j++)
		{
			if (BackgroundMatrix[i][j] != 1)// if all row has 1 mean they are completely filled 
			{
				LineFull = false;
				break;
			}
		}
		if (LineFull)
		{
			TotalLinesCleared++;
			for (int r = i; r > 0; r--)// set r = filled row
			{
				for (int c = 0; c < cols; c++)
				{
					// move the entire rows above filled row ,  one row down 
					BackgroundMatrix[r][c] = BackgroundMatrix[r - 1][c];
					BackgroundSprites[r][c].setTexture(*BackgroundSprites[r - 1][c].getTexture());
				}
			
			}
			for (int l = 0; l < cols; l++)// set the first row empty
			{
				BackgroundMatrix[0][l] = 0;
				BackgroundSprites[0][l].setTexture(BackgroundDefaultTexture);
			}

			// Since we cleared a line, we need to check the same row again after shifting
			i++;  // This ensures that the newly shifted row is checked again
		}
	}
}



bool GameBoard::GameOver()// checks the top row and area where tetris spawns if they are filled 
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 4; j++)  // columns 0 to 3
		{
			if (BackgroundMatrix[i][j] == 1)
			{
				return true;   // Game over,  space is blocked
			}
		}
	}
	return false;
}
bool GameBoard::LevelClear()// if 10 lines are cleared level increase
{
	if (TotalLinesCleared >= 10)// if ten line or above clears then move to next level
	{
		currentLevel++;
		return true;
	}
	return false;
}

void GameBoard::WindowReset()//a function that resets the background when a level is cleared
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			BackgroundMatrix[i][j] = 0;// set the whole matrix to 0
		}
	}
	TotalLinesCleared = 0;
	BackgroundSet();// call the function to give new texture to 2d vector of sprites
}

void GameBoard::GameEnd()// game end when player reach level 8 resetting everything going back to level 1
{
	if (currentLevel == 8)
	{
		currentLevel = 0;
		TotalLinesCleared = 0;
		WindowReset();// call the above function
	}
}





// getter functions used in main 
int GameBoard::getCurrentLevel()
{
	return currentLevel;
}

int GameBoard::getscore()
{
	return TotalLinesCleared*100;
}

int GameBoard::getlines()
{
	return TotalLinesCleared;
}

sf::Sprite& GameBoard::getSprite(const int& i, const int& j)// used in main function for window.draw 
{
	return BackgroundSprites[i][j];
}
