#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <string>

#include "../Log.h"

namespace astro { namespace graphics {

	class DynamicFont
	{
	private:
		SDL_Renderer *m_Renderer;
		SDL_Texture  *m_Texture;
		TTF_Font	 *m_Font;
		SDL_Rect	  m_Bounds;

		std::string m_Text;
		SDL_Color m_Color;

		TTF_Font* Load(const char* path, const int& size);

	public:
		DynamicFont(SDL_Renderer *renderer, const char *path, const int& size);
		~DynamicFont();

		void Post(const std::string &text, const SDL_Color& color);
		void Render(const int& x, const int& y);

		inline int GetWidth()  { return m_Bounds.w; }
		inline int GetHeight() { return m_Bounds.h; }

	};

} }