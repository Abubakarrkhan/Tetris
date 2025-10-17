#include "I_Tetrimino.h"
#include "J_Tetrimino.h"
#include "L_Tetrimino.h"
#include "O_Tetrimino.h"
#include "S_Tetrimino.h"
#include "T_Tetrimino.h"
#include "Z_Tetrimino.h"
#include <cstdlib>
#include"GameBoard.h"
#include <SFML/Audio.hpp>

void spawnNewTetris(Tetrimino *& tetris)// this function assigns the pointer a randow tetris piece
{
    int randomPiece = rand() % 7; // Random number between 0 and 6
    switch (randomPiece)
    {
    case 0:
        tetris = new I_Tetrimino();//checked cyan
        break;
    case 1:
        tetris = new J_Tetrimino();// checked blue
        break;
    case 2:
        tetris = new L_Tetrimino();//checked orange
        break;
    case 3:
        tetris = new O_Tetrimino();//checked yellow
        break;
    case 4:
        tetris = new S_Tetrimino();//ehecked green
        break;
    case 5:
        tetris = new T_Tetrimino();//checked purple
        break;
    case 6:
        tetris = new Z_Tetrimino();// checked red
        break;
    }
    tetris->Set(); // Set up the Tetrimino structure
}

void displayCredit(sf::RenderWindow& window, sf::Music& backgroundmusic)// when game end
{
    sf::Sprite endscreen;
    sf::Texture end;
    end.loadFromFile("Credits.png");
    endscreen.setTexture(end);

   
    while (window.isOpen())
    {
        // Event polling
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
                // You can handle other events here
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
        }
        window.clear();
        window.draw(endscreen);
        window.display();
    }
    
}

int main()
{
    sf::Music backgroundmusic;
    backgroundmusic.openFromFile("backgroundmusic.ogg");
    backgroundmusic.play();
    // Create a window to display the game
    sf::RenderWindow window(sf::VideoMode(800, 800), "Tetris Powered by Unity (Made on Unreal Engine)");
    GameBoard G;
    G.BackgroundSet();



    sf::Font font;
    font.loadFromFile("arial.ttf");
    
    sf::Text text1; 
    sf::Text text2;
    sf::Text text3; 
    text1.setFont(font);
    text2.setFont(font);
    text3.setFont(font);

    text1.setPosition(530, 200);
    text2.setPosition(530, 400);
    text3.setPosition(530, 600);
    text1.setCharacterSize(25);
    text2.setCharacterSize(25);
    text3.setCharacterSize(25);

    // Randomly select a Tetrimino type
    Tetrimino* tetris = nullptr;
    srand(time(0)); 
    spawnNewTetris(tetris);

    // Game timing variables
    sf::Clock clock;
    float DownMovementTimer;// a timer that at what rate the tetris move down 
    float timer = 0.0f;
    bool moveDown = true;// a checker that checks whether tetris can move down
    // Main game loop
    while (window.isOpen())
    {
  
        text1.setString("Current Level : " + std::to_string(G.getCurrentLevel()+1));
        text2.setString("Score : " + std::to_string(G.getscore()));
        text3.setString("Lines Cleared : " + std::to_string(G.getlines()));


        DownMovementTimer = 1.0f - ((float)G.getCurrentLevel() * 0.1f);// depending upon subtract 0.1 from it is 1 - (level * 0.1)

        float deltaTime = clock.restart().asSeconds();// each delta time will be 0.017s 

        timer += deltaTime;// adding delta time so when timer = downTimerMovement, it will automatically move down tetris 
      
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Handle user input for Tetrimino movement
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                    if(G.GameBoardLeftMovementCheck(tetris))// if no tetris piece places
                        tetris->MoveLeft();//
                }
                else if (event.key.code == sf::Keyboard::Right)
                {
                    if (G.GameBoardRightMovementCheck(tetris)) // if no tetris piece places
                        tetris->MoveRight();
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    moveDown = G.GameBoardDownMovementCheck(tetris) && tetris->MoveDown();// if first function return true then evalutes second function else abandon 
                }
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    if (G.GameBoardRotationMovementCheck(tetris))// if no tetris piece places
                    {
                        tetris->rotate();
                        
                    }
                      
                }  
            }
        }
        if (G.GameOver())// if tetris reach spawn location
        {
            displayCredit(window, backgroundmusic);
        }
        if (G.LevelClear())// if user clears 10 lines
        {
            G.WindowReset();// reset the background
            G.GameEnd();// a function that work when user reach level 8
        }

        // Move the Tetrimino down 
        if (timer >= DownMovementTimer)
        {
            moveDown = G.GameBoardDownMovementCheck(tetris) && tetris->MoveDown();// first check if first return true then evalutes second function else abandon

            timer = 0;
        }

        // Clear the window and draw everything
        window.clear();
        for(int i =0;i<20;i++)
            for (int j = 0; j < 10; j++)
            {
                window.draw(G.getSprite(i, j));
            }

        window.draw(text1);
        window.draw(text2);
        window.draw(text3);

        // Draw the Tetrimino blocks
        for (int i = 0; i < 4; i++)
        {
            window.draw(tetris->getSprite(i));
        }

        if (!moveDown)// if move down is false this means tetris can no longer move down 
        {

            G.PlaceTetriminoOnBoard(tetris);// place its last location
            delete tetris;
            tetris = nullptr;
            G.LineClear();// check if ant line clear
            spawnNewTetris(tetris);// spawn a new tetris
            moveDown = true;
        }

        window.display();
    }

    // Clean up the dynamically allocated Tetrimino
    delete tetris;
    return 0;
}
