#include "ppch.h"
#include "OpenGLShader.h"

#include <glm/gtc/type_ptr.hpp>

namespace Pandemonium {

	static GLenum ShaderTypeFromString(const std::string& type) {
		if(type == "vertex") return GL_VERTEX_SHADER;
		if(type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;

		LOG_ERROR("Unknown shader of type: %s", type);
		return 0;
	}

	OpenGLShader::OpenGLShader(const std::string& filepath) {
		PANDEMONIUM_PROFILE_FUNCTION();

		std::string								source		  = ReadFile(filepath);
		std::unordered_map<GLenum, std::string> shaderSources = PreProcess(source);
		Compile(shaderSources);

		size_t lastSlash = filepath.find_last_of("/\\");
		lastSlash		 = lastSlash == std::string::npos ? 0 : lastSlash + 1;

		size_t lastDot	 = filepath.rfind(".");
		size_t count	 = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;

		m_Name			 = filepath.substr(lastSlash, count);
	}

	OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc) : m_Name(name) {
		PANDEMONIUM_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> sources;
		sources[GL_VERTEX_SHADER]	= vertexSrc;
		sources[GL_FRAGMENT_SHADER] = fragmentSrc;
		Compile(sources);
	}

	OpenGLShader::~OpenGLShader() {
		PANDEMONIUM_PROFILE_FUNCTION();

		glDeleteProgram(m_RendererID);
	}

	std::string OpenGLShader::ReadFile(const std::string& filepath) {
		PANDEMONIUM_PROFILE_FUNCTION();

		std::string	  result;
		std::ifstream in(filepath, std::ios::in | std::ios::binary);
		if(in) {
			in.seekg(0, std::ios::end);
			result.resize(in.tellg());
			in.seekg(0, std::ios::beg);
			in.read(&result[0], result.size());
			in.close();
			;
		} else {
			LOG_ERROR("Could not open file %s", filepath);
		}
		return result;
	}

	std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(const std::string& source) {
		PANDEMONIUM_PROFILE_FUNCTION();

		std::unordered_map<GLenum, std::string> shaderSources;

		const char*								typeToken		= "#type";
		size_t									typeTokenLength = strlen(typeToken);
		size_t									pos				= source.find(typeToken, 0);
		while(pos != std::string::npos) {
			size_t eol = source.find_first_of("\r\n", pos);
			ASSERT(eol != std::string::npos, "Syntax error");
			size_t		begin = pos + typeTokenLength + 1;
			std::string type  = source.substr(begin, eol - begin);
			ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

			size_t nextLinePos						  = source.find_first_not_of("\r\n", eol);
			pos										  = source.find(typeToken, nextLinePos);
			shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos, pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
		}

		return shaderSources;
	}

	void OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources) {
		PANDEMONIUM_PROFILE_FUNCTION();

		GLuint program = glCreateProgram();
		ASSERT(shaderSources.size() <= 2, "Too many shaders! Only support 2");
		std::array<GLenum, 2> glShaderIDs;
		int					  glShaderIDIndex = 0;

		for(const std::pair<const GLenum, std::string>& kv : shaderSources) {
			GLenum			   type		  = kv.first;
			const std::string& source	  = kv.second;

			GLuint			   shader	  = glCreateShader(type);

			const GLchar*	   sourceCStr = source.c_str();
			glShaderSource(shader, 1, &sourceCStr, 0);

			glCompileShader(shader);

			GLint isCompiled = 0;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);

			if(isCompiled == GL_FALSE) {
				GLint maxLength = 0;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

				std::vector<GLchar> infoLog(maxLength);
				glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

				glDeleteShader(shader);

				LOG_ERROR("Shader compilation failure!");
				LOG_ERROR("%s", infoLog.data());
				DEBUG_BREAK();
				break;
			}

			glAttachShader(program, shader);
			glShaderIDs[glShaderIDIndex++] = (shader);
		}

		m_RendererID = program;

		glLinkProgram(m_RendererID);

		GLint isLinked = 0;
		glGetProgramiv(m_RendererID, GL_LINK_STATUS, (int*)&isLinked);
		if(isLinked == GL_FALSE) {
			GLint maxLength = 0;
			glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

			glDeleteProgram(m_RendererID);

			for(GLenum id : glShaderIDs) {
				glDeleteShader(id);
			}

			LOG_ERROR("Shader link failure!");
			LOG_ERROR("%s", infoLog.data());
			DEBUG_BREAK();

			return;
		}

		for(GLenum id : glShaderIDs) {
			glDetachShader(program, id);
		}

		m_RendererID = program;
	}

	void OpenGLShader::Bind() const {
		PANDEMONIUM_PROFILE_FUNCTION();

		glUseProgram(m_RendererID);
	}

	void OpenGLShader::Unbind() const {
		PANDEMONIUM_PROFILE_FUNCTION();

		glUseProgram(0);
	}

	void OpenGLShader::SetInt(const std::string& name, int value) {
		PANDEMONIUM_PROFILE_FUNCTION();

		UploadUniformInt(name, value);
	}

	void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value) {
		PANDEMONIUM_PROFILE_FUNCTION();

		UploadUniformFloat3(name, value);
	}

	void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value) {
		PANDEMONIUM_PROFILE_FUNCTION();

		UploadUniformFloat4(name, value);
	}

	void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value) {
		PANDEMONIUM_PROFILE_FUNCTION();

		UploadUniformMat4(name, value);
	}

	void OpenGLShader::UploadUniformInt(const std::string& name, int value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1i(location, value);
	}

	void OpenGLShader::UploadUniformFloat(const std::string& name, float value) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform1f(location, value);
	}

	void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& values) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform2f(location, values.x, values.y);
	}

	void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& values) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform3f(location, values.x, values.y, values.z);
	}

	void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& values) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniform4f(location, values.x, values.y, values.z, values.w);
	}

	void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix) {
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}

} // namespace Pandemonium