#include "Gameplay.h"

Gameplay::Gameplay(SDL_Renderer* renderer, Menu& menu)
    : renderer(renderer) {
    strumNotes = new StrumNotes(renderer, menu.isDownscrollEnabled()); // Pass downscroll state from Menu
    strumNotes->loadTextures({
        "assets/images/notes/leftN.png",
        "assets/images/notes/downN.png",
        "assets/images/notes/upN.png",
        "assets/images/notes/rightN.png"
        });
}

Gameplay::~Gameplay() {
    delete strumNotes;
}

void Gameplay::handleEvent(SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
        case SDLK_a: strumNotes->pressKey(0); break;
        case SDLK_s: strumNotes->pressKey(1); break;
        case SDLK_k: strumNotes->pressKey(2); break;
        case SDLK_l: strumNotes->pressKey(3); break;
        case SDLK_LEFT: strumNotes->pressKey(0); break;
        case SDLK_DOWN: strumNotes->pressKey(1); break;
        case SDLK_UP: strumNotes->pressKey(2); break;
        case SDLK_RIGHT: strumNotes->pressKey(3); break;
        }
    }
    if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
        case SDLK_a: strumNotes->releaseKey(0); break;
        case SDLK_s: strumNotes->releaseKey(1); break;
        case SDLK_k: strumNotes->releaseKey(2); break;
        case SDLK_l: strumNotes->releaseKey(3); break;
        case SDLK_LEFT: strumNotes->releaseKey(0); break;
        case SDLK_DOWN: strumNotes->releaseKey(1); break;
        case SDLK_UP: strumNotes->releaseKey(2); break;
        case SDLK_RIGHT: strumNotes->releaseKey(3); break;
        }
    }
}

void Gameplay::update() {
    // sexy gaem logics here!!
}

void Gameplay::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    strumNotes->drawNotes();

    SDL_RenderPresent(renderer);
}
