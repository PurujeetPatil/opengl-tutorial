#include "Test.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

namespace test
{
	TestMenu::TestMenu(Test*& current)
		: m_Current(current)
	{

	}
	
	void TestMenu::ImGuiRender()
	{
		for (auto& test : m_TestList)
		{
			if (ImGui::Button(test.first.c_str()))
			{
				m_Current = test.second();
			}
		}
	}
}