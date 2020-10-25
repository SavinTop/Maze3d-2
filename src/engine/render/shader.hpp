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
	ShaderProgram(const std::string VertexShaderPath, const std::string FragmentShaderPath, const std::string pname);
	~ShaderProgram();

	unsigned int getProgramID();
	unsigned int getUniformLocation(const std::string& name);

	void load() override;
	void unload() override;

	void bind();
	void unbind();

private:
	TextFile_res VertexShaderFile;
	TextFile_res FragmentShaderFile;
	unsigned int m_vertexShader;
	unsigned int m_fragmentShader;
	unsigned int m_program;

	void CreateShader(unsigned int Type, unsigned int& id, const char* source);
	void CreateProgram();
};