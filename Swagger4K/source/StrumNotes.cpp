#include "StrumNotes.h"
#include <SDL_image.h>

StrumNotes::StrumNotes(SDL_Renderer* renderer, bool downscroll)
    : renderer(renderer), downscroll(downscroll) {
    int y_position = downscroll ? (720 - STRUM_NOTE_HEIGHT - VERTICAL_OFFSET) : VERTICAL_OFFSET;
    for (int i = 0; i < 4; ++i) {
        notes.push_back({
            static_cast<int>((1280 - (4 * (STRUM_NOTE_WIDTH + SPACING) - SPACING)) / 2 + i * (STRUM_NOTE_WIDTH + SPACING)),
            y_position,
            false
            });
    }
}

StrumNotes::~StrumNotes() {
    for (auto texture : textures) {
        SDL_DestroyTexture(texture);
    }
}

void StrumNotes::loadTextures(const std::vector<std::string>& texturePaths) {
    for (const auto& path : texturePaths) {
        SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
        if (texture == nullptr) {
            SDL_Log("Failed to load texture %s! IMG_Error: %s", path.c_str(), IMG_GetError());
            return;
        }
        textures.push_back(texture);
    }
}

void StrumNotes::drawNotes() {
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

void StrumNotes::pressKey(int index) {
    if (index >= 0 && index < notes.size()) {
        notes[index].pressed = true;
    }
}

void StrumNotes::releaseKey(int index) {
    if (index >= 0 && index < notes.size()) {
        notes[index].pressed = false;
    }
}
