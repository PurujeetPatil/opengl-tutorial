#include "../errorHandler.h"

#include "TestTexture2D.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../vertexArray.h"
#include "../vertexbuffer.h"
#include "../indexbuffer.h"
#include "../shader.h"
#include "../textures.h"
#include "../vertexBufferLayout.h"
#include "../renderer.h"

namespace test
{
	TestTexture2D::TestTexture2D()
		: m_TranslationA(40, 40, 0), m_TranslationB(40, 40, 0)
	{
		float positions[] = {
		 0.0f,  0.0f, 0.0f, 0.0f, // 0
		 200.0f,  0.0f, 1.0f, 0.0f, // 1
		 200.0f,  200.0f, 1.0f, 1.0f, // 2
		 0.0f,  200.0f, 0.0f, 1.0f  // 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));

		m_VAO = std::make_unique<VertexArray>();
		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.push<float>(2);
		layout.push<float>(2);

		m_VAO->addBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);
		m_IndexBuffer->Bind();

		m_Shader = std::make_unique<Shader>("res/shader/basic.shader");
		m_Shader->bind();

		m_Texture = std::make_unique<Texture>("res\\textures\\meme.png");
		
		m_Shader->setUniform1i("u_texture", 0);

	}

	TestTexture2D::~TestTexture2D()
	{

	}

	void TestTexture2D::onUpdate(float deltaTime)
	{

	}

	void TestTexture2D::onRender()
	{
		GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		Renderer renderer;

		m_Texture->bind();
		glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = projection * view * model;
			m_Shader->bind();
			m_Shader->setUniformMat4f("u_MVP", mvp);
			renderer.draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			glm::mat4 mvp = projection * view * model;
			m_Shader->bind();
			m_Shader->setUniformMat4f("u_MVP", mvp);
			renderer.draw(*m_VAO, *m_IndexBuffer, *m_Shader);
		}
	}

	void TestTexture2D::ImGuiRender()
	{
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 700.0f);
		ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 700.0f);
		ImGui::Text("Hello world!");
	}
}
