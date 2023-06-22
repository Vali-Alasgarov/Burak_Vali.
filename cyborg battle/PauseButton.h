#ifndef PAUSEBUTTON_H
#define PAUSEBUTTON_H

#include <SDL.h>

class PauseButton {
public:
    PauseButton(SDL_Renderer* renderer);

    void handleEvent(SDL_Event& event);
    void render();
    bool isGamePaused() const;

private:
    void togglePause();

    SDL_Renderer* renderer;
    SDL_Rect buttonRect;
    bool isPaused;
};

#endif  // PAUSEBUTTON_H
