#ifndef DWARF_ROOT_H
#define DWARF_ROOT_H

#include "DwarfSetup.h"
#include "Graphics/Window.h"
#include "Input/IInput.h"

namespace Dwarf
{

	class DWARFAPI DwarfRoot
	{
	private:
		Graphics::Window* window;

	protected:
		bool running = true;
		long totalFrames = 0;
	public:
		DwarfRoot();

		Graphics::Window* getWindow();

		void initialize();
		void destroy();
		void run();
		long getTotalFrames();

		virtual void startup();
		virtual void shutdown();
		virtual void fixedUpdate();
		virtual void update();
		virtual void render();
	};

}

#endif
