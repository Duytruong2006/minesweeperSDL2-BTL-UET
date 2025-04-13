#include "Variables.h"
#include "Buttons.h"
#include "function.h"
#include "constant.h"

LButton::LButton()
{
    mPosition.x = 0;
    mPosition.y = 0;
}

void LButton::setPosition(int x,int y)
{
    mPosition.x = x;
    mPosition.y = y;
}

void LButton::render(int i, int j)
{
    Tiles_image.render(mPosition.x, mPosition.y, &Tilesprites[sBoard[i][j]]);
}
void LButton::loseRender(int i, int j)
{
    Tiles_image.render(mPosition.x, mPosition.y, &Tilesprites[board[i][j]]);
}

void LButton::handleEventAgain(SDL_Event* e)
{
    if(e->type == SDL_MOUSEBUTTONDOWN)
    {
        int x,y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;
        if(x < mPosition.x || x > mPosition.x + 42 || y < mPosition.y || y > mPosition.y + 42)
        {
            inside = false;
        }
        if(inside && e->button.button ==  SDL_BUTTON_LEFT)
        {
            playAgain();
        }
    }

}

void LButton::handleEventBack(SDL_Event* e)
{
    if(e->type == SDL_MOUSEBUTTONDOWN)
    {
        int x,y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;
        if(x < mPosition.x || x > mPosition.x + 50 || y < mPosition.y || y > mPosition.y + 50)
        {
            inside = false;
        }
        if(inside && e->button.button == SDL_BUTTON_LEFT)
        {
            SDL_SetWindowSize(window, SCREEN_WIDTH, SCREEN_HEIGHT);
            isRunning = false;
            customMode = false;
            isChoosing = true;
            isWinning = false;
            lose = false;
            easy = false;
            medium = false;
            hard = false;
            cus = false;
        }
    }
}
void LButton::handleEventMute(SDL_Event* e)
{
    if(e->type == SDL_MOUSEBUTTONDOWN)
    {
        int x,y;
        SDL_GetMouseState(&x, &y);
        bool inside = true;
        if(x < mPosition.x || x > mPosition.x + 50 || y < mPosition.y || y > mPosition.y + 50)
        {
            inside = false;
        }
        if(inside && e->button.button == SDL_BUTTON_LEFT)
        {
            if(mute = false)
            {
                mute = true;
            }
            else
            {
                mute = false;
            }
        }
    }
}
void LButton::handleEvent(SDL_Event* e)
{
    if(e -> SDL_MOUSEMOTION || e -> SDL_MOUSEBUTTONUP || e -> SDL_MOUSEBUTTONDOWN)
    {
        int x,y;
        SDL_GetModState(&x,&y);
        int i = (x - distance_x) / TILE_SIZE;
        int j = (y - distance_y) / TILE_SIZE;
        bool inside = true;
        if(x < mPosition.x || x > mPosition.x + TILE_SIZE || y < mPosition.y || y > mPosition.y + TILE_SIZE)
        {
            inside = false;
        }
        if(inside)
        {
            switch(e->button.button)
            {
            case SDL_BUTTON_LEFT:
            {
                reveal(i,j);
                if(CountTileLeft == NumberOfMines)
                {
                    Mix_PlayMusic(winMusic, 1);
                }
                if(sBoard[i][j] == 9)
                {
                    lose = true;
                    Mix_PlayMusic(loseMusic, 1);
                }
                else
                {
                    Mix_PlayChannel(-1, click, 0);
                }
                break;
            }
            case SDL_BUTTON_RIGHT:
            {
                Mix_PlayChannel(-1, click, 0);
                if(sBoard[i][j] >= 10)
                {
                    if(sBoard[i][j] == 10)
                    {
                        sBoard[i][j] = 11;
                        mineCountLeft--;
                    }
                    if(sBoard[i][j] == 11)
                    {
                        sBoard[i][j] = 10;
                        mineCountLeft++;
                    }
                }
                else break;
            }
            break;
            }
        }
    }
}
