#include "shader.h"

const std::string SHADERS_PATH = SHADERS_DIR;

std::string get_file_contents(const char *filename) {

    std::string shaderPath = SHADERS_PATH + "/" + filename;
    std::cout << "path: " << shaderPath << "\n";
  std::ifstream in(shaderPath, std::ios::binary);
  if (in) {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return (contents);
  }
  throw(errno);
}


Shader::Shader(const char* file, GLenum shaderType) {
    type = shaderType;
    
    std::string fileContents = get_file_contents(file);
    const char* source = fileContents.c_str();

    ID = glCreateShaderProgramv(shaderType, 1, &source);

    // GLuint shader = glCreateShader(shaderType);

    // glShaderSource(shader, 1, &source, NULL);

    // glCompileShader(shader);

    // ID = glCreateProgram();

    // glAttachShader(ID, shader);

    // glLinkProgram(ID);

    //glDeleteShader(shader);
}

void Shader::Activate() { glUseProgram(ID); }
void Shader::Destroy() { glDeleteProgram(ID); }
