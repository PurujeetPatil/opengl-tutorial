#include "../errorHandler.h"

#include "TestClearColor.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace test
{
	TestClearColor::TestClearColor()
		: m_ClearColor{ 1.0f, 1.0f, 1.0f, 1.0f }
	{

	}

	TestClearColor::~TestClearColor()
	{

	}

	void TestClearColor::onUpdate(float deltaTime)
	{

	}

	void TestClearColor::onRender()
	{
		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void TestClearColor::ImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", m_ClearColor);
	}
}
