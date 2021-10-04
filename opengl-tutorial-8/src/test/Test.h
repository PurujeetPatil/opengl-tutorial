#pragma once

#include <functional>
#include <vector>
#include <string>


namespace test
{
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void onUpdate(float deltaTime) {}
		virtual void onRender() {}
		virtual void ImGuiRender() {}
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& current);


		void ImGuiRender() override;

		template<typename T>
		void RegisterTest(const std::string &name)
		{
			m_TestList.push_back(std::make_pair( name, []() { return new T(); } ));
		}

	private:
		Test*& m_Current;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_TestList;
	};
}