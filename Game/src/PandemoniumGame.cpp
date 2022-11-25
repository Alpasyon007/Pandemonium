#include <Pandemonium.h>

#include "OpenGLShader.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ExampleLayer : public Pandemonium::Layer {
public:
	ExampleLayer() : Layer("Example"), m_CameraController(1280.0f / 720.0f) {
		m_VertexArray.reset(Pandemonium::VertexArray::Create());

		float										vertices[3 * 7] = {-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f, 0.5f, -0.5f, 0.0f, 0.2f,
																	   0.3f,  0.8f,	 1.0f, 0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f,	1.0f};

		Pandemonium::Ref<Pandemonium::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Pandemonium::VertexBuffer::Create(vertices, sizeof(vertices)));

		Pandemonium::BufferLayout layout = {{Pandemonium::ShaderDataType::Float3, "a_Position"}, {Pandemonium::ShaderDataType::Float4, "a_Color"}};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int							   indices[3] = {0, 1, 2};
		Pandemonium::Ref<Pandemonium::IndexBuffer> indexBuffer;
		indexBuffer.reset(Pandemonium::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Pandemonium::VertexArray::Create());

		float										squareVertices[5 * 4] = {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.5f,	-0.5f, 0.0f, 1.0f, 0.0f,
																			 0.5f,	0.5f,  0.0f, 1.0f, 1.0f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f};

		Pandemonium::Ref<Pandemonium::VertexBuffer> squareVB;
		squareVB.reset(Pandemonium::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({{Pandemonium::ShaderDataType::Float3, "a_Position"}, {Pandemonium::ShaderDataType::Float2, "m_TexCoord"}});
		m_SquareVA->AddVertexBuffer(squareVB);

		unsigned int							   squareIndices[6] = {0, 1, 2, 2, 3, 0};
		Pandemonium::Ref<Pandemonium::IndexBuffer> squareIB;
		squareIB.reset(Pandemonium::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc			 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main() {
				v_Position = a_Position; 
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc			 = R"(
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

		m_Shader						 = Pandemonium::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorVertexSrc	 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main() {
				v_Position = a_Position; 
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";

		std::string flatColorFragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec3 u_Color;

			void main() {
				color = vec4(u_Color, 1.0f); 
			}
		)";

		m_FlatColorShader				 = Pandemonium::Shader::Create("FlatColor", flatColorVertexSrc, flatColorFragmentSrc);

		auto textureShader				 = m_ShaderLibrary.Load("C:\\dev\\Pandemonium\\Game\\assets\\shaders\\Texture.glsl");

		m_Texture						 = Pandemonium::Texture2D::Create("C:\\dev\\Pandemonium\\Game\\assets\\Checkerboard.png");
		m_IconTexture					 = Pandemonium::Texture2D::Create("C:\\dev\\Pandemonium\\Game\\assets\\Gear-icon.png");

		std::dynamic_pointer_cast<Pandemonium::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Pandemonium::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Pandemonium::Timestep ts) override {

		m_CameraController.OnUpdate(ts);

		Pandemonium::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
		Pandemonium::RenderCommand::Clear();

		Pandemonium::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Pandemonium::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Pandemonium::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		for(int y = 0; y < 20; y++) {
			for(int x = 0; x < 20; x++) {
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Pandemonium::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}
		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Pandemonium::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_IconTexture->Bind();
		Pandemonium::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Pandemonium::Renderer::Submit(m_Shader, m_VertexArray);

		Pandemonium::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Pandemonium::Event& e) override { m_CameraController.OnEvent(e); }
private:
	Pandemonium::ShaderLibrary				   m_ShaderLibrary;

	Pandemonium::Ref<Pandemonium::Shader>	   m_Shader;
	Pandemonium::Ref<Pandemonium::VertexArray> m_VertexArray;

	Pandemonium::Ref<Pandemonium::VertexArray> m_SquareVA;
	Pandemonium::Ref<Pandemonium::Shader>	   m_FlatColorShader;

	Pandemonium::Ref<Pandemonium::Texture2D>   m_Texture, m_IconTexture;

	Pandemonium::OrthographicCameraController  m_CameraController;

	glm::vec3								   m_SquareColor = {0.2f, 0.3f, 0.8f};
};

class PandemoniumGame : public Pandemonium::Application {
public:
	PandemoniumGame() { PushLayer(new ExampleLayer()); }

	~PandemoniumGame() {}
};

Pandemonium::Application* Pandemonium::CreateApplication() { return new PandemoniumGame(); }