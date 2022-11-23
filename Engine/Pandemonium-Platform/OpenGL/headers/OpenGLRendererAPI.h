#ifndef OPEN_GL_RENDERER_API_H
#define OPEN_GL_RENDERER_API_H

#include "RendererAPI.h"

namespace Pandemonium {

	class OpenGLRendererAPI : public RendererAPI {
	public:
		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};

} // namespace Pandemonium

#endif /* OPEN_GL_RENDERER_API_H */