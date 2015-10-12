#include <Dwarf/Math/Misc.h>
#include <cmath>

using namespace std;

namespace Dwarf
{
	namespace Math
	{

		float clamp(const float &value, const float &lower, const float &upper) {
			return max(lower, min(value, upper));
		}

		// see: http://en.wikipedia.org/wiki/Slerp
		// For both implementations
		float lerp(const float &start, const float &end, const float &time)
		{
			return (start + (end - start)*time);
		}

		Vector2 lerp(const Vector2 &start, const Vector2 &end, const float &time) {
			return Vector2(lerp(start.x, end.x, time), lerp(start.y, end.y, time));
		}

		// ----------------------------------------------------------------

		float slerp(const float &start, const float &end, const float &time)
		{
			Vector2 a(cos(start), sin(start));
			Vector2 b(cos(end), sin(end));

			float omega = Vector2::dot(a, b);

			return (sin((1 - time)*omega) / sin(omega) * start + sin(time*omega) / sin(omega) * end);
		}

	}
}
