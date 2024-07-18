#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>

class Menu {
public:
    Menu(SDL_Renderer* renderer);
    ~Menu();

    void handleEvent(SDL_Event& e);
    void render();
    void update();

    bool isSinglePlayerSelected() const;
    bool isOptionsSelected() const;
    bool isDownscrollEnabled() const;

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
    SDL_Texture* buttonTexture;
    SDL_Texture* backgroundTexture;
    SDL_Rect singlePlayerButton;
    SDL_Rect optionsButton;
    SDL_Rect backButton;
    bool singlePlayerSelected;
    bool optionsSelected;
    bool optionsMenuOpen;
    bool downscroll;

    float singlePlayerButtonScale;
    float optionsButtonScale;
    float backButtonScale;

    void renderMainMenu();
    void renderOptionsMenu();
    void renderText(const char* text, SDL_Rect& rect);
    SDL_Texture* loadTexture(const char* path);
};

#endif // MENU_H
