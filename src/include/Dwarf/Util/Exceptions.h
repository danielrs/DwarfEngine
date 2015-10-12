#ifndef DWARF_UTIL_EXCEPTIONS_H
#define DWARF_UTIL_EXCEPTIONS_H

#include "../DwarfSetup.h"
#include <string>

namespace Dwarf {
	namespace Util {

		class DWARFAPI FileNotFoundException : public std::exception {
		public:
			FileNotFoundException(const std::string &filename);
			const char* what() const throw() override;
		private:
			std::string filename_;
		};

		// ------------------

		class DWARFAPI ResourceTypeNotValidException : public std::exception {
		public:
			const char* what() const throw() override;
		};

		// ------------------

		class DWARFAPI IllegalStateException : public std::exception {
		public:
			IllegalStateException(const std::string &message);
			const char* what() const throw() override;
		private:
			std::string message_;
		};

		class DWARFAPI IllegalArgumentException : public std::exception {
		public:
			IllegalArgumentException(const std::string &message);
			const char* what() const throw() override;
		private:
			std::string message_;
		};

	} // namespace Util
} // namespace Dwarf

#endif
