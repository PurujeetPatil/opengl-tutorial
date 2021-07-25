#pragma once

#include <string>
#include <fstream>
#include <sstream>

struct ShaderSource {
	std::string vertexSrc;
	std::string fragmentSrc;
};

ShaderSource getShaderSource(const std::string& filepath);
