#ifndef SHADER_H
#define SHADER_H

#include "default.h"
#include "util.h"
#include <fstream>

class Shader
{
    public:
        Shader(string vertex, string fragment);
        Shader(string name);
        int id();
    protected:
        GLuint program_id_;
        string vertex_shader_file_;
        string fragment_shader_file_;
        
        int load_file(string path, string& content);
        int load_shader(GLuint shaderId, const char* path);
        int load_program(const char* vertexShaderFile, const char* fragmentShaderFile);
    private:
};

#endif // SHADER_H

