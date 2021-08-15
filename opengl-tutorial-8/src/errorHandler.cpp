#include "errorHandler.h"

void GLClearCall()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* functionName, const char* file, int line)
{
	if (GLenum error = glGetError())
	{
		std::cout << "[OPENGL ERROR] (" << error << ") " << functionName << " " << file << " : " << line << std::endl;
		return false;
	} 
	return true;
}
