#include <glad/gl.h>

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <glm/glm.hpp>

#include "ebo.h"
#include "error.h"
#include "pipeline.h"
#include "shader.h"
#include "vao.h"
#include "vbo.h"

#include <iostream>

float vertices[] = {0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f, -0.5f, 0.5f, 0.0f};

unsigned int indices[] = {0, 1, 3, 1, 2, 3};

int main(int argc, char* argv[]) {
    bool done = false;
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    SDL_Window* window = SDL_CreateWindow("Hello Triangle", 1280, 920, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!window) {
        std::cerr << "Error creating window: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);

    if (!context) {
        std::cerr << "CreateContext Error" << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress);
    glViewport(0, 0, 1280, 920);

    int flags;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if (flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(DebugMessageCallback, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    Shader vertexShader("default.vert", GL_VERTEX_SHADER);
    Shader fragmentShader("default.frag", GL_FRAGMENT_SHADER);

    Pipeline pipeline(vertexShader.ID, fragmentShader.ID);

    VAO vao;
    vao.Bind();
    VBO vbo(vertices, sizeof(vertices));
    EBO ebo(indices, sizeof(indices));
    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    vao.Unbind();
    vbo.Unbind();
    ebo.Unbind();

    SDL_Event event;

    while (!done) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_EVENT_QUIT) {
                done = true;
                break;
            }
        }

        glClearColor(0.4f, 0.2f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        pipeline.Bind();
        vao.Bind();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        vao.Unbind();

        SDL_GL_SwapWindow(window);
    }

    ebo.Delete();
    vbo.Destroy();
    vao.Destroy();
    pipeline.DestroyPipeline();
    fragmentShader.Destroy();
    vertexShader.Destroy();

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
