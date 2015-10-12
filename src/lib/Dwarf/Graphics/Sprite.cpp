#include <Dwarf/Graphics/Sprite.h>
#include <Dwarf/Util/ResourceManager.h>

using namespace Dwarf::Math;
using namespace Dwarf::Util;
using namespace std;

namespace Dwarf {
	namespace Graphics {

		Sprite::Sprite() {
			this->scale = Vector2(1, 1);
			this->rotation = 0;
		}

		Sprite::Sprite(Texture2D texture) {
			this->scale = Vector2(1, 1);
			this->rotation = 0;

			this->setTexture(texture);
		}

		Texture2D Sprite::getTexture() const {
			return this->texture_;
		}

		void Sprite::setTexture(Texture2D texture) {
			this->texture_ = texture;
			setRegion(0, 0, texture->getWidth(), texture->getHeight());
		}

		void Sprite::updateTexture(Texture2D texture) {
			this->texture_ = texture;
			if (region_.size.magnitude() <= 0) {
				// Region has not been set
				setRegion(0, 0, texture->getWidth(), texture->getHeight());
			}
		}

		Rectangle Sprite::getRegion() const {
			return this->region_;
		}

		void Sprite::setRegion(const int &x, const int &y, const int &w, const int &h) {
			this->region_ = Rectangle(x, y, w, h);
		}

		void Sprite::setRegion(const Math::Rectangle &rect) {
			this->region_.position.x = rect.position.x;
			this->region_.position.y = rect.position.y;
			this->region_.size.x = rect.size.x;
			this->region_.size.y = rect.size.y;
		}

	} // namespace Graphics
} // namespace Dwarf
