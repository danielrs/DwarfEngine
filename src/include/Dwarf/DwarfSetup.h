#ifndef DWARF_SETUP_H
#define DWARF_SETUP_H

// Define export API
#if defined(DWARF_STATIC) || !defined(_WIN32)
#define DWARFAPI
#elif defined(_WIN32)
	#if defined(DWARF_BUILD)
	#define DWARFAPI __declspec(dllexport)
	#else
	#define DWARFAPI __declspec(dllimport)
	#endif
#endif

// Macros for GLEW, STB_IMAGE and OpenGL includes
#define GLEW_H "/home/danielrs/Development/Projects/DwarfEngine/3rdParty/Universal/glew/include/GL/glew.h"

#define STB_IMAGE_H "/home/danielrs/Development/Projects/DwarfEngine/3rdParty/Universal/stb_image/include/stb_image.h"

#ifdef __APPLE__
#define OPENGL_H <OpenGL/gl.h>
#else
#define OPENGL_H <GL/gl.h>
#endif

#endif // DWARF_SETUP_H
