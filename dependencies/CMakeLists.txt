cmake_minimum_required(VERSION 2.8.8)
project(DwarfDependencies)

include(ExternalProject)

option(BUILD_SHARED_LIBS "Build shared libraries" ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules")

# --------------------------------
# External dependencies
# --------------------------------

set(DWARF_EXTERNAL_DOWNLOAD "${CMAKE_CURRENT_BINARY_DIR}/download"
	CACHE PATH "Download directory for dependencies packages.")
set(DWARF_EXTERNAL_INSTALL_PREFIX "${CMAKE_CURRENT_BINARY_DIR}/install/${CMAKE_SYSTEM_NAME}"
	CACHE PATH "Installation path of dependencies.")

# OpenGL
find_package(OpenGL REQUIRED)
if (NOT OPENGL_FOUND)
	message(FATAL_ERROR "OpenGL is not installed and it is required.")
endif()

# GLFW
find_package(GLFW)
if (NOT GLFW_FOUND)
	message(STATUS "GLFW not found. Will build remotely.")
	include(ExternalGLFW)
endif()

# ASSIMP
#find_package(ASSIMP)
#if (NOT ASSIMP_FOUND)
#	message(STATUS "Assimp not found. Will build remotely.")
#	include(ExternalASSIMP)
#endif()

# --------------------------------
#	Fix install_name of installed libraries
# --------------------------------
# The script changes the install_name of all the dylibs in the specified directory to
# @rpath/lib<LIB>.dylib
# That way they can be easily used by other executables defining the rpath entry

if(APPLE)
	# execute_process(
	# 	COMMAND
	# 		"${PROJECT_SOURCE_DIR}/../scripts/rpath.sh" "${DWARF_EXTERNAL_INSTALL_PREFIX}/lib"
	# )
	# Uses add_custom_target instead, so it gets executed at build time
	add_custom_target(FIX_INSTALL_NAME ALL
		DEPENDS GLFW ASSIMP
		COMMAND
			"${PROJECT_SOURCE_DIR}/../scripts/rpath.sh" "${DWARF_EXTERNAL_INSTALL_PREFIX}/lib"
		COMMENT "Fixing install_name for installed *.dylibs"
	)
endif()
