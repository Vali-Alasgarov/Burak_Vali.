#include "PauseButton.h"

PauseButton::PauseButton(SDL_Renderer* renderer)
    : renderer(renderer)
{
    buttonRect = { 10, 10, 50, 50 };
    isPaused = false;
}

void PauseButton::handleEvent(SDL_Event& event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int mouseX = event.button.x;
        int mouseY = event.button.y;
        if (mouseX >= buttonRect.x && mouseX <= buttonRect.x + buttonRect.w &&
            mouseY >= buttonRect.y && mouseY <= buttonRect.y + buttonRect.h) {
            togglePause();
        }
    }
    else if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_p) { // Press 'P' to toggle pause
            togglePause();
        }
    }
}

void PauseButton::render()
{
    if (isPaused) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }
    else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
    SDL_RenderFillRect(renderer, &buttonRect);
}

bool PauseButton::isGamePaused() const
{
    return isPaused;
}

void PauseButton::togglePause()
{
    isPaused = !isPaused;
}
