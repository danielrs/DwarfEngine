#include <Dwarf/Util/FileSystem.h>
#include <Dwarf/Util/Logger.h>

#include <fstream>
#include <sstream>

using namespace std;

namespace Dwarf {
	namespace Util {

		string FileSystem::loadFile(const string &path) {
			string source;
			ifstream in_stream(path, ios::in);

			if (in_stream.is_open())
			{
				stringstream str_stream;
				str_stream << in_stream.rdbuf();
				source = str_stream.str();
			}
			else
			{
				Logger::log(Logger::V_ERROR, "[%s:%d] '%s' not found!\n", __FILE__, __LINE__, path.c_str());
			}

			return source;
		}

	}
}