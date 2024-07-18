#include <SDL.h>
#include <SDL_image.h>
#include "StrumNotes.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// OPTIONS!
bool downscroll = false; // Legit just downscroll, how else do you want me to explain it??

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
        return -1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        SDL_Log("SDL_image could not initialize! IMG_Error: %s", IMG_GetError());
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

    StrumNotes strumNotes(renderer, downscroll);
    strumNotes.loadTextures({
        "assets/images/notes/leftN.png",
        "assets/images/notes/downN.png",
        "assets/images/notes/upN.png",
        "assets/images/notes/rightN.png"
        });

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_a: strumNotes.pressKey(0); break;
                case SDLK_s: strumNotes.pressKey(1); break;
                case SDLK_k: strumNotes.pressKey(2); break;
                case SDLK_l: strumNotes.pressKey(3); break;
                }
            }
            if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                case SDLK_a: strumNotes.releaseKey(0); break;
                case SDLK_s: strumNotes.releaseKey(1); break;
                case SDLK_k: strumNotes.releaseKey(2); break;
                case SDLK_l: strumNotes.releaseKey(3); break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        strumNotes.drawNotes();

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
