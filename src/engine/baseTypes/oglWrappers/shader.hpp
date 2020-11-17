#pragma once

#include <glad/glad.h>
#include <String>
#include <iostream>
#include <vector>

namespace oglw{

class Shader
{
public:
	Shader();
	Shader(const std::string VertexShaderText, const std::string FragmentShaderText);

	unsigned int getProgramID();
	int getUniformLocation(const std::string& name);

	void load();
	void unload();
	void setParams(const std::string VertexShaderText, const std::string FragmentShaderText);

	void bind();
	void unbind();

	bool isLoaded() {return loaded;};
private:
	bool loaded = false;
	std::string vertexShaderText;
	std::string fragmentShaderText;

	unsigned int vertexShader_;
	unsigned int fragmentShader_;
	unsigned int program_;

	void CreateShader(unsigned int Type, unsigned int& id, const std::string& code);
	void CreateProgram();
};

}