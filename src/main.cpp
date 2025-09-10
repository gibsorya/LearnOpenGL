#include "version.h"

#include <glad/gl.h>

#include "error.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <glm/glm.hpp>

#include <iostream>

GLfloat vertices[] = {-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
                      0.5f,  -0.5f * float(sqrt(3)) / 3, 0.0f,
                      0.0f,  0.5f * float(sqrt(3)) / 3,  0.0f};

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << argv[0] << " Version " << PROJECT_VERSION_MAJOR << "." << PROJECT_VERSION_MINOR
                  << std::endl;
        std::cout << "Usage: " << argv[0] << " number" << std::endl;
    }

    bool done = false;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    SDL_Window *window =
        SDL_CreateWindow("OpenGL Window", 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!window) {
        std::cerr << "CreateWindow Error" << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);

    if(!context) {
        std::cerr << "CreateContext Error" << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    gladLoadGL((GLADloadfunc) SDL_GL_GetProcAddress);
    glViewport(0, 0, 640, 480);

    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if(flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(DebugMessageCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    // Fence Sync Object
    GLsync fence = glFenceSync(GL_SYNC_FENCE, 0);

    SDL_Event event;

    while (!done) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
                break;
            }
        }
    }

    glDeleteSync(fence);

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
