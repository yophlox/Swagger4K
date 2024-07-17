#include <iostream>
#include <SDL.h>
#undef main
#include <stdio.h>

using namespace std;

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

bool init();
bool loadMedia();
void close();
SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gSwaggerMain = NULL;

bool init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		gWindow = SDL_CreateWindow("Swagger 4K", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gScreenSurface = SDL_GetWindowSurface(gWindow);
		}
	}

	return success;
}

bool loadMedia()
{
	bool success = true;

	gSwaggerMain = SDL_LoadBMP("assets/images/test/bf.bmp");
	if (gSwaggerMain == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", "assets/images/test/bf.bmp", SDL_GetError());
		success = false;
	}

	return success;
}

void close()
{
	SDL_FreeSurface(gSwaggerMain);
	gSwaggerMain = NULL;

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	SDL_Quit();
}


int main() {
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			SDL_BlitSurface(gSwaggerMain, NULL, gScreenSurface, NULL);
			SDL_UpdateWindowSurface(gWindow);
			SDL_Event e; bool quit = false; while (quit == false) { while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) quit = true; } }
		}
	}

	close();

	return 0;
}