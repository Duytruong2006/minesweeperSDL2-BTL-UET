#include "Texture.h"
#include "Variables.h"
#include "constant.h"
#include "Buttons.h"
#include "function.h"
#include "Timer.h"
#include <sstream>
#include <fstream>
using namespace std;
vector <vector<LButton> > Buttons(3, vector<LButton>(2));
LButton face;
LButton goBack;
LButton sound;
LTimer timer;

//initialization func
bool init()
{
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
            if (renderer == NULL)
            {
                printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                    success = false;
                }

                if (TTF_Init() == -1)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadmedia()
{
    bool success = true;
    if (!Tiles_image.loadFromFile("res/images/tiles5.jpg"))
    {
        printf("Can't load this image from file!");
        success = false;
    }
    else
    {
        for (int i = 0; i < 12; i++)
        {
            Tilesprites[i].x = i * TILE_SIZE;
            Tilesprites[i].y = 0;
            Tilesprites[i].w = TILE_SIZE;
            Tilesprites[i].h = TILE_SIZE;
        }
    }
    if (!Digits.loadFromFile("res/images/Untitled1.png"))
    {
        printf("Fail");
        success = false;
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            Digitsprites[i].x = i * 28;
            Digitsprites[i].y = 0;
            Digitsprites[i].w = 28;
            Digitsprites[i].h = 46;
        }
    }
    if (!easyTable.loadFromFile("res/images/easy.png"))
    {
        printf("Fail");
        success = false;
    }
    if (!mediumTable.loadFromFile("res/images/medium.png"))
    {
        printf("Fail");
        success = false;
    }
    if (!hardTable.loadFromFile("res/images/hard.png"))
    {
        printf("Fail");
        success = false;
    }
    if (!winFace.loadFromFile("res/images/winface.png"))
    {
        printf("Fail");
        success = false;
    }
    if (!loseFace.loadFromFile("res/images/loseface.png"))
    {
        printf("Fail");
        success = false;
    }
    if (!playingFace.loadFromFile("res/images/playingface.png"))
    {
        printf("Fail");
        success = false;
    }
    if (!back.loadFromFile("res/images/backicon.png"))
    {
        success = false;
    }
    if (!sound_on.loadFromFile("res/images/unmute.png"))
    {
        success = false;
    }
    if (!sound_off.loadFromFile("res/images/mute.png"))
    {
        success = false;
    }
    gFont = TTF_OpenFont("res/font.ttf", 20);
    if (gFont == NULL)
    {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }
    SDL_Color textcolor1 = { 255,255,255 };
    if (!menu.loadFromRenderedText("START", textcolor1))
    {
        printf("Fail");
    }
    if (!menu1.loadFromRenderedText("EXIT", textcolor1))
    {
        printf("fail!");
    }
    SDL_Color color = { 255,0,0 };
    if (!menuColor.loadFromRenderedText("START", color))
    {
        printf("Fail");
        success = false;
    }
    if (!menu1Color.loadFromRenderedText("EXIT", color))
    {
        printf("Fail");
        success = false;
    }
    loseMusic = Mix_LoadMUS("res/audio/losing.wav");
    if (loseMusic == NULL)
    {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    winMusic = Mix_LoadMUS("res/audio/winning.wav");
    if (winMusic == NULL)
    {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    click = Mix_LoadWAV("res/audio/click.wav");
    if (click == NULL)
    {
        printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    return success;
}

bool loadMenuMedia()
{
    bool success = true;
    if (!menuTheme.loadFromFile("res/images/menu.jpg"))
    {
        printf("Fail!");
        success = false;
    }
    if (!levelTheme.loadFromFile("res/images/mode.jpg"))
    {
        printf("Fail");
        success = false;
    }
    if (!customStart.loadFromFile("res/images/custom.png"))
    {
        printf("Fail");
        success = true;
    }
    SDL_Color textColor = { 255,255,255 };
    if (!easyChoice.loadFromRenderedText("EASY MODE", textColor))
    {
        printf("Fail");
        success = false;
    }
    if (!mediumChoice.loadFromRenderedText("MEDIUM MODE", textColor))
    {
        printf("Fail");
        success = false;
    }
    if (!hardChoice.loadFromRenderedText("HARD MODE", textColor))
    {
        printf("Fail");
        success = false;
    }
    if (!customChoice.loadFromRenderedText("CUSTOM MODE", textColor))
    {
        printf("Fail");
        success = false;
    }
    SDL_Color textcolor = { 255,0,0 };
    if (!easyChoiceColor.loadFromRenderedText("EASY MODE", textcolor))
    {
        printf("Fail");
        success = false;
    }
    if (!mediumChoiceColor.loadFromRenderedText("MEDIUM MODE", textcolor))
    {
        printf("Fail");
        success = false;
    }
    if (!hardChoiceColor.loadFromRenderedText("HARD MODE", textcolor))
    {
        printf("Fail");
        success = false;
    }
    if (!customChoiceColor.loadFromRenderedText("CUSTOM MODE", textcolor))
    {
        printf("Fail");
        success = false;
    }
    return success;
}

//initialization games
void CreateBoard()
{
    srand(time(0));
    int mine = 0;
    //Initialization
    for (int i = 0; i < BOARD_SIZE_X; i++)
    {
        for (int j = 0; j < BOARD_SIZE_Y; j++)
        {
            sBoard[i][j] = 10;
            board[i][j] = 0;
        }
    }

    //Random mines in board
    while (mine < NumberOfMines)
    {
        int i = rand() % BOARD_SIZE_X;
        int j = rand() % BOARD_SIZE_Y;
        if (board[i][j] == 9) continue;
        board[i][j] = 9;
        mine++;
    }

    //Calculate the number of mines around each cell
    for (int i = 0; i < BOARD_SIZE_X; i++)
    {
        for (int j = 0; j < BOARD_SIZE_Y; j++)
        {
            if (board[i][j] == 9) continue;
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    int xpos = i + x;
                    int ypos = j + y;
                    if (xpos < 0 || xpos>BOARD_SIZE_X - 1 || ypos<0 || ypos>BOARD_SIZE_Y - 1) continue;
                    if (board[xpos][ypos] == 9) board[i][j]++;
                }
            }
        }
    }
}

void setButtonPosition()
{
    face.setPosition(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);
    goBack.setPosition(0, 0);
    sound.setPosition(timeDigit_x - 10, 0);
    for (int i = 0; i < BOARD_SIZE_X; ++i)
    {
        for (int j = 0; j < BOARD_SIZE_Y; ++j)
        {
            Buttons[i][j].setPosition(i * TILE_SIZE + distance_x, j * TILE_SIZE + distance_y);
        }
    }
}

void createMenu()
{
    menuTheme.render(0, 0);
    menu.render(300, 400);
    menu1.render(450, 400);
    SDL_RenderPresent(renderer);
}

void createModeMenu()
{
    levelTheme.render(0, 0);
    easyChoice.render(300, 150);
    mediumChoice.render(300, 200);
    hardChoice.render(300, 250);
    customChoice.render(300, 300);
}

void showMenu()
{
    bool startInside = false;
    bool exitInside = false;
    bool isMenuShowing = true;
    SDL_Event event;
    createMenu();
    while (isMenuShowing)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                mainLoop = false;
                isMenuShowing = false;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (x > 300 && x < 300 + menu.getWidth() && y > 400 && y < 400 + menu.getHeight()) startInside = true;
                else startInside = false;
                if (x > 450 && x < 450 + menu1.getWidth() && y > 400 && y < 400 + menu1.getHeight()) exitInside = true;
                else exitInside = false;
                if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        if (startInside == true)
                        {
                            start = true;
                            isMenuShowing = false;
                        }
                        if (exitInside == true)
                        {
                            mainLoop = false;
                            isMenuShowing = false;

                        }
                    }
                }
                if (event.type == SDL_MOUSEMOTION)
                {
                    if (startInside == true)
                    {
                        menuColor.render(300, 400);
                    }
                    else menu.render(300, 400);
                    if (exitInside == true)
                    {
                        menu1Color.render(450, 400);

                    }
                    else menu1.render(450, 400);
                }

            }
            SDL_RenderPresent(renderer);
        }
    }
}

void showModeChoice()
{
    bool easyInside = false;
    bool mediumInside = false;
    bool hardInside = false;
    bool customInside = false;
    SDL_Event event;
    createModeMenu();
    while (isChoosing)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                mainLoop = false;
                isChoosing = false;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION)
            {
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (x > 300 && x < 300 + easyChoice.getWidth() && y > 150 && y < 150 + easyChoice.getHeight()) easyInside = true;
                else easyInside = false;
                if (x > 300 && x < 300 + mediumChoice.getWidth() && y > 200 && y < 200 + mediumChoice.getHeight()) mediumInside = true;
                else mediumInside = false;
                if (x > 300 && x < 300 + hardChoice.getWidth() && y > 250 && y < 250 + hardChoice.getHeight()) hardInside = true;
                else hardInside = false;
                if (x > 300 && x < 300 + customChoice.getWidth() && y > 300 && y < 300 + customChoice.getHeight()) customInside = true;
                else customInside = false;
                if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        if (easyInside == true)
                        {
                            isRunning = true;
                            isChoosing = false;
                            customMode = false;
                            timer.start();
                            easy = true;
                            medium = false;
                            hard = false;
                            cus = false;
                            SDL_SetWindowSize(window, 294, 436);
                            setGameMode(9, 9, 10, 21, 163, 25, 80, 235, BOARD_SIZE_X, BOARD_SIZE_Y, NumberOfMines, mineCountLeft, CountTileLeft, distance_x, distance_y, digit_x, digit_y, timeDigit_x);
                            CreateBoard();
                        }
                        if (mediumInside == true)
                        {
                            isRunning = true;
                            isChoosing = false;
                            customMode = false;
                            timer.start();
                            easy = false;
                            medium = true;
                            hard = false;
                            cus = false;
                            SDL_SetWindowSize(window, 488, 630);
                            setGameMode(16, 16, 40, 21, 163, 25, 80, 430, BOARD_SIZE_X, BOARD_SIZE_Y, NumberOfMines, mineCountLeft, CountTileLeft, distance_x, distance_y, digit_x, digit_y, timeDigit_x);
                            CreateBoard();
                        }
                        if (hardInside == true)
                        {
                            isRunning = true;
                            isChoosing = false;
                            customMode = false;
                            timer.start();
                            easy = false;
                            medium = false;
                            hard = true;
                            cus = false;
                            SDL_SetWindowSize(window, 880, 632);
                            setGameMode(30, 16, 99, 21, 163, 25, 80, 820, BOARD_SIZE_X, BOARD_SIZE_Y, NumberOfMines, mineCountLeft, CountTileLeft, distance_x, distance_y, digit_x, digit_y, timeDigit_x);
                            CreateBoard();
                        }
                        if (customInside == true)
                        {
                            isChoosing = false;
                            customMode = true;
                            easy = false;
                            medium = false;
                            hard = false;
                            cus = true;
                        }
                    }
                }
                if (event.type == SDL_MOUSEMOTION)
                {
                    if (easyInside == true) easyChoiceColor.render(300, 150);
                    else easyChoice.render(300, 150);
                    if (mediumInside == true) mediumChoiceColor.render(300, 200);
                    else mediumChoice.render(300, 200);
                    if (hardInside == true) hardChoiceColor.render(300, 250);
                    else hardChoice.render(300, 250);
                    if (customInside == true) customChoiceColor.render(300, 300);
                    else customChoice.render(300, 300);
                }
            }
            SDL_RenderPresent(renderer);
        }
    }
}

void CustomMode()
{
    SDL_Event e{};
    SDL_Color black = { 0,0,0,0 };
    SDL_SetWindowSize(window, 400, 600);
    customStart.render(0, 0);
    string width, height, mine;
    int w = 0, h = 0, m = 0;
    char inputChar;
    bool widthInside = false;
    bool heightInside = false;
    bool mineInside = false;
    bool play = false;
    while (customMode)
    {
        SDL_StartTextInput();
        while (SDL_PollEvent(&e) != 0)
        {
            switch (e.type)
            {
            case SDL_QUIT:
                customMode = false;
                mainLoop = false;
                break;
            case SDL_MOUSEBUTTONDOWN:
                int x, y;
                SDL_GetMouseState(&x, &y);
                if (x > 200 && x < 267 && y>374 && y < 394) widthInside = true;
                else widthInside = false;
                if (x > 200 && x < 267 && y>400 && y < 420) heightInside = true;
                else heightInside = false;
                if (x > 200 && x < 267 && y>427 && y < 447) mineInside = true;
                else mineInside = false;
                if (x > 150 && x < 250 && y>488 && y < 526) play = true;
                else play = false;
                break;
            case SDL_TEXTINPUT:
                inputChar = e.text.text[0];
                if (inputChar >= '0' && inputChar <= '9')
                {
                    if (widthInside && width.length() < 6)
                    {
                        width += e.text.text;
                        w *= 10;
                        w += (int)(inputChar - 48);
                        wInput.loadFromRenderedText(width.c_str(), black);
                    }
                    else if (heightInside && height.length() < 6)
                    {
                        height += e.text.text;
                        h *= 10;
                        h += (int)(inputChar - 48);
                        hInput.loadFromRenderedText(height.c_str(), black);
                    }
                    else if (mineInside && mine.length() < 6)
                    {
                        mine += e.text.text;
                        m *= 10;
                        m += (int)(inputChar - 48);
                        mInput.loadFromRenderedText(mine.c_str(), black);
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (widthInside && e.key.keysym.sym == SDLK_BACKSPACE && width.length() > 0)
                {
                    width.pop_back();
                    w /= 10;
                    wInput.loadFromRenderedText(width.c_str(), black);
                }
                else if (heightInside && e.key.keysym.sym == SDLK_BACKSPACE && height.length() > 0)
                {
                    height.pop_back();
                    h /= 10;
                    hInput.loadFromRenderedText(height.c_str(), black);
                }
                else if (mineInside && e.key.keysym.sym == SDLK_BACKSPACE && mine.length() > 0)
                {
                    mine.pop_back();
                    m /= 10;
                    mInput.loadFromRenderedText(mine.c_str(), black);
                }
                else if (e.key.keysym.sym == SDLK_DOWN)
                {
                    if (widthInside)
                    {
                        widthInside = false;
                        heightInside = true;
                        mineInside = false;
                    }
                    else if (heightInside)
                    {
                        widthInside = false;
                        heightInside = false;
                        mineInside = true;
                    }
                    else if (mineInside)
                    {
                        widthInside = true;
                        heightInside = false;
                        mineInside = false;
                    }
                }
                else if (e.key.keysym.sym == SDLK_UP)
                {
                    if (widthInside)
                    {
                        widthInside = false;
                        heightInside = false;
                        mineInside = true;
                    }
                    else if (heightInside)
                    {
                        widthInside = true;
                        heightInside = false;
                        mineInside = false;
                    }
                    else if (mineInside)
                    {
                        widthInside = false;
                        heightInside = true;
                        mineInside = false;
                    }
                }
                break;
            default:
                break;
            }
        }

        wInput.render(201, 370);
        hInput.render(201, 397);
        mInput.render(201, 423);

        if (play == true)
        {
            isRunning = true;
            customMode = false;
            play = false;
            timer.start();
            SDL_SetWindowSize(window, w * TILE_SIZE, h * TILE_SIZE + 110);
            setGameMode(w, h, m, 0, 110, 10, 60, w * TILE_SIZE - 40, BOARD_SIZE_X, BOARD_SIZE_Y, NumberOfMines, mineCountLeft, CountTileLeft, distance_x, distance_y, digit_x, digit_y, timeDigit_x);
            CreateBoard();
        }
        SDL_StopTextInput();
        SDL_RenderPresent(renderer);
    }

    width = "";
    height = "";
    mine = "";
    widthInside = false;
    heightInside = false;
    mineInside = false;
    wInput.free();
    hInput.free();
    mInput.free();
}

//ingame func
void handleEvent()
{
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            isRunning = false;
            mainLoop = false;
        }
        face.handleEventAgain(&e);
        goBack.handleEventBack(&e);
        sound.handleEventMute(&e);
        for (int i = 0; i < BOARD_SIZE_X; i++)
        {
            for (int j = 0; j < BOARD_SIZE_Y; j++)
            {
                Buttons[i][j].handleEvent(&e);
            }
        }

    }
}

void reveal(int i, int j)
{
    if (sBoard[i][j] == 10 || sBoard[i][j] == 11)
    {
        if (sBoard[i][j] == 11)
        {
            return;
        }
        sBoard[i][j] = board[i][j];
        if (sBoard[i][j] != 9) CountTileLeft--;
        if (sBoard[i][j] == 0)
        {
            for (int x = -1; x <= 1; x++)
            {
                for (int y = -1; y <= 1; y++)
                {
                    int xpos = i + x;
                    int ypos = j + y;
                    if (xpos<0 || xpos>BOARD_SIZE_X - 1 || ypos<0 || ypos>BOARD_SIZE_Y - 1) continue;
                    reveal(xpos, ypos);
                }
            }
        }
    }
}

void isPlayerWinning()
{
    if (CountTileLeft == NumberOfMines) isWinning = true;
}

void GameManager()
{
    if (playAgain == true) PlayAgain();
    if (lose == true)
    {
        timer.pause();
        loseFace.render(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);
        for (int i = 0; i < BOARD_SIZE_X; i++)
        {
            for (int j = 0; j < BOARD_SIZE_Y; j++)
            {
                Buttons[i][j].loseRender(i, j);
            }
        }
    }
    if (isWinning == true)
    {
        timer.pause();
        winFace.render(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);
        if (isRunning == false && isWinning) getScore();
    }
}

string getTime()
{
    stringstream Time{};
    if (isWinning == true)
    {
        int n = timer.getTicks() / 1000;
        int h, m, s;
        h = n / 3600;
        m = (n - h * 3600) / 60;
        s = (n - h * 3600 - m * 60);
        Time.str( "" );
        Time << h << ":" << m << ":" << s;
        return Time.str();
    }
}

string getFileScoreName()
{
    stringstream os;
    os.str( "" );
    os << "score/" << BOARD_SIZE_X << "x" << BOARD_SIZE_Y << "x" << NumberOfMines<<".txt";
    return os.str();
}

void getScore()
{
    ofstream outFile;
    outFile.open(getFileScoreName().c_str(),ios::app);
    outFile << getTime() << endl;
    outFile.close();
}

void PlayAgain()
{
    timer.stop();
    if(isWinning) getScore();
    timer.start();
    CreateBoard();
    Mix_HaltMusic();
    mineCountLeft = NumberOfMines;
    CountTileLeft = BOARD_SIZE_X * BOARD_SIZE_Y;
    isWinning = false;
    lose = false;
    playAgain = false;
}

void MineManager()
{
    int n = mineCountLeft;
    if (mineCountLeft < 10)
    {
        Digits.render(digit_x, digit_y, &Digitsprites[0]);
        for (int i = 0; i <= 9; i++)
        {
            if (i == mineCountLeft) Digits.render(digit_x + 28, digit_y, &Digitsprites[i]);
        }
    }

    else
    {
        int i = 0;
        while (n > 0)
        {
            int x = n % 10;
            n /= 10;
            Digits.render(digit_x + (1 - i) * 28, digit_y, &Digitsprites[x]);
            i++;
        }
    }
}

void TimeManager()
{
    int n = timer.getTicks() / 1000;
    if (n < 10)
    {
        for (int i = 0; i <= 9; i++)
        {
            if (i == n) Digits.render(timeDigit_x, digit_y, &Digitsprites[n]);
        }
    }
    else
    {
        int i = 0;
        while (n > 0)
        {
            int x = n % 10;
            n /= 10;
            Digits.render(timeDigit_x - i * 28, digit_y, &Digitsprites[x]);
            i++;
        }
    }

}

void setGameMode(int x, int y, int n, int dx, int dy, int d1x, int d1y, int dtx, int& BOARD_SIZE_X, int& BOARD_SIZE_Y, int& NumberOfMines, int& mineCountLeft, int& CountTileLeft, int& distance_x, int& distance_y, int& digit_x, int& digit_y, int& timeDigit_x)
{
    BOARD_SIZE_X = x;
    BOARD_SIZE_Y = y;
    NumberOfMines = n;
    mineCountLeft = n;
    CountTileLeft = x * y;
    distance_x = dx;
    distance_y = dy;
    digit_x = d1x;
    digit_y = d1y;
    timeDigit_x = dtx;

    Buttons.resize(BOARD_SIZE_X);
    for (int i = 0; i < BOARD_SIZE_X; i++)
    {
        Buttons[i].resize(BOARD_SIZE_Y);
    }
    sBoard.resize(BOARD_SIZE_X);
    for (int i = 0; i < BOARD_SIZE_X; i++)
    {
        sBoard[i].resize(BOARD_SIZE_Y);
    }
    board.resize(BOARD_SIZE_X);
    for (int i = 0; i < BOARD_SIZE_X; i++)
    {
        board[i].resize(BOARD_SIZE_Y);
    }
}

void renderButton()
{
    for (int i = 0; i < BOARD_SIZE_X; i++)
    {
        for (int j = 0; j < BOARD_SIZE_Y; j++)
        {
            Buttons[i][j].render(i, j);
        }
    }
}

void renderGame()
{
    if (mute == false)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        sound_on.render(timeDigit_x - 10, 0);
        loseMusic = Mix_LoadMUS("res/audio/losing.wav");
        winMusic = Mix_LoadMUS("res/audio/winning.wav");
        click = Mix_LoadWAV("res/audio/click.wav");
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        sound_off.render(timeDigit_x - 10, 0);
        click = NULL;
        winMusic = NULL;
        loseMusic = NULL;
    }
    if (easy == true)
    {
        easyTable.render(0, 50);
    }
    if (medium == true)
    {
        mediumTable.render(0, 50);
    }
    if (hard == true)
    {
        hardTable.render(0, 50);
    }
    if (cus == true)
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    }
    playingFace.render(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);
    renderButton();
    back.render(0, 0);
    MineManager();
    isPlayerWinning();
    TimeManager();
    GameManager();
    SDL_RenderPresent(renderer);
}

//close SDL
void close()
{
    Tiles_image.free();
    TTF_CloseFont(gFont);
    gFont = NULL;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

}
