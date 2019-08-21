#pragma once

#include "../Log.h"

#include "Texture.h"

#include <SDL/SDL.h>

namespace astro { namespace graphics {

	class Renderer2D
	{
	private:
		SDL_Renderer *m_Renderer;
		SDL_Rect	  m_Bounds;

	public:
		Renderer2D(SDL_Window *window, const int& flags = 0);
		~Renderer2D();

		void Clear();
		void SwapBuffers();

		void SetColor(const Uint8& r, const Uint8& g, const Uint8& b, const Uint8& a);		
		
		void FillRect(const int& x, const int& y, const int& width, const int& height);
		
		void DrawRect(const int& x, const int& y, const int& width, const int& height);
		
		void DrawPoint(const int& x, const int& y);
		
		void DrawLine(const int&x1, const int&y1, const int&x2, const int&y2);
		
		void RenderTexture(Texture *texture, SDL_Rect *clip, SDL_Rect *dims);
		void RenderTexture(Texture *texture, SDL_Rect *clip, SDL_Rect *dims, double angle, SDL_Point *center, const SDL_RendererFlip &flip);

		inline SDL_Renderer* GetContext() const { return m_Renderer; }
	};

} }