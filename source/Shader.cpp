#include "Shader.h"

Shader::Shader(string vertex, string fragment)
{
    vertex_shader_file_ = vertex; vertex_shader_file_ += ".vs";
    fragment_shader_file_ = fragment; fragment_shader_file_ += ".fs";
    program_id_ = load_program(vertex_shader_file_.c_str(), fragment_shader_file_.c_str());
}

Shader::Shader(string name) : Shader(name, name)
{
}

int Shader::id()
{
    return program_id_;
}

int Shader::load_file(string path, string& content)
{
	ifstream ifs(path, ios::in);
	if(!ifs.is_open())
	{
		return 1;
	}

	string line;
	while(getline(ifs, line))
	{
		content += line + "\n";
	}
	ifs.close();
	return 0;
}

int Shader::load_shader(GLuint shaderId, const char* path)
{
	string shaderContent;

	load_file(path, shaderContent);
	char const* shaderContentPointer = shaderContent.c_str();
	glShaderSource(shaderId, 1, &shaderContentPointer, NULL);
	glCompileShader(shaderId);

	GLint result;
	int logLength;

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

	if(logLength > 0)
	{
		char log[logLength+1];
		log[logLength] = '\0';
		glGetShaderInfoLog(shaderId, logLength, NULL, log);
		std::cout << "shader log: " <<  log << std::endl;
	}

	return 0;
}

int Shader::load_program(const char* vertexShaderFile, const char* fragmentShaderFile)
{
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	load_shader(vertexShaderId, vertexShaderFile);

	load_shader(fragmentShaderId, fragmentShaderFile);


	GLuint programId = glCreateProgram();
	glAttachShader(programId, vertexShaderId);
	glAttachShader(programId, fragmentShaderId);

	glLinkProgram(programId);

	int result;
	int logLength;
	glGetProgramiv(programId, GL_LINK_STATUS, &result);
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);

	if(logLength > 0)
	{
		char log[logLength+1];
		log[logLength] = '\0';
		glGetProgramInfoLog(programId, logLength, NULL, log);
		cout << "link program log: " << log << endl;
	}

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	return programId;
}
