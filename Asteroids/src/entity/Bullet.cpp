#include "Bullet.h"
#include "../Game.h"

namespace astro { namespace entity {


	Bullet::Bullet(graphics::Texture *texture, const math::Vector2f& position, const float& angle)
	{
		this->m_Texture    = texture;
		this->m_Position.x = position.x + 16 / 2;
		this->m_Position.y = position.y + 16 / 2;
		this->m_Type	   = EntityType::SpaceShipBullet;
		this->m_Angle	       = angle;
		
		this->m_Width      = 14;
		this->m_Height     = 14;

		m_Speed = 4.5f;

		m_Velocity = math::Vector2f(cos(angle * PI / 180.0f) * m_Speed, sin(angle * PI / 180.0f) * m_Speed);
	}

	Bullet::~Bullet() 
	{
	}

	void Bullet::OnInput(const SDL_Event &event)
	{
	}
	
	void Bullet::OnUpdate() 
	{
		if (m_Position.x <= 0 || m_Position.y <= 0 || m_Position.x >= Game::GetScreenWidth() - (int)m_Width || m_Position.y >= Game::GetScreenHeight() - (int)m_Height)
		{
			OnRemove();
		}

		m_Position += m_Velocity;
	}
	
	void Bullet::OnRender(graphics::Renderer2D *renderer) 
	{
		SDL_Rect rect = { m_Position.x, m_Position.y, m_Width, m_Height };
		SDL_Rect clip = { 0, 0, 32, 64 };
		
		renderer->RenderTexture(m_Texture, &clip, &rect);
	}

} }