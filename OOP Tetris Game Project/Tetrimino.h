#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include"Point.h"
class Tetrimino
{
protected:
	Point TetrisBlocksPos[4];// these will store Points of tetris block that makes a complete tetris piece(set in child classes)
	int Blockscount;// count how many blocks are entered in point array(set in child clases)
	int tetrimino[4][4];// a 4x4 grid that forms from child classes(set in child classes)
	sf::Texture TetrisBlock;// texture of the tetrimino block(their color) (set in child classes)
	vector<sf::Sprite> tetris;// vector of sprites that make complete tetris piece(total will be 4 always) 
 
public:
	Tetrimino();//a constructor
	void Load();//set the texture on blocks and assigns their posiition
	virtual void Set() = 0;// a pure virtual that defines data members for each tetris class
	virtual void rotate();// virtual as it inherits a seperate formula for O and S classes and rest inherits from parent class

	void MoveLeft();
	void MoveRight();
	bool MoveDown();

	//getter functions
	sf::Sprite& getSprite(const int& i);// used in main function for window.draw
	int getTetrisPiecePosX(const int& i);
	int getTetrisPiecePosY(const int& j);
	int getBlocksCount();
	virtual string getcolor() = 0;
};

