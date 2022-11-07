#include <Pandemonium.h>

class ExampleLayer : public Pandemonium::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {

		if(Pandemonium::Input::IsKeyPressed(PANDEMONIUM_KEY_TAB)) { LOG_INFO("Tab key is pressed"); }
	}

	void OnEvent(Pandemonium::Event& e) override {
		if(e.GetEventType() == Pandemonium::EventType::KeyPressed) {
			Pandemonium::KeyPressedEvent& event = (Pandemonium::KeyPressedEvent&)e;
			if(event.GetKeyCode() == PANDEMONIUM_KEY_TAB) { LOG_INFO("Tab key is pressed"); }
			LOG_INFO("%c", (char)event.GetKeyCode());
		}
	}
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