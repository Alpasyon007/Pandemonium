#include <Pandemonium.h>

#include "imgui.h"

class ExampleLayer : public Pandemonium::Layer {
public:
	ExampleLayer() : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) {
		m_VertexArray.reset(Pandemonium::VertexArray::Create());

		float									   vertices[3 * 7] = {-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f, 0.5f, -0.5f, 0.0f, 0.2f,
																	  0.3f,	 0.8f,	1.0f, 0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f,  1.0f};

		std::shared_ptr<Pandemonium::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Pandemonium::VertexBuffer::Create(vertices, sizeof(vertices)));

		Pandemonium::BufferLayout layout = {{Pandemonium::ShaderDataType::Float3, "a_Position"}, {Pandemonium::ShaderDataType::Float4, "a_Color"}};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int							  indices[3] = {0, 1, 2};
		std::shared_ptr<Pandemonium::IndexBuffer> indexBuffer;
		indexBuffer.reset(Pandemonium::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Pandemonium::VertexArray::Create());

		float									   squareVertices[3 * 4] = {-0.75f, -0.75f, 0.0f, 0.75f, -0.75f, 0.0f, 0.75f, 0.75f, 0.0f, -0.75f, 0.75f, 0.0f};

		std::shared_ptr<Pandemonium::VertexBuffer> squareVB;
		squareVB.reset(Pandemonium::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({{Pandemonium::ShaderDataType::Float3, "a_Position"}});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int							  squareIndices[6] = {0, 1, 2, 2, 3, 0};
		std::shared_ptr<Pandemonium::IndexBuffer> squareIB;
		squareIB.reset(Pandemonium::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc	= R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position; 
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			uniform mat4 u_ViewProjection;

			in vec3 v_Position;
			in vec4 v_Color;

			void main() {
				color = u_ViewProjection * vec4(v_Position * 0.5f + 0.5f, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Pandemonium::Shader(vertexSrc, fragmentSrc));

		std::string blueVertexSrc	= R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main() {
				v_Position = a_Position; 
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string blueFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main() {
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		m_BlueShader.reset(new Pandemonium::Shader(blueVertexSrc, blueFragmentSrc));
	}

	void OnUpdate() override {
		Pandemonium::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
		Pandemonium::RenderCommand::Clear();

		m_Camera.SetPosition({0.5f, 0.5f, 0.0f});
		m_Camera.SetRotation(45.0f);

		Pandemonium::Renderer::BeginScene(m_Camera);

		Pandemonium::Renderer::Submit(m_BlueShader, m_SquareVA);
		Pandemonium::Renderer::Submit(m_Shader, m_VertexArray);

		Pandemonium::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {}

	void		 OnEvent(Pandemonium::Event& e) override {}
private:
	std::shared_ptr<Pandemonium::Shader>	  m_Shader;
	std::shared_ptr<Pandemonium::VertexArray> m_VertexArray;

	std::shared_ptr<Pandemonium::VertexArray> m_SquareVA;
	std::shared_ptr<Pandemonium::Shader>	  m_BlueShader;

	Pandemonium::OrthographicCamera			  m_Camera;
};

class PandemoniumGame : public Pandemonium::Application {
public:
	PandemoniumGame() { PushLayer(new ExampleLayer()); }

	~PandemoniumGame() {}
};

Pandemonium::Application* Pandemonium::CreateApplication() {
	// int a = 5;
	// char* b = "BYE";

	// ASSERT(a < 1);
	// ASSERT(a < 1, "HELLO");
	// ASSERT(a < 1, "HELLO %d", a);

	// // DEBUG_BREAK();

	// LOG_DEBUG("HELLO %d %s", a, b);
	// LOG_INFO("HELLO %d %s", a, b);
	// LOG_WARN("HELLO %d %s", a, b);
	// LOG_ERROR("HELLO %d %s", a, b);

	return new PandemoniumGame();
}