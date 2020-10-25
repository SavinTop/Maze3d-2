#include "shader.hpp"

ShaderProgram::ShaderProgram(const std::string VertexShaderPath, const std::string FragmentShaderPath, const std::string pname)
	:Resource(pname), 
	m_fragmentShader(0), 
	m_vertexShader(0), 
	m_program(0),
	VertexShaderFile(VertexShaderPath), 
	FragmentShaderFile(FragmentShaderPath)
{
	this->subResources_.setResources({&this->VertexShaderFile, &this->FragmentShaderFile});
}

void ShaderProgram::load(){
	subResources_.load();
	if(subResources_.isLoaded()){
		CreateShader(GL_VERTEX_SHADER, m_vertexShader, this->VertexShaderFile.data());
		CreateShader(GL_FRAGMENT_SHADER, m_fragmentShader, this->FragmentShaderFile.data());
		CreateProgram();
	}
	loaded = subResources_.isLoaded();
}

void ShaderProgram::unload(){
	subResources_.unload();
	glDetachShader(m_program, m_vertexShader);
	glDetachShader(m_program, m_fragmentShader);

    glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
	glDeleteProgram(m_program);

	loaded = false;
}

ShaderProgram::~ShaderProgram()
{
	unload();
}

unsigned int ShaderProgram::getProgramID()
{
	return m_program;
}

unsigned int ShaderProgram::getUniformLocation(const std::string& name)
{
	return glGetUniformLocation(m_program, name.c_str());
}

void ShaderProgram::bind()
{
	glUseProgram(m_program);
}

void ShaderProgram::unbind()
{
	glUseProgram(0);
}

void ShaderProgram::CreateShader(unsigned int Type, unsigned int & id, const char* source)
{
	id = glCreateShader(Type);
	glShaderSource(id, 1, &source, 0);
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
	m_program = glCreateProgram();
	glAttachShader(m_program, m_vertexShader);
	glAttachShader(m_program, m_fragmentShader);
	glLinkProgram(m_program);

	int isLinked = 0;
	glGetProgramiv(m_program, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		int maxLength = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(m_program, maxLength, &maxLength, &infoLog[0]);

		std::cout<<infoLog.data();

		glDeleteProgram(m_program);
		glDeleteShader(m_vertexShader);
		glDeleteShader(m_fragmentShader);

		return;
	}

}
