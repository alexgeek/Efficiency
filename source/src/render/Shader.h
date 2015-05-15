#ifndef SHADER_H
#define SHADER_H

#include "../default.h"
#include "../util.h"
#include <fstream>

class Shader
{
    public:
        Shader(std::string vertex, std::string fragment);
        Shader(std::string name);
        GLuint id();
    protected:
        GLuint program_id_;
        std::string vertex_shader_file_;
        std::string fragment_shader_file_;
        
        int load_file(std::string path, std::string& content);
        int load_shader(GLuint shaderId, const char* path);
        GLuint load_program(const char* vertexShaderFile, const char* fragmentShaderFile);
    private:
};

#endif // SHADER_H

