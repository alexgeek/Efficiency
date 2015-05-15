#include "Shader.h"

Shader::Shader(std::string vertex, std::string fragment)
{
    vertex_shader_file_ = vertex; vertex_shader_file_ = "assets/shaders/" + vertex_shader_file_ + ".vs"; // TODO if not already
    fragment_shader_file_ = fragment; fragment_shader_file_ = "assets/shaders/" + fragment_shader_file_ + ".fs"; // TODO ditto
    program_id_ = load_program(vertex_shader_file_.c_str(), fragment_shader_file_.c_str());
}

Shader::Shader(std::string name) : Shader(name, name)
{
}

GLuint Shader::id()
{
    return program_id_;
}

int Shader::load_file(std::string path, std::string& content)
{
	using namespace std;
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

// TODO handle failure gracefully when shader not found, e.g. default shader
int Shader::load_shader(GLuint shaderId, const char* path)
{
	std::string shaderContent;

	load_file(path, shaderContent);
	char const* shaderContentPointer = shaderContent.c_str();
	glShaderSource(shaderId, 1, &shaderContentPointer, NULL);
	glCompileShader(shaderId);

	GLint result;
	int logLength;

	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);

	if(logLength > 1)
	{
		char log[logLength+1];
		log[logLength] = '\0';
		glGetShaderInfoLog(shaderId, logLength, NULL, log);
		std::cout << "Shader log: " <<  log << std::endl;
	}

	return 0;
}

GLuint Shader::load_program(const char* vertexShaderFile, const char* fragmentShaderFile)
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

	if(logLength > 1)
	{
		char log[logLength+1];
		log[logLength] = '\0';
		glGetProgramInfoLog(programId, logLength, NULL, log);
		std::cout << "Program log: " << log << std::endl;
	}

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	return programId;
}
