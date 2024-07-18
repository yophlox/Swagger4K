#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <SDL.h>
#include "StrumNotes.h"
#include "Menu.h"

class Gameplay {
public:
    Gameplay(SDL_Renderer* renderer, Menu& menu);
    ~Gameplay();

    void handleEvent(SDL_Event& e);
    void update();
    void render();

private:
    SDL_Renderer* renderer;
    StrumNotes* strumNotes;
};

#endif // GAMEPLAY_H
