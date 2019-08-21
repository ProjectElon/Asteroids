#include "Window.h"

namespace astro { namespace graphics {
	
	Window::Window(const char *title, const int& width, const int& height, const Uint32& flags)
		: m_Title(title), m_Width(width), m_Height(height), m_WindowHandle(nullptr)
	{
		Init(flags);
	}

	Window::~Window()
	{
		if (m_WindowHandle != nullptr)
		{
			SDL_DestroyWindow(m_WindowHandle);
			m_WindowHandle = nullptr;
		}

		Mix_Quit();
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	bool Window::Init(const Uint32& flags)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		{
			SDL_LogError();
			return false;
		}

		m_WindowHandle = SDL_CreateWindow( m_Title,
						 SDL_WINDOWPOS_CENTERED,
						 SDL_WINDOWPOS_CENTERED, 
						 m_Width, 
						 m_Height, 
						 SDL_WINDOW_SHOWN | flags );

		if (m_WindowHandle == nullptr)
		{
			SDL_LogError();
			return false;
		}

		int img_flags = IMG_INIT_PNG | IMG_INIT_JPG;
		
		if (!(IMG_Init(img_flags) & img_flags))
		{
			IMG_LogError();
			return false;
		}

		if (TTF_Init() == -1)
		{
			TTF_LogError();
			return false;
		}

		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
		{
			MIX_LogError();
			return false;
		}
		
		return true;
	}

} }