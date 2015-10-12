#ifndef SHADER_H
#define SHADER_H

#include "../DwarfSetup.h"
#include GLEW_H

#include <string>

namespace Dwarf
{
	namespace Graphics
	{

		class DWARFAPI Shader
		{
		public:
			enum Type {
				INVALID = 0,
				VERTEX,
				TESS_CTRL,
				TESS_EVAL,
				GEOMETRY,
				FRAGMENT,
				COMPUTE
			};
		protected:
			GLuint shader_id;
			Type type;
			std::string source;

			// Internal use only
			void free();

		public:
			Shader();
			Shader(const Type &type);
			Shader(const Type &type, const std::string &source);
			~Shader();

			// Methods
			GLuint getID() const;

			Type getType() const;
			void setType(const Type &type);

			std::string getSource() const;
			void setSource(const std::string &source);

			bool isCompiled() const;
			void compile();
			std::string getInfoLog() const;
		};

	}
}

#endif
