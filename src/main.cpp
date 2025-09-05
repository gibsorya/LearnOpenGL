#include "version.h"

#include <glad/gl.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <glm/glm.hpp>

#include <iostream>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << argv[0] << " Version " << PROJECT_VERSION_MAJOR << "." << PROJECT_VERSION_MINOR
                  << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
    }

    bool done = false;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window =
        SDL_CreateWindow("OpenGL Window", 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!window) {
        std::cerr << "CreateWindow Error" << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    SDL_Event event;

    while (!done) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
                break;
            }
        }
    }

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
