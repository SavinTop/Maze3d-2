#include "shader.hpp"

namespace oglw{

Shader::Shader() 
{
    
}

Shader::Shader(const std::string VertexShaderText, const std::string FragmentShaderText) 
{
    setParams(vertexShaderText, fragmentShaderText);
}

unsigned int Shader::getProgramID() 
{
    return program_;
}

int Shader::getUniformLocation(const std::string& name) 
{
    return glGetUniformLocation(program_, name.c_str());
}

void Shader::load() 
{
    CreateShader(GL_VERTEX_SHADER, vertexShader_, this->vertexShaderText);
	CreateShader(GL_FRAGMENT_SHADER, fragmentShader_, this->fragmentShaderText);
	CreateProgram();
}

void Shader::unload() 
{
    glDetachShader(program_, vertexShader_);
	glDetachShader(program_, fragmentShader_);

    glDeleteShader(vertexShader_);
	glDeleteShader(fragmentShader_);
	glDeleteProgram(program_);

	vertexShader_ = 0;
	fragmentShader_ = 0;
	program_ = 0;
}

void Shader::setParams(const std::string VertexShaderText, const std::string FragmentShaderText) 
{
    this->vertexShaderText = VertexShaderText;
    this->fragmentShaderText = FragmentShaderText;
}

void Shader::bind() 
{
    glUseProgram(program_);
}

void Shader::unbind() 
{
    glUseProgram(0);
}

void Shader::CreateShader(unsigned int Type, unsigned int& id, const std::string& code) 
{
    id = glCreateShader(Type);
	const char* c_str = code.c_str();
	glShaderSource(id, 1, &c_str, 0);
	glCompileShader(id);

	GLint success = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (success == GL_FALSE)
	{
		int maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		std::cout<<errorLog.data();

		glDeleteShader(id); 
		return;
	}
}

void Shader::CreateProgram() 
{
    program_ = glCreateProgram();
	glAttachShader(program_, vertexShader_);
	glAttachShader(program_, fragmentShader_);
	glLinkProgram(program_);

	int isLinked = 0;
	glGetProgramiv(program_, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		int maxLength = 0;
		glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program_, maxLength, &maxLength, &infoLog[0]);

		std::cout<<infoLog.data();

		glDeleteProgram(program_);
		glDeleteShader(vertexShader_);
		glDeleteShader(fragmentShader_);

		return;
	}
}

}