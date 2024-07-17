#include <SDL.h>
#include <SDL_image.h>
#include <vector>

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const int STRUM_NOTE_WIDTH = 100;
const int STRUM_NOTE_HEIGHT = 100;
const int SPACING = 20;
const int VERTICAL_OFFSET = 50;
const int PRESS_ANIM_OFFSET = 5;
const float PRESS_SCALE = 0.9f;

// OPTIONS!
bool downscroll = false; // Legit just downscroll, how else do you want me to explain it??

struct Note {
    int x, y;
    bool pressed;
};

void drawStrumNotes(SDL_Renderer* renderer, std::vector<Note>& notes, SDL_Texture* textures[]) {
    for (size_t i = 0; i < notes.size(); ++i) {
        SDL_Rect rect;
        rect.x = notes[i].x;
        rect.y = notes[i].y;
        rect.w = notes[i].pressed ? static_cast<int>(STRUM_NOTE_WIDTH * PRESS_SCALE) : STRUM_NOTE_WIDTH;
        rect.h = notes[i].pressed ? static_cast<int>(STRUM_NOTE_HEIGHT * PRESS_SCALE) : STRUM_NOTE_HEIGHT;

        if (notes[i].pressed) {
            rect.x += (STRUM_NOTE_WIDTH - rect.w) / 2;
            rect.y += (STRUM_NOTE_HEIGHT - rect.h) / 2;
        }

        SDL_RenderCopy(renderer, textures[i], nullptr, &rect);
    }
}

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

    SDL_Texture* textures[4];

    textures[0] = IMG_LoadTexture(renderer, "assets/images/notes/leftN.png");
    textures[1] = IMG_LoadTexture(renderer, "assets/images/notes/downN.png");
    textures[2] = IMG_LoadTexture(renderer, "assets/images/notes/upN.png");
    textures[3] = IMG_LoadTexture(renderer, "assets/images/notes/rightN.png");

    for (int i = 0; i < 4; ++i) {
        if (textures[i] == nullptr) {
            SDL_Log("Failed to load texture %d! IMG_Error: %s", i, IMG_GetError());
            return -1;
        }
    }

    std::vector<Note> notes(4);

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

        drawStrumNotes(renderer, notes, textures);

        SDL_RenderPresent(renderer);
    }

    for (int i = 0; i < 4; ++i) {
        SDL_DestroyTexture(textures[i]);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}
