#include "Variables.h"
#include<iostream>
using namespace std;

// loop variable
bool isRunning = false;
bool showmenu = false;
bool isChoosing = true;
bool mainLoop = true;
bool customMode = false;

// win or lose
bool isWinning = false;
bool lose = false;

// mines
int mineCountLeft = NumberOfMines;
int CountTileLeft = BOARD_SIZE_X * BOARD_SIZE_Y;

// images use in game
LTexture menuTheme(NULL, 0, 0);
LTexture levelTheme(NULL, 0, 0);
LTexture easyTable(NULL, 0, 0);
LTexture mediumTable(NULL, 0, 0);
LTexture hardTable(NULL, 0, 0);
LTexture customStart(NULL, 0, 0);
LTexture back(NULL, 0, 0);
LTexture sound_on(NULL, 0, 0);
LTexture sound_off(NULL, 0, 0);

//image face
LTexture winFace(NULL,0,0);
LTexture playingFace(NULL,0,0);
LTexture loseFace(NULL,0,0);

// text
LTexture menu(NULL, 0, 0);
LTexture menu1(NULL, 0, 0);
LTexture menuColor(NULL, 0, 0);
LTexture menu1Color(NULL, 0, 0);
LTexture easyChoice(NULL, 0, 0);
LTexture mediumChoice(NULL, 0, 0);
LTexture hardChoice(NULL, 0, 0);
LTexture customChoice(NULL, 0, 0);
LTexture easyChoiceColor(NULL, 0, 0);
LTexture mediumChoiceColor(NULL, 0, 0);
LTexture hardChoiceColor(NULL, 0, 0);
LTexture customChoiceColor(NULL, 0, 0);
LTexture wInput(NULL, 0, 0);
LTexture hInput(NULL, 0, 0);
LTexture mInput(NULL, 0, 0);

// create board data
vector <vector<int> > sBoard(3, vector<int>(2,0));
vector <vector<int> > board(3, vector<int>(2,0));

// Tiles in board
extern LTexture Tiles_image(NULL, 0, 0);
extern SDL_Rect Tilesprites[12] = {};

// audio
bool mute = false;
Mix_Chunk* click = NULL;
Mix_Music* loseMusic = NULL;
Mix_Music* winMusic = NULL;

// distance
int distance_x = 0;
int distance_y = 0;
int digit_x = 0;
int digit_y = 0;
int timeDigit_x = 0;

// digits image
LTexture Digits(NULL, 0, 0);
SDL_Rect Digitsprites[10] = {};

// Board size
int BOARD_SIZE_X = 0;
int BOARD_SIZE_Y = 0;
int NumberOfMines = 0;

// boolean
bool playAgain = false;
bool saveScore = false;
bool start = false;
bool easy = false;
bool medium = false;
bool hard = false;
bool cus = false;
