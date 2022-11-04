#include <Pandemonium.h>

class PandemoniumGame : public Pandemonium::Application {
public:
	PandemoniumGame() {}

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