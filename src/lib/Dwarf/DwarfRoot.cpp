#include <Dwarf/DwarfRoot.h>

#include <Dwarf/Graphics/GLFWWindow.h>
#include <Dwarf/Input/Keyboard.h>
#include <Dwarf/Input/GLFWKeyboard.h>
#include <Dwarf/Util/Time.h>

#include <iostream>
using namespace std;

using namespace Dwarf::Graphics;
using namespace Dwarf::Input;
using namespace Dwarf::Util;

namespace Dwarf
{

	DwarfRoot::DwarfRoot()
	{
		/**
		 * GLFWInput should be used when GLFWWindow is used (same with SDL)
		 */
		window = new GLFWWindow("", 800, 600);
		Keyboard::set(new GLFWKeyboard);
	}

	// ----------------------------------------------------------------

	Window* DwarfRoot::getWindow()
	{
		return window;
	}

	// ----------------------------------------------------------------

	void DwarfRoot::initialize()
	{
		window->initialize();
		window->makeContextCurrent();

		// Initializes Time subsystem
		Time::INSTANCE().initialize();

		// Setups OpenGL stuff
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		/* glEnable(GL_CULL_FACE); */
		/* glCullFace(GL_FRONT); */
		glCullFace(GL_BACK);
	}

	// ----------------------------------------------------------------

	void DwarfRoot::destroy()
	{
		window->destroy();
		delete window;
		window = NULL;
	}

	// ----------------------------------------------------------------
	// Main game loop
	// see: http://gafferongames.com/game-physics/fix-your-timestep/
	// see: http://gameprogrammingpatterns.com/game-loop.html

	void DwarfRoot::run()
	{

		initialize();
		// User startup
		startup();

		// Gameloop
		float accumulator = 0;

		while (running)
		{
			// Updates the deltaTime stored in singleton Time
			Time::INSTANCE().step();
			float frameTime = Time::INSTANCE().delta();

			// Input
			window->updateEvents();
			// Check for quit event
			if (window->shouldQuit()) running = false;

			// Set accumulator limit to prevent spiral of death
			if (accumulator > 0.25)
				accumulator = 0.25;
			// Accumulate last frameTime
			accumulator += frameTime;
			// Consume anytime we have available
			while (accumulator >= Time::INSTANCE().fixed_step)
			{
				fixedUpdate();
				accumulator -= Time::INSTANCE().fixed_step;
			}

			// Calculates alpha with remaining accumulator
			Time::INSTANCE().setAlpha(accumulator / Time::INSTANCE().fixed_step);

			// Calls update and render
			update();
			render();

			// Swap buffers
			window->swapBuffers();

			++totalFrames;
		}

		// User shutdown
		shutdown();

		destroy();
	}

	// ----------------------------------------------------------------

	long DwarfRoot::getTotalFrames()
	{
		return totalFrames;
	}

	// ----------------------------------------------------------------

	void DwarfRoot::startup()
	{

	}

	// ----------------------------------------------------------------

	void DwarfRoot::shutdown()
	{

	}

	// ----------------------------------------------------------------

	void DwarfRoot::fixedUpdate()
	{

	}

	// ----------------------------------------------------------------

	void DwarfRoot::update()
	{

	}

	// ----------------------------------------------------------------

	void DwarfRoot::render()
	{

	}

}
