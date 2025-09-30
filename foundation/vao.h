#ifndef VAO_H
#define VAO_H

#include "vbo.h"
#include <glad/gl.h>

class VAO {
public:
    GLuint ID;
    VAO();

    void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
    void Bind();
    void Unbind();
    void Destroy();
};
#endif // !VAO_H
