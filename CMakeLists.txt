cmake_minimum_required(VERSION 2.8)

# --------------------------------
#	Project initialization
# --------------------------------

project(DwarfEngine)

# The version number
set(DWARF_VERSION_MAJOR 0)
set(DWARF_VERSION_MINOR 1)

# Project variables
set(DWARF_LIBRARY_NAME Dwarf)

# Other variables
option(BUILD_SHARED_LIBS "Build shared libraries" ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/Modules/")

# --------------------------------
#	Dependencies
# --------------------------------

#
# Check if they are installed
#

set(DWARF_EXTERNAL_INSTALL_PREFIX "${PROJECT_SOURCE_DIR}/dependencies/build/install/${CMAKE_SYSTEM_NAME}"
	CACHE PATH "Installation path of dependencies.")
set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${DWARF_EXTERNAL_INSTALL_PREFIX})

message(STATUS "Checking dependencies...")

find_package(OpenGL QUIET)
find_package(GLFW QUIET)
find_package(ASSIMP QUIET)

set (DEPS_SATISFIED ON)

if(NOT OPENGL_FOUND)
	set(DEPS_SATISFIED OFF)
	message(WARNING "Dependency not satisfied: OpenGL")
endif()
if(NOT GLFW_FOUND)
	set(DEPS_SATISFIED OFF)
	message(WARNING "Dependency not satisfied: GLFW")
endif()
#if(NOT ASSIMP_FOUND)
#	set(DEPS_SATISFIED OFF)
#	message(WARNING "Dependency not satisfied: Assimp")
#endif()

if(NOT DEPS_SATISFIED)
	message(FATAL_ERROR "Dependencies not satisfied! Try to install them first! (and set the DWARF_EXTERNAL_INSTALL_PREFIX to a valid value)")
endif()

#
# Add them to project
#

message(STATUS "Dependencies satisfied!")

# Sets the include directories
set(DWARF_DEPS_INCLUDE_DIRS
	${GLFW_INCLUDE_DIR}
	${OPENGL_INCLUDE_DIR}
	#${ASSIMP_INCLUDE_DIR}
	# CACHE STRING "Dwarf Engine include directories of dependencies"
)

# Sets the link libraries
set(DWARF_DEPS_LIBRARIES
	${GLFW_LIBRARIES}
	${OPENGL_LIBRARIES}
	#${ASSIMP_LIBRARIES}
)

# --------------------------------
#	Compiler and linker preparation
# --------------------------------

#
# Definitions and flags
#

add_definitions(-DDWARF_BUILD -DGLEW_BUILD -DGLEW_NO_GLU)
if (NOT ${BUILD_SHARED_LIBS})
	add_definitions(-DDWARF_STATIC -DGLEW_STATIC -DSTB_IMAGE_STATIC)
endif()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
	"${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(warnings "-Wall -Wextra")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
	set(warnings "/W4 /Wx /EHsc")
endif()
if (NOT CONFIGURED_ONCE)
	set(CMAKE_CXX_FLAGS "${warnings} -std=c++11"
		CACHE STRING "Flags used by the compiler during all buidls types." FORCE)
	set(CMAKE_C_FLAGS "${warnings}"
		CACHE STRING "Flags used by the compiler during all builds types." FORCE)
endif()

#
# Include and link directories
#

set(DWARF_INCLUDE_DIRECTORIES
	${CMAKE_CURRENT_SOURCE_DIR}/src/include
	${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/Universal/glew/include
	${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/Universal/sb6/include
	${DWARF_DEPS_INCLUDE_DIRS}
)

include_directories(
	${DWARF_INCLUDE_DIRECTORIES}
)

#
# Source files
#

# Dwarf files
file(
	GLOB_RECURSE
	DWARF_SRC_FILES
	src/lib/*.cpp
)

# Universal files
set(DWARF_GLEW_H ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/Universal/glew/include/GL/glew.h)
set(DWARF_STB_IMAGE_H ${CMAKE_CURRENT_SOURCE_DIR}/3rdParty/Universal/stb_image/include/stb_image.h)
set(DWARF_SETUP_H ${CMAKE_CURRENT_SOURCE_DIR}/src/include/Dwarf/DwarfSetup.h)

file(
	GLOB_RECURSE
	EXTERNAL_SRC_FILES
	3rdParty/Universal/glew/src/glew.c
	3rdParty/Universal/sb6/src/*.cpp
)

# -------------------------------
#	Targets
# --------------------------------

add_library (
	${DWARF_LIBRARY_NAME}
	${EXTERNAL_SRC_FILES}
	${DWARF_SRC_FILES}
)

target_link_libraries(
	${DWARF_LIBRARY_NAME}
	${DWARF_DEPS_LIBRARIES}
)

# --------------------------------
#	Configuration of other files
# --------------------------------

configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/src/include/Dwarf/DwarfSetup.h.in
	${DWARF_SETUP_H}
	@ONLY
)

# --------------------------------
#	Package configuration
# --------------------------------

set(DWARF_PACKAGE_CONFIG_FILE ${CMAKE_CURRENT_BINARY_DIR}/${DWARF_LIBRARY_NAME}Config.cmake)

configure_file(
	src/cmake/${DWARF_LIBRARY_NAME}Config.cmake.in
	${DWARF_PACKAGE_CONFIG_FILE}
	@ONLY
)

# --------------------------------
#	Installation
# --------------------------------

install(TARGETS ${DWARF_LIBRARY_NAME} DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/include/Dwarf DESTINATION include)
install(FILES ${DWARF_PACKAGE_CONFIG_FILE} DESTINATION lib/cmake/${DWARF_LIBRARY_NAME})

# --------------------------------
#	CPack driven installer package
# --------------------------------

# include(InstallRequiredSystemLibraries)
# set(CPACK_RESOURCE_FILE_LICENSE
# 	"${CMAKE_CURRENT_SOURCE_DIR}/License.txt"
# )
# set(CPACK_PACKAGE_VERSION_MAJOR ${DWARF_VERSION_MAJOR})
# set(CPACK_PACKAGE_VERSION_MINOR ${DWARF_VERSION_MINOR})
# include(CPACK)

# --------------------------------
#	Other
# --------------------------------

set(CONFIGURED_ONCE TRUE CACHE INTERNAL "A flag showing that CMake has configured at least once.")

# find_package(Dwarf)
# if(DWARF_FOUND)
# 	message("FOUND")
# 	# message(${Dwarf_LIBRARIES})
# endif()
