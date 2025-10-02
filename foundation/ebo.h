#ifndef EBO_H
#define EBO_H

#include <glad/gl.h>
#include <iostream>

class EBO {
public:
    GLuint ID;
    EBO(GLuint* indices, GLsizeiptr size);

    void Bind();
    void Unbind();
    void Delete();
};
#endif // !EBO_H
