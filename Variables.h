#pragma once
#include "Buttons.h"
#include "constant.h"
#include "Texture.h"

using namespace std;

// initialization
extern SDL_Window* window;
extern SDL_Renderer* renderer;

// loop variable
extern bool isRunning;
extern bool isChoosing;
extern bool showMenu;
extern bool gameLoop;
extern bool customMode;

// win or lose variables
extern bool isWinning;
extern bool lose;

//image use in game
extern LTexture menuTheme;
extern LTexture leveltheme;
extern LTexture easyTable;
extern LTexture mediumTable;
extern LTexture hardTable;
extern LTexture customStart;
extern LTexture sound_on;
extern LTexture sound_off;
extern LTexture back;

// image face
extern LTexture winFace;
extern LTexture playingFace;
extern LTexture loseFace;

//tiles on board
extern LTexture Tiles_image;
extern SDL_Rect Tilesprites[12];

// text

extern LTexture menu;
extern LTexture menu1;
extern LTexture menuColor;
extern LTexture menu1Color;
extern LTexture easyChoice;
extern LTexture mediumChoice;
extern LTexture hardChoice;
extern LTexture customChoice;
extern LTexture easyChoiceColor;
extern LTexture mediumChoiceColor;
extern LTexture hardChoiceColor;
extern LTexture customChoiceColor;
extern LTexture wInput;
extern LTexture hInput;
extern LTexture mInput;
extern TTF_Font* gfont;

// Create board data
extern vector <vector<int> > sBoard;
extern vector <vector<int> > board;

// mines
extern int mineCountLeft;
extern int CountTileLeft;

// audio
extern Mix_Chunk* click;
extern Mix_Music* loseMusic;
extern Mix_Music* winMusic;

//distance
extern int distance_x;
extern int distance_y;
extern int digit_x;
extern int digit_y;
extern int timeDigit_x;

// digits image
extern LTexture Digits;
extern SDL_Rect Digitsprites[10];

// board size
extern int BOARD_SIZE_X;
extern int BOARD_SIZE_Y;
extern int NumberOfMines;

//boolean
extern bool playAgain;
extern bool saveScore;
extern bool easy;
extern bool medium;
extern bool hard;
extern bool cus;
extern bool start;

