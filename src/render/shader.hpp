#pragma once

#include <glad/glad.h>
#include <String>
#include <iostream>
#include <vector>
#include "baseTypes/resource.hpp"
#include "utilities/fileLoader.hpp"
#include "baseTypes/disk_file_text_res.hpp"

class ShaderProgram : public Resource
{
public:
	ShaderProgram(const std::string& VertexShaderPath, std::string& FragmentShaderPath);
	~ShaderProgram();

	unsigned int getProgramID();
	unsigned int getUniformLocation(const std::string& name);

	void load() override;
	void free() override;

	void bind();
	void unbind();

private:
	disk_file_text_res VertexShaderFile;
	disk_file_text_res FragmentShaderFile;
	unsigned int m_vertexShader;
	unsigned int m_fragmentShader;
	unsigned int m_program;

	void CreateShader(unsigned int Type, unsigned int& id, const char* source);
	void CreateProgram();
};