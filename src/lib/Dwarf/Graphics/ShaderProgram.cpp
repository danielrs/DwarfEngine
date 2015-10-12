#include <Dwarf/Graphics/ShaderProgram.h>
#include <Dwarf/Graphics/Shader.h>
#include <Dwarf/Util/Logger.h>

using namespace Dwarf::Math;
using namespace Dwarf::Util;
using namespace std;

namespace Dwarf
{
	namespace Graphics
	{

		ShaderProgram::ShaderProgram() {}

		// ----------------------------------------------------------------

		ShaderProgram::~ShaderProgram()
		{
			dispose();
			shaders.clear();
		}

		// ----------------------------------------------------------------

		void ShaderProgram::dispose()
		{
			if (glIsProgram(program_id))
				glDeleteProgram(program_id);
		}

		// ----------------------------------------------------------------

		GLuint ShaderProgram::getID() const
		{
			return program_id;
		}

		// ----------------------------------------------------------------

		void ShaderProgram::attachShader(Shader* shader)
		{
			shaders.push_back(shader);
		}

		// ----------------------------------------------------------------

		void ShaderProgram::clearShaders()
		{
			shaders.clear();
		}

		bool ShaderProgram::isLinked()
		{
			if (glIsProgram(program_id))
			{
				GLint link_status;
				glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);
				return link_status == GL_TRUE;
			}

			return false;
		}

		void ShaderProgram::link()
		{
			dispose();

			std::list<Shader*>::iterator it;

			// Iterates over each Shader and compiles them.
			// Only creates program if all shaders compiled correctly.
			for (it = shaders.begin(); it != shaders.end(); ++it)
			{
				// Tries to compile once
				if (!(*it)->isCompiled()) (*it)->compile();
				if (!(*it)->isCompiled()) {
					Logger::log(Logger::V_WARNING, "[%s:%d] Error compiling shader %d\n", __FILE__, __LINE__, (*it)->getID());
					return;
				}
			}

			program_id = glCreateProgram();

			// All shaders compiled correctly
			if (program_id)
			{
				for (it = shaders.begin(); it != shaders.end(); ++it) {
					glAttachShader(program_id, (*it)->getID());
				}

				glLinkProgram(program_id);

				for (it = shaders.begin(); it != shaders.end(); ++it) {
					glDetachShader(program_id, (*it)->getID());
				}

				if (!isLinked())
				{
					Logger::log(Logger::V_WARNING, "[%s:%d] Error linking program %d\n", __FILE__, __LINE__, program_id);
					Logger::log(Logger::V_WARNING, "%s\n", getInfoLog().c_str());
				}
			}
		} // link

		std::string ShaderProgram::getInfoLog() const
		{
			std::string result;

			GLint infoLogLength;
			glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &infoLogLength);

			if (infoLogLength > 0)
			{
				GLchar* infoLog = new GLchar[infoLogLength + 1];
				glGetProgramInfoLog(program_id, infoLogLength, &infoLogLength, infoLog);
				result = (char*) infoLog;
				delete[] infoLog;
			}

			return result;
		}

		// Attributes and Uniforms
		int ShaderProgram::getAttribLocation(const string &name) {
			auto it = attributes.find(name);
			if (it == attributes.end() || it->second == -1)
				attributes.insert(pair<string, int>(name, glGetAttribLocation(program_id, name.c_str())));
			return attributes[name];
		}

		int ShaderProgram::getUniformLocation(const string &name) {
			auto it = uniforms.find(name);
			if (it == uniforms.end() || it->second == -1)
				uniforms.insert(pair<string, int>(name, glGetUniformLocation(program_id, name.c_str())));
			return uniforms[name];
		}

		void ShaderProgram::setUniformf(const int &location, const float &value1) {
			glUseProgram(program_id);
			glUniform1f(location, value1);
		}

		void ShaderProgram::setUniformf(const int &location, const float &value1, const float &value2) {
			glUseProgram(program_id);
			glUniform2f(location, value1, value2);
		}

		void ShaderProgram::setUniformf(const int &location, const float &value1, const float &value2, const float &value3) {
			glUseProgram(program_id);
			glUniform3f(location, value1, value2, value3);
		}

		void ShaderProgram::setUniformf(const int &location, const float &value1, const float &value2, const float &value3, const float &value4) {
			glUseProgram(program_id);
			glUniform4f(location, value1, value2, value3, value4);
		}

		void ShaderProgram::setUniformf(const int &location, const Math::Vector2 &values) {
			glUseProgram(program_id);
			glUniform2fv(location, 1, &values[0]);
		}

		void ShaderProgram::setUniformf(const int &location, const Math::Vector3 &values) {
			glUseProgram(program_id);
			glUniform3fv(location, 1, &values[0]);
		}

		void ShaderProgram::setUniformf(const int &location, const Math::Vector4 &values) {
			glUseProgram(program_id);
			glUniform4fv(location, 1, &values[0]);
		}

		void ShaderProgram::setUniformi(const int &location, const int &value1) {
			glUseProgram(program_id);
			glUniform1i(location, value1);
		}

		void ShaderProgram::setUniformi(const int &location, const int &value1, const int &value2) {
			glUseProgram(program_id);
			glUniform2i(location, value1, value2);
		}

		void ShaderProgram::setUniformi(const int &location, const int &value1, const int &value2, const int &value3) {
			glUseProgram(program_id);
			glUniform3i(location, value1, value2, value3);
		}

		void ShaderProgram::setUniformi(const int &location, const int &value1, const int &value2, const int &value3, const int &value4) {
			glUseProgram(program_id);
			glUniform4i(location, value1, value2, value3, value4);
		}

		void ShaderProgram::setUniform1fv(const int &location, float const * const values) {
			glUseProgram(program_id);
			glUniform1fv(location, 1, values);
		}

		void ShaderProgram::setUniform2fv(const int &location, float const * const values) {
			glUseProgram(program_id);
			glUniform2fv(location, 1, values);
		}

		void ShaderProgram::setUniform3fv(const int &location, float const * const values) {
			glUseProgram(program_id);
			glUniform3fv(location, 1, values);
		}

		void ShaderProgram::setUniform4fv(const int &location, float const * const values) {
			glUseProgram(program_id);
			glUniform4fv(location, 1, values);
		}

		void ShaderProgram::setUniform1iv(const int &location, int const * const values) {
			glUseProgram(program_id);
			glUniform1iv(location, 1, values);
		}

		void ShaderProgram::setUniform2iv(const int &location, int const * const values) {
			glUseProgram(program_id);
			glUniform2iv(location, 1, values);
		}

		void ShaderProgram::setUniform3iv(const int &location, int const * const values) {
			glUseProgram(program_id);
			glUniform3iv(location, 1, values);
		}

		void ShaderProgram::setUniform4iv(const int &location, int const * const values) {
			glUseProgram(program_id);
			glUniform4iv(location, 1, values);
		}

		void ShaderProgram::setUniformMatrix(const int &location, const Matrix4 &matrix, const bool &transpose) {
			glUseProgram(program_id);
			glUniformMatrix4fv(location, 1, transpose ? GL_TRUE : GL_FALSE, matrix);
		}

		void ShaderProgram::setUniformMatrix3fv(const int &location, float const * const values, const bool &transpose) {
			glUseProgram(program_id);
			glUniformMatrix3fv(location, 1, transpose ? GL_TRUE : GL_FALSE, values);
		}

		void ShaderProgram::setUniformMatrix4fv(const int &location, float const * const values, const bool &transpose) {
			glUseProgram(program_id);
			glUniformMatrix4fv(location, 1, transpose ? GL_TRUE : GL_FALSE, values);
		}

	} // end of namespace Graphics
} // end of namespace Dwarf
