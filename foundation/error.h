#ifndef OPENGL_DEBUG_CALLBACK
#define OPENGL_DEBUG_CALLBACK

#include <SDL3/SDL_opengl.h>

#ifdef __cplusplus
extern "C" {
#endif

void GLAPIENTRY DebugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                         GLsizei length, const GLchar *message,
                         const void *userParam);

#ifdef __cplusplus
}
#endif

#endif
