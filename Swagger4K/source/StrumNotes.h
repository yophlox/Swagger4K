#ifndef STRUM_NOTES_H
#define STRUM_NOTES_H

#include <SDL.h>
#include <vector>
#include <string>

class StrumNotes {
public:
    struct Note {
        int x, y;
        bool pressed;
    };

    StrumNotes(SDL_Renderer* renderer, bool downscroll);
    ~StrumNotes();

    void loadTextures(const std::vector<std::string>& texturePaths);
    void drawNotes();

    void pressKey(int index);
    void releaseKey(int index);

private:
    SDL_Renderer* renderer;
    std::vector<SDL_Texture*> textures;
    std::vector<Note> notes;
    bool downscroll;

    const int STRUM_NOTE_WIDTH = 100;
    const int STRUM_NOTE_HEIGHT = 100;
    const int SPACING = 20;
    const int VERTICAL_OFFSET = 50;
    const float PRESS_SCALE = 0.9f;
};

#endif // STRUM_NOTES_H
