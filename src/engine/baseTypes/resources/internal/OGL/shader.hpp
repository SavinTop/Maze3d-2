#pragma once

#include <glad/glad.h>
#include <String>
#include <iostream>
#include <vector>
#include "utilities/fileLoader.hpp"
#include "baseTypes/resources/external/TextFile.hpp"
#include "baseTypes/resource/resourceManager.hpp"

#include "baseTypes/oglWrappers/shader.hpp"

namespace res::ogl{

class ShaderProgram : public OpenGLResource
{
public:
	ShaderProgram();
	ShaderProgram(const std::string VertexShaderPath, const std::string FragmentShaderPath, const std::string pname);

	unsigned int getProgramID();
	int getUniformLocation(const std::string& name);

	void load() override;
	void unload() override;
	void setParams(const std::string VertexShaderPath, const std::string FragmentShaderPath, const std::string pname);

	virtual void InitializeSubResources(std::string groupName);

	void bind();
	void unbind();

	oglw::Shader& getProgram();
private:
	std::shared_ptr<res::ex::TextFile> VertexShaderFile_;
	std::shared_ptr<res::ex::TextFile> FragmentShaderFile_;
	std::string vertexShaderPath;
	std::string fragmentShaderPath;
	oglw::Shader program;
};

}