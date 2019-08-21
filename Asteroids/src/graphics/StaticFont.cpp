#include "StaticFont.h"

namespace astro { namespace graphics {

	StaticFont::StaticFont(SDL_Renderer* renderer, const char *fontPath, const int& size, const std::string& text, const SDL_Color &color)
		: m_Renderer(renderer), m_Font(nullptr), m_Texture(nullptr)
	{
		m_Font = Load(fontPath, size);
		Post(text, color);
	}
	
	StaticFont::~StaticFont()
	{
		if (m_Texture != nullptr)
		{
			SDL_DestroyTexture(m_Texture);
			m_Texture = nullptr;
		}

		if (m_Font != nullptr) 
		{
			TTF_CloseFont(m_Font);
			m_Font = nullptr;
		}
	}

	TTF_Font* StaticFont::Load(const char* fontPath, const int& size)
	{
		TTF_Font* font = TTF_OpenFont(fontPath, size);

		if (font == nullptr)
		{
			TTF_LogError();
		}

		return font;
	}

	void StaticFont::Post(const std::string& text, const SDL_Color &color)
	{
		SDL_Surface *surface = TTF_RenderText_Blended(m_Font, text.c_str(), color);
		
		if (surface == nullptr)
		{
			TTF_LogError();
		}

		m_Texture  = SDL_CreateTextureFromSurface(m_Renderer, surface);
		
		m_Bounds.w = surface->w;
		m_Bounds.h = surface->h;
			
		SDL_FreeSurface(surface);
	}

	void StaticFont::Render(const int& x, const int& y)
	{
		m_Bounds.x = x, m_Bounds.y = y;
		SDL_RenderCopy(m_Renderer, m_Texture, nullptr, &m_Bounds);	
	}

} }