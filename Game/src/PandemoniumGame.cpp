#include <Pandemonium.h>

class ExampleLayer : public Pandemonium::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {
		// LOG_INFO("ExampleLayer::Update");
	}

	void OnEvent(Pandemonium::Event& e) override { LOG_INFO(e.ToString()); }
};

class PandemoniumGame : public Pandemonium::Application {
public:
	PandemoniumGame() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Pandemonium::ImGuiLayer());
	}

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