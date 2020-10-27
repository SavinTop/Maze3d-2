#pragma once

#include <glad/glad.h>
#include <String>
#include <iostream>
#include <vector>
#include "baseTypes/resource.hpp"
#include "utilities/fileLoader.hpp"
#include "baseTypes/resources/external/TextFile.hpp"

class ShaderProgram : public Resource
{
public:
	ShaderProgram();
	ShaderProgram(const std::string VertexShaderPath, const std::string FragmentShaderPath, const std::string pname);
	~ShaderProgram();

	unsigned int getProgramID();
	unsigned int getUniformLocation(const std::string& name);

	void load() override;
	void unload() override;
	void setParams(const std::string VertexShaderPath, const std::string FragmentShaderPath, const std::string pname);

	void bind();
	void unbind();


private:
	Resources::External::TextFile VertexShaderFile_;
	Resources::External::TextFile FragmentShaderFile_;
	unsigned int vertexShader_;
	unsigned int fragmentShader_;
	unsigned int program_;

	void CreateShader(unsigned int Type, unsigned int& id, const std::string& code);
	void CreateProgram();
};