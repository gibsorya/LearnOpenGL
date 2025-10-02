#include "ebo.h"

EBO::EBO(GLuint* indices, GLsizeiptr size) {
    std::cout << "creating EBO..." << "\n";
    glGenBuffers(1, &ID);
    Bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

void EBO::Bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void EBO::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::Delete() {
    glDeleteBuffers(1, &ID);
}
