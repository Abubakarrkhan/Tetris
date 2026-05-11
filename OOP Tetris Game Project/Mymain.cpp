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


void drawInfoCard(sf::RenderWindow& window,float x, float y, float w, float h,const std::string& label, const std::string& value,sf::Font& font)
{
    // Card background
    sf::RectangleShape card(sf::Vector2f(w, h));
    card.setPosition(x, y);
    card.setFillColor(sf::Color(30, 30, 50, 220));
    card.setOutlineThickness(2.f);
    card.setOutlineColor(sf::Color(80, 80, 160, 200));
    window.draw(card);

    // Accent top bar
    sf::RectangleShape accent(sf::Vector2f(w, 4.f));
    accent.setPosition(x, y);
    accent.setFillColor(sf::Color(120, 90, 220));
    window.draw(accent);

    // Label text
    sf::Text lbl;
    lbl.setFont(font);
    lbl.setString(label);
    lbl.setCharacterSize(13);
    lbl.setFillColor(sf::Color(160, 140, 255));
    lbl.setStyle(sf::Text::Bold);
    lbl.setPosition(x + 12.f, y + 10.f);
    window.draw(lbl);

    // Value text
    sf::Text val;
    val.setFont(font);
    val.setString(value);
    val.setCharacterSize(26);
    val.setFillColor(sf::Color(240, 240, 255));
    val.setStyle(sf::Text::Bold);
    val.setPosition(x + 12.f, y + 30.f);
    window.draw(val);
}


void drawNextPiecePanel(sf::RenderWindow& window,Tetrimino* nextTetris,sf::Font& font,float panelX, float panelY, float panelW, float panelH)
{
    // Panel background
    sf::RectangleShape panel(sf::Vector2f(panelW, panelH));
    panel.setPosition(panelX, panelY);
    panel.setFillColor(sf::Color(20, 20, 45, 230));
    panel.setOutlineThickness(2.f);
    panel.setOutlineColor(sf::Color(80, 80, 160, 200));
    window.draw(panel);

    // Accent bar
    sf::RectangleShape accent(sf::Vector2f(panelW, 4.f));
    accent.setPosition(panelX, panelY);
    accent.setFillColor(sf::Color(80, 200, 200));
    window.draw(accent);

    // "NEXT" label
    sf::Text nextLabel;
    nextLabel.setFont(font);
    nextLabel.setString("NEXT");
    nextLabel.setCharacterSize(13);
    nextLabel.setFillColor(sf::Color(80, 220, 220));
    nextLabel.setStyle(sf::Text::Bold);
    nextLabel.setPosition(panelX + 12.f, panelY + 10.f);
    window.draw(nextLabel);

    if (!nextTetris) return;

    // Find bounding box of the next piece to centre it in the preview panel
    float minX = 1e9f, minY = 1e9f, maxX = -1e9f, maxY = -1e9f;
    int count = nextTetris->getBlocksCount();
    for (int i = 0; i < count; i++)
    {
        float bx = (float)nextTetris->getTetrisPiecePosX(i);
        float by = (float)nextTetris->getTetrisPiecePosY(i);
        if (bx < minX) minX = bx;
        if (by < minY) minY = by;
        if (bx > maxX) maxX = bx;
        if (by > maxY) maxY = by;
    }
    float pieceW = maxX - minX + 40.f;  // 40 = block size
    float pieceH = maxY - minY + 40.f;

    float previewAreaTop = panelY + 35.f;
    float previewAreaH   = panelH - 40.f;
    float offsetX = panelX + (panelW - pieceW) * 0.5f - minX;
    float offsetY = previewAreaTop + (previewAreaH - pieceH) * 0.5f - minY;

    for (int i = 0; i < count; i++)
    {
        sf::Sprite s = nextTetris->getSprite(i);          // copy sprite
        float origX = (float)nextTetris->getTetrisPiecePosX(i);
        float origY = (float)nextTetris->getTetrisPiecePosY(i);
        s.setPosition(origX + offsetX, origY + offsetY);
        window.draw(s);
    }
}


void drawControls(sf::RenderWindow& window, sf::Font& font,float x, float y, float w)
{
    sf::RectangleShape bg(sf::Vector2f(w, 148.f));
    bg.setPosition(x, y);
    bg.setFillColor(sf::Color(20, 20, 45, 210));
    bg.setOutlineThickness(2.f);
    bg.setOutlineColor(sf::Color(80, 80, 160, 200));
    window.draw(bg);

    sf::RectangleShape accent(sf::Vector2f(w, 4.f));
    accent.setPosition(x, y);
    accent.setFillColor(sf::Color(220, 120, 60));
    window.draw(accent);

    struct ControlEntry { const char* key; const char* action; };
    ControlEntry controls[] = {
        { "<  >", "Move Left / Right" },
        { "  v  ", "Move Down"  },
        { "  ^  ", "Rotate" }
    };

    for (int i = 0; i < 3 ;i++)
    {
        // Key badge
        sf::RectangleShape badge(sf::Vector2f(46.f, 22.f));
        badge.setPosition(x + 10.f, y + 14.f + i * 30.f);
        badge.setFillColor(sf::Color(60, 60, 100));
        badge.setOutlineThickness(1.f);
        badge.setOutlineColor(sf::Color(120, 120, 200));
        window.draw(badge);

        sf::Text keyTxt;
        keyTxt.setFont(font);
        keyTxt.setString(controls[i].key);
        keyTxt.setCharacterSize(11);
        keyTxt.setFillColor(sf::Color(220, 220, 255));
        keyTxt.setPosition(x + 13.f, y + 17.f + i * 30.f);
        window.draw(keyTxt);

        sf::Text actTxt;
        actTxt.setFont(font);
        actTxt.setString(controls[i].action);
        actTxt.setCharacterSize(11);
        actTxt.setFillColor(sf::Color(180, 180, 220));
        actTxt.setPosition(x + 62.f, y + 17.f + i * 30.f);
        window.draw(actTxt);
    }
}

int main()
{
    sf::Music backgroundmusic;
    backgroundmusic.openFromFile("backgroundmusic.ogg");
    backgroundmusic.play();
    // Create a window to display the game
    sf::RenderWindow window(sf::VideoMode(800, 800), "Tetris");
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

    Tetrimino* nextTetris = nullptr;
    spawnNewTetris(nextTetris);

    const float SB_X = 410.f;   // sidebar left edge (10px gap after board)
    const float SB_W = 375.f;   // sidebar width
    const float CARD_W = SB_W;
    const float CARD_H = 72.f;

    // Game timing variables
    sf::Clock clock;
    float DownMovementTimer;// a timer that at what rate the tetris move down 
    float timer = 0.0f;
    bool moveDown = true;// a checker that checks whether tetris can move down
    // Main game loop
    while (window.isOpen())
    {
  
        //text1.setString("Current Level : " + std::to_string(G.getCurrentLevel()+1));
        //text2.setString("Score : " + std::to_string(G.getscore()));
        //text3.setString("Lines Cleared : " + std::to_string(G.getlines()));


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

        sf::RectangleShape sidebar(sf::Vector2f(390.f, 800.f));
        sidebar.setPosition(400.f, 0.f);
        sidebar.setFillColor(sf::Color(12, 12, 28));
        window.draw(sidebar);

        // Thin divider line between board and sidebar
        sf::RectangleShape divider(sf::Vector2f(2.f, 800.f));
        divider.setPosition(400.f, 0.f);
        divider.setFillColor(sf::Color(70, 60, 140));
        window.draw(divider);

        // TITLE 
        sf::Text title;
        title.setFont(font);
        title.setString("TETRIS");
        title.setCharacterSize(42);
        title.setStyle(sf::Text::Bold);
        title.setFillColor(sf::Color(160, 120, 255));
        // Centre the title in the sidebar
        sf::FloatRect tb = title.getLocalBounds();
        title.setPosition(SB_X + (SB_W - tb.width) * 0.5f - tb.left, 18.f);
        window.draw(title);

        // Decorative line under title
        sf::RectangleShape titleLine(sf::Vector2f(SB_W - 20.f, 2.f));
        titleLine.setPosition(SB_X + 10.f, 72.f);
        titleLine.setFillColor(sf::Color(100, 70, 200, 180));
        window.draw(titleLine);

        drawNextPiecePanel(window, nextTetris, font,SB_X, 82.f, CARD_W, 140.f);

        // info cards
        drawInfoCard(window, SB_X, 240.f, CARD_W, CARD_H, "LEVEL",std::to_string(G.getCurrentLevel() + 1),font);
        drawInfoCard(window, SB_X, 320.f, CARD_W, CARD_H,"SCORE",std::to_string(G.getscore()),font);
        drawInfoCard(window, SB_X, 400.f, CARD_W, CARD_H,"LINES CLEARED",std::to_string(G.getlines()),font);

        // ── control legend
        drawControls(window, font, SB_X, 490.f, CARD_W);


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

            tetris = nextTetris;
            nextTetris = nullptr;
            spawnNewTetris(nextTetris);
            moveDown = true;
        }

        window.display();
    }

    delete tetris;
    delete nextTetris;
    return 0;
}
