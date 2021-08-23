#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader
{
private:
	unsigned int m_renderID;
	std::string m_filepath;
	std::unordered_map<std::string, int> m_uniformLocationCache;
public:
	Shader(std::string filepath);
	~Shader();

	void bind() const;
	void unbind() const;
	void setUniform1i(const std::string& location, int value);
	void setUniform4f(const std::string &location, float f1, float f2, float f3, float f4);
	void setUniformMat4f(const std::string& location, const glm::mat4& matrix);
private:
	unsigned int getShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int compileShader(unsigned int type, const std::string& src);
	int getUniformLocation(const std::string& location);
};