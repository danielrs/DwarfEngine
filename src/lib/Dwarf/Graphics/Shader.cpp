#include <Dwarf/Graphics/Shader.h>

#include <Dwarf/Util/Logger.h>
#include "../../../../3rdParty/Universal/glew/include/GL/glew.h"

using namespace Dwarf::Util;

namespace Dwarf
{
	namespace Graphics
	{

		Shader::Shader() {
			this->type = VERTEX;
			this->source = "";
		}

		Shader::Shader(const Type &type) {
			this->type = type;
		}

		Shader::Shader(const Type &type, const std::string &source)
		{
			this->type = type;
			this->source = source;
		}

		Shader::~Shader()
		{
			free();
		}

		void Shader::free()
		{
			if (glIsShader(shader_id))
				glDeleteShader(shader_id);
		}

		GLuint Shader::getID() const
		{
			return shader_id;
		}

		Shader::Type Shader::getType() const
		{
			return type;
		}

		void Shader::setType(const Type &type)
		{
			this->type = type;
			this->free();
		}

		std::string Shader::getSource() const
		{
			return source;
		}

		void Shader::setSource(const std::string &source)
		{
			this->source = source;
			this->free();
		}

		bool Shader::isCompiled() const
		{
			if (glIsShader(shader_id))
			{
				GLint compileStatus;
				glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compileStatus);
				return compileStatus == GL_TRUE;
			}

			return false;
		}

		void Shader::compile()
		{
			free();

			const char *sourcePtr = source.c_str();

			static GLenum shaderTypes[] =
			{
				GL_VERTEX_SHADER,
				GL_VERTEX_SHADER,
				GL_TESS_CONTROL_SHADER,
				GL_TESS_EVALUATION_SHADER,
				GL_GEOMETRY_SHADER,
				GL_FRAGMENT_SHADER,
				GL_COMPUTE_SHADER
			};

			shader_id = glCreateShader(shaderTypes[type]);
			glShaderSource(shader_id, 1, &sourcePtr, NULL);

			if (shader_id)
			{
				glCompileShader(shader_id);

				if (!isCompiled())
				{
					Logger::log(Logger::V_WARNING, "[%s:%d] Error compiling shader %d\n", __FILE__, __LINE__, shader_id);
					Logger::log(Logger::V_WARNING, "%s\n", getInfoLog().c_str());
					Logger::log(Logger::V_WARNING, "[Shader Source]\n");
					Logger::log(Logger::V_WARNING, source.c_str());
				}
			}

		}

		std::string Shader::getInfoLog() const
		{
			std::string result;
			GLint infoLogLength;

			glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &infoLogLength);
			if (infoLogLength > 0)
			{
				GLchar* infoLog = new GLchar[infoLogLength + 1];
				glGetShaderInfoLog(shader_id, infoLogLength, &infoLogLength, infoLog);

				result = (char*) infoLog;
				delete[] infoLog;
			}

			return result;
		}

	} // end of namespace Graphics
} // end of namespace Dwarf
