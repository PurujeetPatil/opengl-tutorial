#include "fileutil.h"

ShaderSource getShaderSource(const std::string& filepath)
{
	std::fstream file(filepath);
	std::stringstream strings[2];
	std::string line;
	enum class Shadertype
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};
	Shadertype mode = Shadertype::NONE;
	while (std::getline(file, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				mode = Shadertype::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				mode = Shadertype::FRAGMENT;
			}
		}
		else
		{
			if(mode != Shadertype::NONE)
				strings[(int)mode] << line << "\n";
		}
	}
	return {strings[0].str(), strings[1].str()};
}
