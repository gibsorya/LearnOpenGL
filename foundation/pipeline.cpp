#include "pipeline.h"

Pipeline::Pipeline(GLuint vertexShader, GLuint fragmentShader) {
    glGenProgramPipelines(1, &ID);

    glUseProgramStages(ID, GL_VERTEX_SHADER_BIT, vertexShader);
    glUseProgramStages(ID, GL_FRAGMENT_SHADER_BIT, fragmentShader);

    GLchar log[2048];

    glGetProgramInfoLog(vertexShader, 2048, NULL, log);
    std::cout << log << "\n";

    glGetProgramInfoLog(fragmentShader, 2048, NULL, log);
    std::cout << log << "\n";

    // GLint location = glGetUniformLocation(fragmentShader, "color");
    Bind(); 
}

void Pipeline::Bind() {
    glBindProgramPipeline(ID);
}

void Pipeline::Unbind() {
    glBindProgramPipeline(0);
}

void Pipeline::DestroyPipeline() {
    glDeleteProgramPipelines(1, &ID);
}
