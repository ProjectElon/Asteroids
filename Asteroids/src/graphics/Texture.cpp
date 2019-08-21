#include "Texture.h"

namespace astro { namespace graphics {
	
	Texture::Texture(SDL_Renderer *renderer, const char *path)
		: m_Texture(nullptr), m_Renderer(renderer), m_Width(0), m_Height(0), m_Path(path)
	{
		m_Texture = LoadFromFile();
	}

	Texture::~Texture()
	{
		if (m_Texture != nullptr)
		{
			SDL_DestroyTexture(m_Texture);
			m_Texture = nullptr;
		}
	}

	SDL_Texture* Texture::LoadFromFile()
	{
		SDL_Texture *texture = nullptr;
		SDL_Surface *image	 = IMG_Load(m_Path);
		
		if (image == nullptr)
		{
			IMG_LogError();
		}

		texture = SDL_CreateTextureFromSurface(m_Renderer, image);
		
		m_Width	 = image->w;
		m_Height = image->h;

		SDL_FreeSurface(image);

		return texture;
	}

	void Texture::SetAlpha(const Uint8 &alpha)
	{
		SDL_SetTextureAlphaMod(m_Texture, alpha);
	}

} }