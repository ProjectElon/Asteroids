#include "AlienBullet.h"
#include "../Game.h"

namespace astro { namespace entity {

	AlienBullet::AlienBullet(graphics::Texture *texture, const math::Vector2f &position, const math::Vector2f &shipPosition) 
	{
		m_Texture  = texture;
		m_Type     = EntityType::AlienShipBullet;
		m_Position = position;
		m_Speed	   = 3.7f;

		m_Width = m_Height = 18;

		math::Vector2f direction = shipPosition - m_Position;
		direction.Normalize();

		m_Velocity = direction * m_Speed;
	}

	AlienBullet::~AlienBullet() 
	{
	}

	void AlienBullet::OnInput(const SDL_Event &event) 
	{
	}
	
	void AlienBullet::OnUpdate() 
	{
		if (m_Position.x <= 0 || m_Position.y <= 0 || m_Position.x >= Game::GetScreenWidth() - m_Width || m_Position.y >= Game::GetScreenHeight() - m_Height)
		{
			OnRemove();
		}

		m_Position += m_Velocity;
	}
	
	void AlienBullet::OnRender(graphics::Renderer2D *renderer)
	{
		SDL_Rect rect = { m_Position.x, m_Position.y, m_Width, m_Height };
		SDL_Rect clip = { 0, 0, 32, 64 };
		renderer->RenderTexture(m_Texture, &clip, &rect);
	}

} }