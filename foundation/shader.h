#ifndef SHADER_H
#define SHADER_H

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <glad/gl.h>

class Shader {
public:
    GLuint ID;
    GLenum type;
    Shader(const char *file, GLenum shaderType);

    void Activate();
    void Destroy();
};
#endif
