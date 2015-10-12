#include <Dwarf/Graphics/Camera2D.h>

using namespace Dwarf::Math;

namespace Dwarf {
	namespace Graphics {

		Camera2D::Camera2D(const size_t &screen_width, const size_t &screen_height)
		: screen_width(screen_width), screen_height(screen_height),
			position(0, 0), _camera_matrix(1.0f)
		{
			this->updateOrthoMatrix();
		}

		// --------------------------------

		void Camera2D::update() {
			// Center camera at specified position
			Vector3 translation(screen_width/2 - position.x, screen_height/2 - position.y, -0.1f);
			_camera_matrix =  _ortho_matrix * Matrix4::translate(translation);
		}

		// --------------------------------

		Matrix4 Camera2D::getCameraMatrix() const {
			return _camera_matrix;
		}

		// --------------------------------

		void Camera2D::setSize(const size_t &screen_width, const size_t &screen_height) {
			this->screen_width = screen_width;
			this->screen_height = screen_height;
			this->updateOrthoMatrix();
		}

		// --------------------------------

		void Camera2D::setWidth(const size_t &screen_width) {
			this->setSize(screen_width, this->screen_height);
		}

		// --------------------------------

		void Camera2D::setHeight(const size_t &screen_height) {
			this->setSize(this->screen_width, screen_height);
		}


		// --------------------------------

		void Camera2D::updateOrthoMatrix() {
			_ortho_matrix =
				Matrix4::ortho(0, screen_width, 0, screen_height, 0.1f, 1000);
		}

	} // namespace Math
} // namespace Dwarf
