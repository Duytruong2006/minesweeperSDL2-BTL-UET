#pragma once
#include "Timer.h"
#include <SDL.h>
using namespace std;

// initialization func
void init();
void loadmedia();
void loadMenuMedia();

// close SDL
void close();

//initialization game
void Createboard();
void createMenu();
void createModeMenu();
void CustomMode();
void showMenu();
void showModeChoice();
void setButtonPosition();

//ingame func
void isPlayerWinning();
void MineManager();
void GameManager();
void playAgain();
string getTime();
string getFileScoreName();
void getScore();
void TimeManager();
void renderButton();
void handleEvent();
void reveal(int i, int j);
void renderGame();
void setGameMode(int x,int y, int n, int dx, int dy, int d1x, int d1y, int& BOARD_SIZE_X, int& BOARD_SIZE_, int& NumberOfMines, int& mineCountLeft, int& CountTileLeft, int& distance_x, int& distance_y, int& digit_x, int& digit_y, int& timeDigit_x);
