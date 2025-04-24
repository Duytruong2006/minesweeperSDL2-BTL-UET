#pragma once
#include "Timer.h"
#include <SDL.h>
using namespace std;

// initialization func
bool init();
bool loadmedia();
bool loadMenuMedia();

//initialization game
void CreateBoard();
void createMenu();
void createModeMenu();
void CustomMode();
void showMenu();
void showModeChoice();
void setButtonPosition();

//ingame func
void isPlayerWinning();
string getTime();
string getFileScoreName();
void getScore();
void MineManager();
void TimeManager();
void GameManager();
void PlayAgain();
void renderButton();
void handleEvent();
void reveal(int i, int j);
void renderGame();
void setGameMode(int x,int y, int n, int dx, int dy, int d1x, int d1y,int dtx , int& BOARD_SIZE_X, int& BOARD_SIZE_Y, int& NumberOfMines, int& mineCountLeft, int& CountTileLeft, int& distance_x, int& distance_y, int& digit_x, int& digit_y, int& timeDigit_x);

// close SDL
void close();
