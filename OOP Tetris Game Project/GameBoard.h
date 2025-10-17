#pragma once
#include"Tetrimino.h"
class GameBoard
{
private:
	const int rows;
	const int cols;
	int BackgroundMatrix[20][10]; 
	vector < vector<sf::Sprite>> BackgroundSprites;//2d vector of sprites
	sf::Texture BackgroundDefaultTexture;// a texture to load 
	vector<sf::Texture> TextureStore;
	int TotalLinesCleared;
	int currentLevel;
public:
	GameBoard();// constructor assign data members values
	void BackgroundSet();//adds the texture to 2d Vector of sprites(data member) and set their position
	void PlaceTetriminoOnBoard(Tetrimino*& t);// gets a tetrimino and place it on gameboard 
	bool GameBoardDownMovementCheck(Tetrimino*& t);// gets the tetris check all its four points of blocks location and whether there is another tetris below it
	bool GameBoardRightMovementCheck(Tetrimino*& t);// gets the tetris check all its four points of blocks location and whether there is another tetris right to it
	bool GameBoardLeftMovementCheck(Tetrimino*& t);// gets the tetris check all its four points of blocks location and whether there is another tetris left to it
	bool GameBoardRotationMovementCheck(Tetrimino*& t);// gets the tetris check make a rotation and check whether after rotation there is any collision between a placed tetris piece

	void LineClear();// checks whether any line is filled with tetris piece
	bool GameOver();// checks the top row and area where tetris spawns if they are filled 
	bool LevelClear();// if 10 lines are cleared level increase
	void WindowReset();//a function that resets the background when a level is cleared
	void GameEnd();// game end when player reach level 8 resetting everything going back to level 1


	//getter functions 
	int getCurrentLevel();
	int getscore();
	int getlines();
	sf::Sprite& getSprite(const int& i, const int& j);// used in main function for window.draw
};





