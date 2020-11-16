#include "shader.hpp"

namespace res::ogl{

ShaderProgram::ShaderProgram(const std::string VertexShaderPath, const std::string FragmentShaderPath, const std::string pname)
	:OpenGLResource()
{
	setParams(VertexShaderPath, FragmentShaderPath, pname);
}

void ShaderProgram::load(){
	if(loaded) return;
	program.setParams(VertexShaderFile_->data(), FragmentShaderFile_->data());
	program.load();
	loaded = true;
}

void ShaderProgram::unload(){
	program.unload();
	loaded = false;
}

void ShaderProgram::setParams(const std::string VertexShaderPath, const std::string FragmentShaderPath, const std::string pname) 
{
	this->vertexShaderPath = VertexShaderPath;
	this->fragmentShaderPath = FragmentShaderPath;
	this->resName_ = pname;
}

void ShaderProgram::InitializeSubResources(std::string groupName) 
{
	if(!rm) return;
	this->FragmentShaderFile_ = rm->createResource<>(res::ex::TextFile(fragmentShaderPath), groupName);
	this->VertexShaderFile_ = rm->createResource<>(res::ex::TextFile(vertexShaderPath), groupName);
	this->subResources_.setResources({VertexShaderFile_.get(), FragmentShaderFile_.get()});
}

unsigned int ShaderProgram::getProgramID(){ return program.getProgramID(); }

int ShaderProgram::getUniformLocation(const std::string& name)
{
	return program.getUniformLocation(name);
}

void ShaderProgram::bind()
{
	program.bind();
}

void ShaderProgram::unbind()
{
	program.unbind();
}

oglw::Shader& ShaderProgram::getProgram() 
{
	return program;
}

ShaderProgram::ShaderProgram():
OpenGLResource()
{
	
}


}