#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Menu.h"
#include "Gameplay.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

enum GameState {
    MENU,
    GAMEPLAY,
    OPTIONS
};

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return -1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        SDL_Log("SDL_image could not initialize! IMG_Error: %s", IMG_GetError());
        return -1;
    }

    if (TTF_Init() == -1) {
        SDL_Log("SDL_ttf could not initialize! TTF_Error: %s", TTF_GetError());
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Swagger 4K",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Log("Window could not be created! SDL_Error: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Renderer could not be created! SDL_Error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    GameState currentState = MENU;
    Menu menu(renderer);
    Gameplay* gameplay = nullptr;

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            switch (currentState) {
            case MENU:
                menu.handleEvent(e);
                if (menu.isSinglePlayerSelected()) {
                    currentState = GAMEPLAY;
                    gameplay = new Gameplay(renderer);
                }
                if (menu.isOptionsSelected()) {
                    // Handle options selection
                }
                break;
            case GAMEPLAY:
                gameplay->handleEvent(e);
                break;
            case OPTIONS:
                // Handle options events
                break;
            }
        }

        switch (currentState) {
        case MENU:
            menu.update();
            menu.render();
            break;
        case GAMEPLAY:
            gameplay->update();
            gameplay->render();
            break;
        case OPTIONS:
            // Render options menu
            break;
        }
    }

    delete gameplay;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}
