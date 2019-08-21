#pragma once

#include "../Log.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

namespace astro { namespace graphics {
	
	class Texture
	{
	private:
		SDL_Texture  *m_Texture;
		SDL_Renderer *m_Renderer;
		int			  m_Width;
		int			  m_Height;
		const char   *m_Path;
		
		SDL_Texture* LoadFromFile();

	public:
		Texture(SDL_Renderer *renderer, const char *path);
		~Texture();
		
		void SetAlpha(const Uint8 &alpha);

		inline SDL_Texture*  GetHandle()	{ return m_Texture;  }
		inline SDL_Renderer* GetRenderer()  { return m_Renderer; }
		
		inline int GetWidth()		 { return m_Width;	}
		inline int GetHeight()		 { return m_Height; }
		inline const char* GetPath() { return m_Path;   }
	};

} }