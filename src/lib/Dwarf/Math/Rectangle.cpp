#include <Dwarf/Math/Rectangle.h>

namespace Dwarf {
	namespace Math {

		Rectangle::Rectangle() {}

		Rectangle::Rectangle(const Vector2 &position, const Vector2 &size) {

			this->position = position;
			this->size = size;
		}

		Rectangle::Rectangle(const float &x, const float &y, const float &width, const float &height) {
			this->position = Vector2(x, y);
			this->size = Vector2(width, height);
		}

	} // namespace Math
} // namespace Dwarf
