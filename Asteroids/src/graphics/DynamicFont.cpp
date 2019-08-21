#include "DynamicFont.h"

namespace astro { namespace graphics {

	DynamicFont::DynamicFont(SDL_Renderer *renderer, const char *path, const int& size) 
		: m_Renderer(renderer), m_Texture(nullptr)  
	{
		m_Font = Load(path, size);
	}

	DynamicFont::~DynamicFont() 
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

	TTF_Font* DynamicFont::Load(const char* path, const int& size)
	{
		TTF_Font *font = TTF_OpenFont(path, size);
		
		if (m_Font == nullptr) 
		{
			TTF_LogError();
		}

		return font;
	}

	void DynamicFont::Post(const std::string &text, const SDL_Color& color)
	{
		SDL_Surface *surface = TTF_RenderText_Blended(m_Font, text.c_str(), color);
		m_Texture = SDL_CreateTextureFromSurface(m_Renderer, surface);
		m_Bounds.w = surface->w, m_Bounds.h = surface->h;
		SDL_FreeSurface(surface);
	}

	void DynamicFont::Render(const int& x, const int& y)
	{
		m_Bounds.x = x;
		m_Bounds.y = y;
		SDL_RenderCopy(m_Renderer, m_Texture, nullptr, &m_Bounds);
		SDL_DestroyTexture(m_Texture);
		m_Texture = nullptr;
	}

} }