#include "Asteroid.h"
#include "../Game.h"

namespace astro { namespace entity {

	Asteroid::Asteroid(graphics::Texture *texture, const math::Vector2f &ShipPos, math::Vector2f *position, float *angle)
	{
		m_Texture = texture;
		m_Type = EntityType::Asteroid;

		m_Width = m_Height = 60;
		m_Speed = 1.5f;

		if (position == nullptr)
		{
			do 
			{
				m_Position.x = rand() % Game::GetScreenWidth() - m_Width;
				m_Position.y = rand() % Game::GetScreenHeight() - m_Height;
			} 
			while (m_Position.Distance(ShipPos) <= m_SpwanRange);
		}
		else
		{
			m_Position = *position;
		}

		if (angle == nullptr) 
		{
			m_Velocity.x = 1 + rand() % 2;
			m_Velocity.y = 1 + rand() % 2;
		}
		else
		{
			m_Velocity = math::Vector2f(cos((*angle) * PI / 180.0f) * m_Speed, sin((*angle) * PI / 180.0f) * m_Speed);
		}
	}

	Asteroid::~Asteroid()
	{
	}

	void Asteroid::OnInput(const SDL_Event &event)
	{

	}
	
	void Asteroid::OnUpdate()
	{
		PassThrowEdages(0, 0, Game::GetScreenWidth(), Game::GetScreenHeight());
		m_Position += m_Velocity;
	}

	void Asteroid::OnRender(graphics::Renderer2D *renderer) 
	{
		SDL_Rect rect = { m_Position.x, m_Position.y, m_Width, m_Height };
		SDL_Rect clip = { 10, 10, 45, 45 };
		renderer->RenderTexture(m_Texture, &clip, &rect);
	}

} }