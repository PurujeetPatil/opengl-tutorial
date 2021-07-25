#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearCall();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__));

/*
	#x turns the argument to string
	__FILE__ is an intrinsic macro that contains the file name
	__LINE__ is an intrinsic macro that contains the executing line number
*/

void GLClearCall();

bool GLLogCall(const char* functionName, const char* file, int line);
