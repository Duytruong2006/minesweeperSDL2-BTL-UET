#pragma once
#include<iostream>
#include<time.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>
#include<string>
#include <vector>
using namespace std;
class LTexture
{
public:
	//Initializes variables
	LTexture(SDL_Texture* _mTexture, int _mWidth, int _mHeight);

	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(string path);

	//Creates image from font string
	bool loadFromRenderedText(string textureText, SDL_Color textColor);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};
