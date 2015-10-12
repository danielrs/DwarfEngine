#ifndef DWARF_GRAPHICS_GLFWWINDOW_H
#define DWARF_GRAPHICS_GLFWWINDOW_H

#include "../DwarfSetup.h"
#include "Window.h"

/**
 * NOTE
 * leave this includes in the order: glew, opengl, glfw
 */
#include GLEW_H
#include OPENGL_H
#include "GLFW/glfw3.h"

namespace Dwarf
{
	namespace Graphics
	{

		class DWARFAPI GLFWWindow : public Window
		{
		private:
			std::string title;
			size_t width;
			size_t height;

			bool should_quit;
            bool use_vsync;

			/**
			 * Note this is not a pointer to the same class defined in this file,
			 * this is a pointer of the class GLFWwindow defined in glfw3.h
			 */
			GLFWwindow *window;

			static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

		public:
			GLFWWindow(const std::string &title, const size_t &width, const size_t &height);
			~GLFWWindow();

			bool initialize() override;
			void destroy() override;

			void setTitle(const std::string &title) override;
			void setSize(const size_t &width, const size_t &height) override;

			std::string getTitle() const override;
			int getWidth() const override;
			int getHeight() const override;
			float getAspect() const override;

			void updateEvents() override;

			void makeContextCurrent() override;
			void swapBuffers() override;
			void useVSync(bool active) override;

			// Quit event
			void quit() override;
			bool shouldQuit() override;
		};
	}
}

#endif // GLFWWINDOW_H
