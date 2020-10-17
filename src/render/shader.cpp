#include "shader.hpp"

ShaderProgram::ShaderProgram(const std::string& VertexShaderPath, std::string& FragmentShaderPath)
	:Resource(VertexShaderPath), m_fragmentShader(0), m_vertexShader(0), m_program(0),
	VertexShaderFile(VertexShaderPath, "vertex_shader_file"), FragmentShaderFile(FragmentShaderPath, "fragment_shader_file")
{
	this->subResources.setResources({&this->VertexShaderFile, &this->FragmentShaderFile});
}

void ShaderProgram::load(){
	subResources.load();
	if(subResources.isLoaded()){
		CreateShader(GL_VERTEX_SHADER, m_vertexShader, this->VertexShaderFile.data());
		CreateShader(GL_FRAGMENT_SHADER, m_fragmentShader, this->FragmentShaderFile.data());
		CreateProgram();
	}
	loaded = subResources.isLoaded();
}

void ShaderProgram::free(){
	subResources.free();

	glDetachShader(m_program, m_vertexShader);
	glDetachShader(m_program, m_fragmentShader);

    glDeleteShader(m_vertexShader);
	glDeleteShader(m_fragmentShader);
	glDeleteProgram(m_program);

	loaded = false;
}

ShaderProgram::~ShaderProgram()
{
	free();
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
