#include "cleanup.h"
#include "res_path.h"
#include "drawing_functions.h"
#include "SDL_mixer.h"
#include "globals.h"
#include "game.h"
#include <cstdlib> //srand, rand
#include <ctime> //time
#include "PauseButton.h"

int main(int argc, char** argv) {
    // Set the random seed for the random number sequence
    srand(time(0));

    // Setup SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        cout << "Error initializing SDL" << endl;
        return 1;
    }

    // Setup window
    SDL_Window* window = SDL_CreateWindow("Cyborg Battle", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        Globals::ScreenWidth * Globals::ScreenScale,
        Globals::ScreenHeight * Globals::ScreenScale, SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        SDL_Quit();
        cout << "Window error" << endl;
        return 1;
    }

    // Setup renderer
    Globals::renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (Globals::renderer == nullptr) {
        cleanup(window);
        SDL_Quit();
        cout << "Renderer error" << endl;
        return 1;
    }
    // Set the size to draw things at, before scaling it to the screen size dimensions mentioned in createWindow
    SDL_RenderSetLogicalSize(Globals::renderer, Globals::ScreenWidth, Globals::ScreenHeight);

    // Initialise SDL_image
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        SDL_Quit();
        cout << "SDL_image did not initialise" << endl;
        return 1;
    }

    // Initialise SDL_ttf
    if (TTF_Init() != 0) {
        SDL_Quit();
        cout << "SDL_ttf did not initialise" << endl;
        return 1;
    }

    // Initialise SDL_mixer
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        SDL_Quit();
        cout << "Mixer did not initialise" << endl;
        return 1;
    }

    // Create a pause button instance
    PauseButton pauseButton(Globals::renderer);

    Game game;

    bool quit = false;
    SDL_Event event;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                pauseButton.handleEvent(event);
            }
        }

        if (!pauseButton.isGamePaused()) {
            game.update();  // Update game logic here if not paused
        }

        // Clear the screen
        SDL_RenderClear(Globals::renderer);

        // Draw game objects here

        // Render the pause button
        pauseButton.render();

        // Show the rendered frame on the window
        SDL_RenderPresent(Globals::renderer);
    }

    // Cleanup and quit SDL
    cleanup(Globals::renderer);
    cleanup(window);
    SDL_Quit();

    return 0;
}
