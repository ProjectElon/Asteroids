#pragma once

#include <string>

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <sstream>

#include "../Log.h"

namespace astro { namespace graphics {

	class StaticFont
	{
	private:
		SDL_Renderer *m_Renderer;
		TTF_Font	 *m_Font;
		SDL_Texture	 *m_Texture;
		SDL_Rect	  m_Bounds;
		
		TTF_Font* Load(const char *fontPath, const int& size);
		void Post(const std::string& text, const SDL_Color &color);

	public:
		StaticFont(SDL_Renderer* renderer, const char *fontPath, const int& size, const std::string& text, const SDL_Color &color);
		~StaticFont();

		void Render(const int& x, const int& y);

		inline int GetWidth()  { return m_Bounds.w; }
		inline int GetHeight() { return m_Bounds.h; }
	};

} }