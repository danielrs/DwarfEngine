#include <Dwarf/Graphics/GLFWWindow.h>

#include <Dwarf/Input/Keyboard.h>
#include <Dwarf/Util/Logger.h>
#include <Dwarf/Util/Misc.h>

using namespace std;
using namespace Dwarf::Input;
using namespace Dwarf::Util;

namespace Dwarf
{
	namespace Graphics
	{

		GLFWWindow::GLFWWindow(const string &title, const size_t &width, const size_t &height)
		{
			this->title = string(title);
			this->width = width;
			this->height = height;

			should_quit = false;
			use_vsync = false;

			window = NULL;
		}

		// ----------------------------------------------------------------

		GLFWWindow::~GLFWWindow()
		{
			destroy();
		}

		// ----------------------------------------------------------------

		void GLFWWindow::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
		{
			UNUSED(window);
			UNUSED(scancode);
			UNUSED(mods);

			if (action == GLFW_PRESS)
				Keyboard::keyPressed(Keyboard::get().translate(key));
			else if (action == GLFW_RELEASE)
				Keyboard::keyReleased(Keyboard::get().translate(key));
		}

		// ----------------------------------------------------------------

		bool GLFWWindow::initialize()
		{

			if (!glfwInit())
			{
				Logger::log(Logger::V_ERROR, "[%s:%d] Error initializing GLFW\n", __FILE__, __LINE__);
			}
			else
			{
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
				glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
				glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

				window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
				glfwSetKeyCallback(window, keyCallback);

				if (window == NULL)
				{
					Logger::log(Logger::V_ERROR, "[%s:%d] Error creating GLFW window\n", __FILE__, __LINE__);
					glfwTerminate();
				}
				else
				{
					return true;
				}
			}

			return false;
		}

		// ----------------------------------------------------------------

		void GLFWWindow::destroy()
		{
			glfwTerminate();
		}

		// ----------------------------------------------------------------

		void GLFWWindow::setTitle(const string &title)
		{
			this->title = string(title);
			if (window)
				glfwSetWindowTitle(window, title.c_str());
		}

		// ----------------------------------------------------------------

		void GLFWWindow::setSize(const size_t &width, const size_t &height)
		{
			this->width = width;
			this->height = height;

			glfwSetWindowSize(window, width, height);
		}

		// ----------------------------------------------------------------

		string GLFWWindow::getTitle() const
		{
			return title;
		}

		// ----------------------------------------------------------------

		int GLFWWindow::getWidth() const
		{
			return width;
		}

		// ----------------------------------------------------------------

		int GLFWWindow::getHeight() const
		{
			return height;
		}

		// ----------------------------------------------------------------

		float GLFWWindow::getAspect() const
		{
			return width / (float) height;
		}

		// ----------------------------------------------------------------

		void GLFWWindow::updateEvents()
		{
			glfwPollEvents();
			if (glfwWindowShouldClose(window))
				quit();
		}

		// ----------------------------------------------------------------

		void GLFWWindow::makeContextCurrent()
		{
			if (window)
			{
				glfwMakeContextCurrent(window);

				glewExperimental = true;
				GLenum glewError = glewInit();
				if (glewError != GLEW_OK)
					Logger::log(Logger::V_ERROR, "[%s:%d] Error initializing glew\n", __FILE__, __LINE__);

				useVSync(use_vsync);
			}
		}

		// ----------------------------------------------------------------

		void GLFWWindow::swapBuffers()
		{
			glfwSwapBuffers(window);
		}

		// ----------------------------------------------------------------

		void GLFWWindow::useVSync(bool active)
		{
			use_vsync = active;
			glfwSwapInterval(active ?  1 : 0);
		}

		// ----------------------------------------------------------------

		void GLFWWindow::quit()
		{
			should_quit = true;
		}

		bool GLFWWindow::shouldQuit()
		{
			return should_quit;
		}

	} // End of namespace Graphics
} // End of namespace Dwarf

