#include "pipeline.h"
#include "version.h"

#include <glad/gl.h>

#include "error.h"
#include "shader.h"
#include "vbo.h"
#include "vao.h"
#include "ebo.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#include <glm/glm.hpp>

#include <iostream>

// clang-format off
GLfloat vertices[] = {
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left 
};

GLuint indices[] = {
    0, 1, 3,
    1, 2, 3
};
// clang-format on

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

    std::cout << "Running shaders..." << "\n";


    Shader vertexShader("default.vert", GL_VERTEX_SHADER);
    Shader fragmentShader("default.frag", GL_FRAGMENT_SHADER);
    
    std::cout << "Creating pipeline..." << "\n";
    Pipeline pipeline(vertexShader.ID, fragmentShader.ID);
    // Fence Sync Object
    GLsync fence = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);

    // Inserts a "fence" into the command stream. Allows the CPU to "wait" for the GPU to finish commands.
    // The CPU "waits" for the GPU when glCientWaitSync or glWaitSync is called. This is great for multi-threading.
    // A fence blocks a CPU thread until the GPU commands are done executing.
    
    // VAO + VBO
    VAO VAO;
    VAO.Bind();
    VBO VBO(vertices, sizeof(vertices));
    EBO EBO(indices, sizeof(indices));

    VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);

    VAO.Unbind();
    VBO.Unbind();
    EBO.Unbind();

    SDL_Event event;

    
    while (!done) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_EVENT_QUIT) {
                std::cout << "DONE" << "\n";
                done = true;
                break;
            }
        }

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        pipeline.Bind();
        VAO.Bind();
        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

        SDL_GL_SwapWindow(window);
    }

    glDeleteSync(fence);
    VBO.Destroy();
    VAO.Destroy();
    pipeline.DestroyPipeline();
    fragmentShader.Destroy();
    vertexShader.Destroy();
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
