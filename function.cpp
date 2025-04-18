#include <bits/stdc++.h>
#include "Buttons.h"
#include "constant.h"
#include "Variables.h"
#include "function.h"
#include "Texture.h"
#include "Timer.h"
using namespace std;

vector<vector<LButton>> Buttons(3,vector<LButton>(2));
LButton face;
LButton goBack;
LButton sound;
LTimer timer;
// initialization func
bool init()
{
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        cout << "SDL could not initialize :" << SDL_GetError() << endl;
        success = false;
    }
    else
    {
        window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL)
        {
            cout << "window could not be created: " << SDL_GetError() << endl;
            success = false;
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer == NULL)
            {
                cout << "renderer could not be created: " << SDL_GetError() << endl;
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF,0xFF,0xFF);
                if (!(IMG_Init(IMG_INIT_PNG)))
                {
                    cout << "IMG_init has failed. Error: " << IMG_GetError() << endl;
                    success = false;
                }
                if(TTF_Init() == -1)
                {
                    cout << "TTF init has failed. Error " << TTF_GetError() << endl;
                    success =  false;
                }
                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
                {
                    cout << "Mixer init has failed. Error " << Mix_GetError() << end;
                    success = false;
                }
            }
        }
    }
}
void loadmedia()
{
    bool success = true;
    if(!Tiles_image.loadFromFile("res/images/tiles5.jpg"))
    {
        cout << "can not load this from file" << endl;
        success = false;
    }
    else
    {
        for(int i=0 ; i<12 ; i++)
        {
            Tilesprites[i].x = i * TILE_SIZE;
            Tilesprites[i].y = 0;
            Tilesprites[i].w = TILE_SIZE;
            Tilesprites[i].h = TILE_SIZE;
        }
    }
    if(!Digits.loadFromFile("res/images/Untitled1.png"))
    {
        cout << "can not load this from file" << endl;
        success = false;
    }
    else
    {
        for(int i=0 ; i<10 ; i++)
        {
            Digitsprites[i].x = i * 28;
            Digitsprites[i].y = 0;
            Digitsprites[i].w = 28;
            Digitsprites[i].h = 46;
        }
    }
    if(!easyTable.loadFromFile("res/images/easy.png"))
    {
        cout << "fail" << endl;
        success = false;
    }
    if(!mediumTable.loadFromFile("res/images/medium.png"))
    {
        cout << "fail" << endl;
        success = false;
    }
    if(!hardTable.loadFromFile("res/images/hard.png"))
    {
        cout << "fail" << endl;
        success = false;
    }
    if(!winFace.loadFromFile("res/images/winface.png"))
    {
        cout << "fail" << endl;
        success = false;
    }
    if(!playingFace.loadFromFile("res/images/playingface.png"))
    {
        cout << "fail" << endl;
        success = false;
    }
    if(!loseFace.loadFromFile("res/images/loseface.png"))
    {
        cout << "fail" << endl;
        success = false;
    }
    if(!back.loadFromFile("res/images/backicon.png"))
    {
        cout << "fail" << endl;
        success = false;
    }
    if(!sound_on.loadFromFile("res/images/unmute.png"))
    {
        cout << "fail" << endl;
        success = false;
    }
    if(!sound_off.loadFromFile("res/images/mute.png"))
    {
        cout << "fail" << endl;
        success = false;
    }
    gfont = TTF_OpenFont("res/font.ttf", 20);
    if(gfont == NULL)
    {
        cout << "failed to load lazy font" << TTF_GetError() << endl;
        success = false;
    }
    winMusic = Mix_LoadMUS("res/audio/winning.wav");
    if(winMusic == NULL)
    {
        cout << "fail to load winning sound" << Mix_GetError() << endl;
        success = false;
    }
    loseMusic = Mix_LoadMUS("res/audio/losing.wav");
    if(loseMusic == NULL)
    {
        cout << "fail to load bomb sound" << Mix_GetError() << endl;
        success = false;
    }
    click = Mix_LoadWAV("res/audio/click.wav");
    if(click == NULL)
    {
        cout << "fail to load clicking sound effect" << Mix_GetError() << endl;
        success =false;
    }
    return success;
}
void loadMenuMedia()
{
    bool success = true;
    if (!menuTheme.loadFromFile("res/images/menu.jpg"))
    {
        cout << "fail" << endl;
        success = false;
    }
    if (!levelTheme.loadFromFile("res/images/mode.jpg"))
    {
        cout << "fail" << endl;
        success = false;
    }
    if (!customStart.loadFromFile("res/images/custom.png"))
    {
        cout << "fail" << endl;
        success = true;
    }
    SDL_Color textColor = { 255,255,255 };
    if (!easyChoice.loadFromRenderedText("EASY MODE", textColor))
    {
        cout << "fail" << endl;
        success = false;
    }
    if (!mediumChoice.loadFromRenderedText("MEDIUM MODE", textColor))
    {
        cout << "fail" << endl;
        success = false;
    }
    if (!hardChoice.loadFromRenderedText("HARD MODE", textColor))
    {
        cout << "fail" << endl;
        success = false;
    }
    if (!customChoice.loadFromRenderedText("CUSTOM MODE", textColor))
    {
        cout << "fail" << endl;
        success = false;
    }
    SDL_Color textcolor = { 255,0,0 };
    if (!easyChoiceColor.loadFromRenderedText("EASY MODE", textcolor))
    {
        cout << "fail" << endl;
        success = false;
    }
    if (!mediumChoiceColor.loadFromRenderedText("MEDIUM MODE", textcolor))
    {
        cout << "fail" << endl;
        success = false;
    }
    if (!hardChoiceColor.loadFromRenderedText("HARD MODE", textcolor))
    {
        cout << "fail" << endl;
        success = false;
    }
    if (!customChoiceColor.loadFromRenderedText("CUSTOM MODE", textcolor))
    {
        cout << "fail" << endl;
        success = false;
    }
    return success;
}

// initialization game
void Createboard()
{
    srand(time(0));
    for(int i=0 ; i<BOARD_SIZE_X ; i++)
    {
        for(int j=0; j<BOARD_SIZE_Y ; j++)
        {
            sBoard[i][j] = 10;
            board[i][j] = 0;
        }
    }
    while(mine < NumberOfMines)
    {
        int i = rand() % BOARD_SIZE_X;
        int j = rand() % BOARD_SIZE_Y;
        if(board[i][j] == 9)
        {
            continue;
        }
        board[i][j] = 9;
        mine++;
    }
    for(int i=0; i<BOARD_SIZE_X ; i++)
    {
        for(int j=0; j<=BOARD_SIZE_Y; j++)
        {
            if(board[i][j] == 9)
            {
                continue;
            }
            for(int x=-1 ; x<=1 ; x++)
            {
                for(int y=-1; y<=1 ; y++)
                {
                    int xpos = i + x;
                    int ypos = j + y;
                    if(xpos < 0 || xpos > BOARD_SIZE_X - 1 ||  ypos < 0 ||ypos > BOARD_SIZE_Y -1)
                    {
                        continue;
                    }
                    if(board[xpos][ypos] == 9)
                    {
                        board[i][j]++;
                    }
                }
            }
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
    easyChoice,render(300, 150);
    mediumChoice.render(300, 200);
    hardChoice.render(300, 250);
    customChoice.render(300, 300);
}
void CustomMode()
{

}
void showMenu()
{

}
void showModeChoice()
{

}
void setButtonPosition()
{

}

// ingame func
void isPlayerWinning()
{
    if(CountTileLeft == NumberOfMines)
    {
        isWinning = true;
    }
}
string getTime()
{
    stringstream Time{};
    if(isWinning)
    {
        int n = timer.getTicks() / 1000;
        int h,m,s;
        h = n / 3600;
        m = (n - h*3600) / 60;
        s = (n - h*3600 - m*60);
        Time.str("");
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

void MineManager()
{
    int n = mineCountLeft;
    if(mineCountLeft < 10)
    {
        Digits.render(digit_x, digit_y, &Digitsprites[0]);
        for(int i=0 ; i<=9 ; i++)
        {
            if(i == mineCountLeft)
            {
                Digits.render(digit_x + 28, digit_y, &Digitsprites[i]);
            }
        }
    }
    else
    {
        int i=0;
        while(n > 0)
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
    if(n < 10)
    {
        for(int i=0 ; i<=9 ; i++)
        {
            if(i == n)
            {
                Digits.render(digit_x + 28, digit_y, &Digitsprites[n]);
            }
        }
    }
    else
    {
        int i=0;
        while(n > 0)
        {
            int x = n % 10;
            n /= 10;
            Digits.render(digit_x + (1 - i) * 28, digit_y, &Digitsprites[x]);
            i++;
        }
    }
}
void GameManager()
{
    if(playAgain == true)
    {
        PlayAgain();
    }
    if(lose == true)
    {
        timer.pause();
        loseFace.render(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);
        for(int i=0; i<BOARD_SIZE_X ; i++)
        {
            for(int j=0; j<BOARD_SIZE_Y ; j++)
            {
                Buttons[i][j].loseRender(i, j);
            }
        }
    }
    if(isWinning == true)
    {
        timer.pause();
        winFace.render(BOARD_SIZE_X * TILE_SIZE / 2, digit_y);
        if(isRunning == false)
        {
            getScore();
        }
    }
}
void playAgain()
{
    timer.stop();
    if(isWinning)
    {
        getScore();
    }
    timer.start();
    Createboard();
    Mix_HaltMusic();
    CountTileLeft = BOARD_SIZE_X * BOARD_SIZE_Y;
    mineCountLeft = NumberOfMines;
    isWinning = false;
    lose = false;
    playAgain = false;
}
void renderButton(){

}
void handleEvent(){

}
void reveal(int i, int j){

}
void renderGame(){

}
void setGameMode(int x,int y, int n, int dx, int dy, int d1x, int d1y, int& BOARD_SIZE_X, int& BOARD_SIZE_, int& NumberOfMines, int& mineCountLeft, int& CountTileLeft, int& distance_x, int& distance_y, int& digit_x, int& digit_y, int& timeDigit_x){

}
// close SDL
void close(){
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
