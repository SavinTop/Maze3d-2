#pragma once

#include <glad/glad.h>
#include <String>
#include <iostream>
#include <vector>
#include "utilities/fileLoader.hpp"
#include "baseTypes/resources/external/TextFile.hpp"
#include "baseTypes/resource/resourceManager.hpp"

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
private:
	std::shared_ptr<res::ex::TextFile> VertexShaderFile_;
	std::shared_ptr<res::ex::TextFile> FragmentShaderFile_;
	std::string vertexShaderPath;
	std::string fragmentShaderPath;

	unsigned int vertexShader_;
	unsigned int fragmentShader_;
	unsigned int program_;

	void CreateShader(unsigned int Type, unsigned int& id, const std::string& code);
	void CreateProgram();
};

}