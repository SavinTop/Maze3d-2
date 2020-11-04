#include "shader.hpp"

namespace res::ogl{

ShaderProgram::ShaderProgram(const std::string VertexShaderPath, const std::string FragmentShaderPath, const std::string pname)
	:OpenGLResource(), 
	fragmentShader_(0), 
	vertexShader_(0), 
	program_(0)
{
	setParams(VertexShaderPath, FragmentShaderPath, pname);
}

void ShaderProgram::load(){
	if(loaded = subResources_.isLoaded()){
		CreateShader(GL_VERTEX_SHADER, vertexShader_, this->VertexShaderFile_.data());
		CreateShader(GL_FRAGMENT_SHADER, fragmentShader_, this->FragmentShaderFile_.data());
		CreateProgram();
	}
}

void ShaderProgram::unload(){
	glDetachShader(program_, vertexShader_);
	glDetachShader(program_, fragmentShader_);

    glDeleteShader(vertexShader_);
	glDeleteShader(fragmentShader_);
	glDeleteProgram(program_);

	vertexShader_ = 0;
	fragmentShader_ = 0;
	program_ = 0;

	loaded = false;
}

void ShaderProgram::setParams(const std::string VertexShaderPath, const std::string FragmentShaderPath, const std::string pname) 
{
	this->VertexShaderFile_.setParams(VertexShaderPath);
	this->FragmentShaderFile_.setParams(FragmentShaderPath);
	this->resName_ = pname;
	this->subResources_.setResources({&this->VertexShaderFile_, &this->FragmentShaderFile_});
}

ShaderProgram::~ShaderProgram(){}

unsigned int ShaderProgram::getProgramID(){ return program_; }

int ShaderProgram::getUniformLocation(const std::string& name)
{
	return glGetUniformLocation(program_, name.c_str());
}

void ShaderProgram::bind()
{
	glUseProgram(program_);
}

void ShaderProgram::unbind()
{
	glUseProgram(0);
}

void ShaderProgram::CreateShader(unsigned int Type, unsigned int & id, const std::string& code)
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

void ShaderProgram::CreateProgram()
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

ShaderProgram::ShaderProgram():
OpenGLResource(),
fragmentShader_(0), 
vertexShader_(0), 
program_(0)
{
	
}


}