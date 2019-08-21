#pragma once

#include "../Log.h"
#include "../input/Keyboard.h"
#include "../input/Mouse.h"

#include <SDL/SDL.h>

namespace astro { namespace graphics {

	class Window
	{
	private:
		const char  *m_Title;
		int          m_Width;
		int	         m_Height;

		SDL_Window  *m_WindowHandle;
		SDL_Event    m_WindowEvent;

		bool Init(const Uint32& flags);

	public:
		Window(const char *title, const int& width, const int& height, const Uint32& flags = 0);
		~Window();

		inline const char* GetTitle()   { return m_Title;  }
		inline int		   GetWidth()   { return m_Width;  }
		inline int		   GetHeight()  { return m_Height; }
		
		inline SDL_Window* GetHandle()  { return m_WindowHandle; }
		inline SDL_Event&  GetEvent()   { return m_WindowEvent;  }
	};

} }