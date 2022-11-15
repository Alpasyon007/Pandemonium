#ifndef OPEN_GL_SHADER_H
#define OPEN_GL_SHADER_H

#include "ppch.h"
#include "Core.h"
#include "Shader.h"
#include <glm/glm.hpp>

namespace Pandemonium {

	class PANDEMONIUM_API OpenGLShader : public Shader {
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~OpenGLShader();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		void		 UploadUniformInt(const std::string& name, const int value);

		void		 UploadUniformFloat(const std::string& name, const float value);
		void		 UploadUniformFloat2(const std::string& name, const glm::vec2& values);
		void		 UploadUniformFloat3(const std::string& name, const glm::vec3& values);
		void		 UploadUniformFloat4(const std::string& name, const glm::vec4& values);

		void		 UploadUniformMat3(const std::string& name, const glm::mat3& matrix);
		void		 UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	private:
		uint32_t m_RendererID;
	};

} // namespace Pandemonium

#endif /* OPEN_GL_SHADER_H */