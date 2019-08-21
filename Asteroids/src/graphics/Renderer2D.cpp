#include "Renderer2D.h"

namespace astro { namespace graphics {

	Renderer2D::Renderer2D(SDL_Window *window, const int& flags)
	{
		m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | flags);
		
		if (m_Renderer == nullptr)
		{
			SDL_LogError();
		}
		
		SDL_RendererInfo info;
		SDL_GetRendererInfo(m_Renderer, &info);
		log(info.name);
	}

	Renderer2D::~Renderer2D()
	{
		if (m_Renderer != nullptr)
		{
			SDL_DestroyRenderer(m_Renderer);
			m_Renderer = nullptr;
		}
	}

	void Renderer2D::Clear()
	{
		SDL_RenderClear(m_Renderer);
	}

	void Renderer2D::SwapBuffers()
	{
		SDL_RenderPresent(m_Renderer);
	}

	void Renderer2D::SetColor(const Uint8& r, const Uint8& g, const Uint8& b, const Uint8& a)
	{
		SDL_SetRenderDrawColor(m_Renderer, r, g, b, a);
	}

	void Renderer2D::FillRect(const int& x, const int& y, const int& width, const int& height)
	{
		m_Bounds.x = x, m_Bounds.y = y, m_Bounds.w = width, m_Bounds.h = height;
		SDL_RenderFillRect(m_Renderer, &m_Bounds);
	}

	void Renderer2D::DrawRect(const int& x, const int& y, const int& width, const int& height) 
	{
		m_Bounds.x = x, m_Bounds.y = y, m_Bounds.w = width, m_Bounds.h = height;
		SDL_RenderDrawRect(m_Renderer, &m_Bounds);
	}

	void Renderer2D::DrawPoint(const int& x, const int& y) 
	{
		SDL_RenderDrawPoint(m_Renderer, x, y);
	}

	void Renderer2D::DrawLine(const int&x1, const int&y1, const int&x2, const int&y2)
	{
		SDL_RenderDrawLine(m_Renderer, x1, y1, x2, y2);
	}

	void Renderer2D::RenderTexture(Texture *texture, SDL_Rect *clip, SDL_Rect *dims) 
	{

		SDL_RenderCopy(m_Renderer, texture->GetHandle(), clip, dims);
	}

	void Renderer2D::RenderTexture(Texture *texture, SDL_Rect *clip, SDL_Rect *dims, double angle, SDL_Point *center, const SDL_RendererFlip &flip)
	{
		SDL_RenderCopyEx(m_Renderer, texture->GetHandle(), clip, dims, angle, center, flip);
	}


} }