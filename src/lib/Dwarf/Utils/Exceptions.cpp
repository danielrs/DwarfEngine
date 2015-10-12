#include <Dwarf/Util/Exceptions.h>

using namespace std;

namespace Dwarf {
	namespace Util {

		FileNotFoundException::FileNotFoundException(const string &filename) {
			this->filename_ = filename;
		}
		const char* FileNotFoundException::what() const throw() {
			return (string("File not found: ") + filename_).c_str();
		}

		// ------------------

		const char* ResourceTypeNotValidException::what() const throw() {
			return "Resource type not valid!";
		}

		// ------------------

		IllegalStateException::IllegalStateException(const string &message) {
			this->message_ = message;
		}

		const char* IllegalStateException::what() const throw() {
			return (string("Illegal State Exception: ") + message_).c_str();
		}

		IllegalArgumentException::IllegalArgumentException(const string &message) {
			this->message_ = message;
		}

		const char* IllegalArgumentException::what() const throw() {
			return (string("Illegal Argument Exception: ") + message_).c_str();
		}

	} // namespace Util
} // namespace Dwarf
