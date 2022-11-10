#ifndef OPEN_GL_RENDERER_API_H
#define OPEN_GL_RENDERER_API_H

#include "RendererAPI.h"

namespace Pandemonium {

	class OpenGLRendererAPI : public RendererAPI {
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};

} // namespace Pandemonium

#endif /* OPEN_GL_RENDERER_API_H */