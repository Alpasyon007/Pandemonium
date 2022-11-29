#include "PandemoniumGame2D.h"

#include "OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui.h"

PandemoniumGame2D::PandemoniumGame2D() : Layer("2D"), m_CameraController(1280.0f / 720.0f) {}

void PandemoniumGame2D::OnAttach() { m_CheckerboardTexture = Pandemonium::Texture2D::Create("C:\\dev\\Pandemonium\\Game\\assets\\Checkerboard.png"); }

void PandemoniumGame2D::OnDetach() {}

void PandemoniumGame2D::OnUpdate(Pandemonium::Timestep ts) {
	m_CameraController.OnUpdate(ts);

	Pandemonium::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
	Pandemonium::RenderCommand::Clear();

	Pandemonium::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Pandemonium::Renderer2D::DrawQuad({-1.0f, 0.0f}, {0.8f, 0.8f}, {0.8f, 0.2f, 0.3f, 1.0f});
	Pandemonium::Renderer2D::DrawQuad({0.5f, -0.5f}, {0.5f, 0.75f}, {0.2f, 0.3f, 0.8f, 1.0f});
	Pandemonium::Renderer2D::DrawQuad({0.0f, 0.0f, -0.1f}, {10.0f, 10.0f}, m_CheckerboardTexture);
	Pandemonium::Renderer2D::EndScene();
}

void PandemoniumGame2D::OnImGuiRender() {
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void PandemoniumGame2D::OnEvent(Pandemonium::Event& e) { m_CameraController.OnEvent(e); }