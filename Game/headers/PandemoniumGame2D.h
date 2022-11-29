#ifndef PANDEMONIUM_GAME_2D
#define PANDEMONIUM_GAME_2D

#include <Pandemonium.h>

class PandemoniumGame2D : public Pandemonium::Layer {
public:
	PandemoniumGame2D();
	virtual ~PandemoniumGame2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(Pandemonium::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Pandemonium::Event& event) override;
private:
	Pandemonium::OrthographicCameraController  m_CameraController;

	Pandemonium::Ref<Pandemonium::VertexArray> m_SquareVA;
	Pandemonium::Ref<Pandemonium::Shader>	   m_FlatColorShader;

	glm::vec4								   m_SquareColor = {0.2f, 0.3f, 0.8f, 1.0f};

	Pandemonium::Ref<Pandemonium::Texture2D>   m_CheckerboardTexture;
};

#endif /* PANDEMONIUM_GAME_2D */