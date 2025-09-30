#ifndef PIPELINE_H
#define PIPELINE_H

#include <iostream>
#include <glad/gl.h>
#include "shader.h"
#include <vector>

class Pipeline {
public:
    GLuint ID;
    Pipeline(GLuint vertexShader, GLuint fragmentShader);

    void AddShaderProgram(GLuint program);
    void Bind();
    void Unbind();
    void DestroyPipeline();
};

#endif
