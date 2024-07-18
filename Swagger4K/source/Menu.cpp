#include "Menu.h"
#include <SDL_image.h> // Include SDL_image header

Menu::Menu(SDL_Renderer* renderer)
    : renderer(renderer), singlePlayerSelected(false), optionsSelected(false),
    singlePlayerButtonScale(1.0f), optionsButtonScale(1.0f) {

    singlePlayerButton = { 540, 300, 200, 50 };
    optionsButton = { 540, 400, 200, 50 };

    font = TTF_OpenFont("assets/fonts/arial.ttf", 24);
    if (font == nullptr) {
        SDL_Log("Failed to load font! TTF_Error: %s", TTF_GetError());
    }

    buttonTexture = loadTexture("assets/images/menus/button.png");
    if (buttonTexture == nullptr) {
        SDL_Log("Failed to load button texture! SDL_Error: %s", SDL_GetError());
    }

    backgroundTexture = loadTexture("assets/images/menus/bg.png");
    if (backgroundTexture == nullptr) {
        SDL_Log("Failed to load background texture! SDL_Error: %s", SDL_GetError());
    }
}

Menu::~Menu() {
    SDL_DestroyTexture(buttonTexture);
    SDL_DestroyTexture(backgroundTexture);
    TTF_CloseFont(font);
}

void Menu::handleEvent(SDL_Event& e) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        if (x >= singlePlayerButton.x && x <= singlePlayerButton.x + singlePlayerButton.w &&
            y >= singlePlayerButton.y && y <= singlePlayerButton.y + singlePlayerButton.h) {
            singlePlayerSelected = true;
        }
        if (x >= optionsButton.x && x <= optionsButton.x + optionsButton.w &&
            y >= optionsButton.y && y <= optionsButton.y + optionsButton.h) {
            optionsSelected = true;
        }
    }
}

void Menu::update() {
    const float animationSpeed = 0.05f;
    if (singlePlayerSelected) {
        singlePlayerButtonScale = 1.0f + animationSpeed;
        if (singlePlayerButtonScale > 1.1f) singlePlayerButtonScale = 1.0f;
    }
    else {
        singlePlayerButtonScale = 1.0f;
    }

    if (optionsSelected) {
        optionsButtonScale = 1.0f + animationSpeed;
        if (optionsButtonScale > 1.1f) optionsButtonScale = 1.0f;
    }
    else {
        optionsButtonScale = 1.0f;
    }
}

void Menu::render() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_Rect bgRect = { 0, 0, 1280, 720 };
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, &bgRect);

    SDL_Rect spButtonDest = {
        singlePlayerButton.x - static_cast<int>((singlePlayerButton.w * (singlePlayerButtonScale - 1.0f)) / 2),
        singlePlayerButton.y - static_cast<int>((singlePlayerButton.h * (singlePlayerButtonScale - 1.0f)) / 2),
        static_cast<int>(singlePlayerButton.w * singlePlayerButtonScale),
        static_cast<int>(singlePlayerButton.h * singlePlayerButtonScale)
    };
    SDL_Rect optionsButtonDest = {
        optionsButton.x - static_cast<int>((optionsButton.w * (optionsButtonScale - 1.0f)) / 2),
        optionsButton.y - static_cast<int>((optionsButton.h * (optionsButtonScale - 1.0f)) / 2),
        static_cast<int>(optionsButton.w * optionsButtonScale),
        static_cast<int>(optionsButton.h * optionsButtonScale)
    };

    SDL_RenderCopy(renderer, buttonTexture, nullptr, &spButtonDest);
    SDL_RenderCopy(renderer, buttonTexture, nullptr, &optionsButtonDest);

    renderText("Single Player", spButtonDest);
    renderText("Options", optionsButtonDest);

    SDL_RenderPresent(renderer);
}

bool Menu::isSinglePlayerSelected() const {
    return singlePlayerSelected;
}

bool Menu::isOptionsSelected() const {
    return optionsSelected;
}

void Menu::renderText(const char* text, SDL_Rect& rect) {
    SDL_Color textColor = { 255, 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = { rect.x + (rect.w - textSurface->w) / 2, rect.y + (rect.h - textSurface->h) / 2, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, nullptr, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}

SDL_Texture* Menu::loadTexture(const char* path) {
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == nullptr) {
        SDL_Log("Unable to load image %s! SDL_image Error: %s", path, IMG_GetError());
    }
    else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == nullptr) {
            SDL_Log("Unable to create texture from %s! SDL Error: %s", path, SDL_GetError());
        }
        SDL_FreeSurface(loadedSurface);
    }
    return newTexture;
}
