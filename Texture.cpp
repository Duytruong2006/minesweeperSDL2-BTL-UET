#pragma once
#include "Texture.h"
#include "Variables.h"
using namespace std;

LTexture::LTexture(SDL_Texture* _mTexture, int _mWidth, int _mHeight)
{
    mTexture = _mTexture;
    mWidth = _mWidth;
    mHeight = _mHeight;
}

void LTexture::free()
{
    if(mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

LTexture::~LTexture()
{
    free();
}

int LTexture::getHeight()
{
    return mHeight;
}

int LTexture::getWidth()
{
    return mWidth;
}

void LTexture::render(int x,int y,SDL_Rect* clip)
{
    SDL_Rect renderquad = {x, y, mWidth, mHeight};
    if(clip != NULL)
    {
        renderquad.w = clip->w;
        renderquad.h = clip->h;
    }
    SDL_RenderCopy(renderer, mTexture, clip , &renderquad);
}

bool LTexture::loadFromFile(string path)
{
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
        cout << "fail to load the image" << path.c_str() << IMG_GetError() << endl;
    }
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(newTexture == NULL)
        {
            cout << "fail to create a newTexture" << path.c_str() << SDL_GetError() << endl;
        }
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

bool LTexture::loadFromRenderedText(string textureText, SDL_Color textColor)
{
    free();
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
    if(textSurface == NULL)
    {
        cout << "fail to render text surface" << TTF_GetError() << endl;
    }
    else
    {
        mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(mTexture == NULL)
        {
            cout << "fail to create texture form rendered text" << SDL_GetError() << endl;
        }
        else
        {
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }
        SDL_FreeSurface(textSurface);
    }
    return mTexture != NULL;
}
