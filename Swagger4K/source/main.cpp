#include <SDL.h>
#include <vector>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int STRUM_NOTE_WIDTH = 50;
const int STRUM_NOTE_HEIGHT = 20;
const int SPACING = 20; 
const int VERTICAL_OFFSET = 50;
const int PRESS_ANIM_OFFSET = 5; 

struct Note {
    int x, y;
    bool pressed;
};

void drawStrumNotes(SDL_Renderer* renderer, std::vector<Note>& notes) {
    for (auto& note : notes) {
        SDL_Rect rect;
        rect.x = note.x;
        rect.y = note.pressed ? note.y + PRESS_ANIM_OFFSET : note.y;
        rect.w = STRUM_NOTE_WIDTH;
        rect.h = STRUM_NOTE_HEIGHT;

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
    }
}

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL_Error: %s", SDL_GetError());
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

    std::vector<Note> notes(4);
    bool downscroll = false;

    int y_position = downscroll ? (SCREEN_HEIGHT - STRUM_NOTE_HEIGHT - VERTICAL_OFFSET) : VERTICAL_OFFSET;
    for (int i = 0; i < notes.size(); ++i) {
        notes[i] = {
            static_cast<int>((SCREEN_WIDTH - (notes.size() * (STRUM_NOTE_WIDTH + SPACING) - SPACING)) / 2 + i * (STRUM_NOTE_WIDTH + SPACING)),
            y_position,
            false
        };
    }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_a: notes[0].pressed = true; break;
                case SDLK_s: notes[1].pressed = true; break;
                case SDLK_k: notes[2].pressed = true; break;
                case SDLK_l: notes[3].pressed = true; break;
                }
            }
            if (e.type == SDL_KEYUP) {
                switch (e.key.keysym.sym) {
                case SDLK_a: notes[0].pressed = false; break;
                case SDLK_s: notes[1].pressed = false; break;
                case SDLK_k: notes[2].pressed = false; break;
                case SDLK_l: notes[3].pressed = false; break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        drawStrumNotes(renderer, notes);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
