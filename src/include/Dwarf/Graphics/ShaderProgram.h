#ifndef DWARF_GRAPHICS_SHADERPROGRAM_H
#define DWARF_GRAPHICS_SHADERPROGRAM_H

#include "../DwarfSetup.h"
#include GLEW_H
#include "../Util/IDisposable.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Matrix4x4.h"

#include <map>
#include <list>
#include <string>

namespace Dwarf
{
	namespace Graphics
	{
		// Forward declare Shader
		class Shader;

		class DWARFAPI ShaderProgram : public Util::IDisposable
		{
		private:
			std::list<Shader*> shaders;
			// Maps for memoization of locations
			std::map<std::string, int> attributes;
			std::map<std::string, int> uniforms;

		protected:
			GLuint program_id;
		public:
			ShaderProgram();
			~ShaderProgram();

			void dispose() override;

			GLuint getID() const;

			void attachShader(Shader *shader);
			void clearShaders();
			bool isLinked();
			void link();

			std::string getInfoLog() const;

			// Attributes and Uniforms
			int getAttribLocation(const std::string &name);
			int getUniformLocation(const std::string &name);

			void setUniformf(const int &location, const float &value1);
			void setUniformf(const int &location, const float &value1, const float &value2);
			void setUniformf(const int &location, const float &value1, const float &value2, const float &value3);
			void setUniformf(const int &location, const float &value1, const float &value2, const float &value3, const float &value4);
			void setUniformf(const int &location, const Math::Vector2 &values);
			void setUniformf(const int &location, const Math::Vector3 &values);
			void setUniformf(const int &location, const Math::Vector4 &values);
			void setUniformi(const int &location, const int &value1);
			void setUniformi(const int &location, const int &value1, const int &value2);
			void setUniformi(const int &location, const int &value1, const int &value2, const int &value3);
			void setUniformi(const int &location, const int &value1, const int &value2, const int &value3, const int &value4);

			void setUniform1fv(const int &location, float const * const values);
			void setUniform2fv(const int &location, float const * const values);
			void setUniform3fv(const int &location, float const * const values);
			void setUniform4fv(const int &location, float const * const values);
			void setUniform1iv(const int &location, int const * const values);
			void setUniform2iv(const int &location, int const * const values);
			void setUniform3iv(const int &location, int const * const values);
			void setUniform4iv(const int &location, int const * const values);

			void setUniformMatrix(const int &location, const Math::Matrix4 &matrix, const bool &transpose);
			void setUniformMatrix3fv(const int &location, float const * const values, const bool &transpose);
			void setUniformMatrix4fv(const int &location, float const * const values, const bool &transpose);

		};

	} // namespace Graphics
} // namespace Dwarf
#endif
