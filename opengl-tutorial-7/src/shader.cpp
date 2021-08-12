#include "shader.h"
#include "errorHandler.h"
#include "fileutil.h"

Shader::Shader(std::string filepath)
	: m_filepath(filepath), m_renderID(0)
{
	ShaderSource source = getShaderSource(filepath);
	m_renderID = getShaderProgram(source.vertexSrc, source.fragmentSrc);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_renderID));
}

void Shader::bind() const 
{
	GLCall(glUseProgram(m_renderID));
}

void Shader::unbind() const 
{
	GLCall(glUseProgram(0));
}

void Shader::setUniform4f(const std::string& location, float f1, float f2, float f3, float f4)
{
	GLCall(glUniform4f(getUniformLocation(location), f1, f2, f3, f4));
}

unsigned int Shader::getShaderProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
	// Create a program to run on GPU
	unsigned int program = glCreateProgram();

	//------------------------Vertex Shader-------------------------

	// Create a shader ID
	unsigned int v_id = compileShader(GL_VERTEX_SHADER, vertexShader);

	//-----------------------Fragment Shader------------------------

	// Same shit below, expect for target that is GL_FRAGMENT_SHADER
	unsigned int f_id = compileShader(GL_FRAGMENT_SHADER, fragmentShader);


	// attach the shader to the program by id
	glAttachShader(program, v_id);
	glAttachShader(program, f_id);

	// link the two shader .obj(s) in the program
	glLinkProgram(program);

	// validate if successfully linked
	glValidateProgram(program);

	// delete the intermediates like .obj(s)
	glDeleteShader(v_id);
	glDeleteShader(f_id);

	return program;
}

unsigned int Shader::compileShader(unsigned int type, const std::string& src)
{
	// Create a shader ID
	unsigned int id = glCreateShader(type);

	// openGL likes NULL terminated string and its pointer for some reason
	const char* s_src = src.c_str();

	// Pass the id for shader, number of shaders, reference to pointer to src of shader (wtf?) and length of shader(we are passing null, as null terminated) 
	glShaderSource(id, 1, &s_src, nullptr);

	// Compile the shader by the id
	glCompileShader(id);

	//-------------------Error Handling---------------------
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		// i specifies that we are giving an integer and v specifies it wants a vector
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

		// Create a message buffer of that length
		char* message = (char*)_malloca(length * sizeof(char));

		// Pass the message buffer
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "Failed to compile shader! : " << (type == GL_VERTEX_SHADER ? "|Vertex|" : "|Fragment|");
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

int Shader::getUniformLocation(const std::string& location)
{
	if (m_uniformLocationCache.find(location) != m_uniformLocationCache.end())
	{
		return m_uniformLocationCache[location];
	}
	GLCall(int uniformlocation = glGetUniformLocation(m_renderID, location.c_str()));
	if (uniformlocation == -1)
	{
		std::cout << "WARNING: Uniform { " << location << " } doesn't exist\n";
	}
	m_uniformLocationCache[location] = uniformlocation;
	return uniformlocation;
}
