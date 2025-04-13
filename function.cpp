#include <bits/stdc++.h>
#include "Buttons.h"
#include "constant.h"
#include "Variables.h"
#include "function.h"
#include "Texture.h"
#include "Timer.h"
using namespace std;

vector<vector<LButton>> LButton(3,vector<LButton>(2));
LButton face;
LButton goBack;
LButton sound;
LTimer timer;

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

}
void loadMenuMedia()
{

}
