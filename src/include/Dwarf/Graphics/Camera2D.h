#ifndef CAMERA_2D_H
#define CAMERA_2D_H

#include "../DwarfSetup.h"
#include "../Math/Vector2.h"
#include "../Math/Matrix4x4.h"

namespace Dwarf {
	namespace Graphics {

		class DWARFAPI Camera2D {
		private:
			Math::Matrix4 _camera_matrix;
			Math::Matrix4 _ortho_matrix;
			size_t screen_width;
			size_t screen_height;

		public:
			Math::Vector2 position;

			Camera2D(const size_t &screen_width, const size_t &screen_height);

			// Misc methods
			void update();

			// Getters
			Math::Matrix4 getCameraMatrix() const;

			// Setters
			void setSize(const size_t &screen_width, const size_t &screen_height);
			void setWidth(const size_t &screen_width);
			void setHeight(const size_t &screen_height);

		private:
			void updateOrthoMatrix();
		};

	};
};
#endif
