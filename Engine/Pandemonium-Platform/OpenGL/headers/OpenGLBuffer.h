#ifndef OPEN_GL_BUFFER_H
#define OPEN_GL_BUFFER_H

#include "Buffer.h"

namespace Pandemonium {
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);

		virtual ~OpenGLVertexBuffer();

		virtual void		 Bind() const;
		virtual void		 Unbind() const;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	private:
		uint32_t m_RendererID;
	};

	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);

		virtual ~OpenGLIndexBuffer();

		virtual void		Bind() const;
		virtual void		Unbind() const;

		virtual uint32_t	GetCount() const { return m_Count; }

		static IndexBuffer* Create(float* vertices, uint32_t size);
	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
} // namespace Pandemonium

#endif /* OPEN_GL_BUFFER_H */