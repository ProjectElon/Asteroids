#include "Ship.h"
#include "../Game.h"

namespace astro { namespace entity {

	Ship::Ship(graphics::Texture *texture, const math::Vector2f &position) 
	{
		m_Texture  = texture;
		m_Position = position;
		m_Type	   = EntityType::Ship;

		m_Width  = 35;
		m_Height = 35;
		m_Lifes  = 4;
		m_IsHit  = false;
		m_Alpha  = 255;
		m_Speed = 0.2f;
	}
	
	Ship::~Ship()
	{
	}

	void Ship::OnInput(const SDL_Event &event)
	{
		if (input::Keyboard::IsKeyDown(SDL_SCANCODE_UP))
		{
			m_IsBoosting = true;
		}
		else
		{
			m_IsBoosting = false;
		}

		if (input::Keyboard::IsKeyDown(SDL_SCANCODE_SPACE) && event.key.repeat == 0)
		{
			if (!m_IsShooting)
			{
				m_IsShooting = true;
			}
		}

		if (input::Keyboard::IsKeyUp(SDL_SCANCODE_SPACE))
		{
			m_IsShooting = false;
		}

		if (input::Keyboard::IsKeyDown(SDL_SCANCODE_RIGHT))
		{
			m_Angle += m_AngularSpeed;
		}
		else if (input::Keyboard::IsKeyDown(SDL_SCANCODE_LEFT))
		{
			m_Angle -= m_AngularSpeed;
		}
	}

	void Ship::OnUpdate()
	{
		if (m_IsBoosting)
		{
			m_Velocity.x += cos(m_Angle * PI / 180.0f) * m_Speed;
			m_Velocity.y += sin(m_Angle * PI / 180.0f) * m_Speed;
			m_Clip.y = 40;
		}
		else
		{
			m_Velocity *= 0.95f;
		}

		if (m_Velocity.Length() >= m_MaxSpeed)
		{
			m_Velocity /= m_MaxSpeed;
		}

		if (m_Velocity.Length() <= 1.0f)
		{
			m_Clip.y = 0;
		}

		if (m_IsHit)
		{
			m_Alpha-=75;
			if (m_Alpha <= 0) m_Alpha = 255;
		}
		else
		{
			m_Alpha = 255;
		}

		PassThrowEdages(0, 0, Game::GetScreenWidth(), Game::GetScreenHeight());
		
		m_Position += m_Velocity;
	}

	void Ship::OnRender(graphics::Renderer2D *renderer) 
	{
		m_Dims.x = m_Position.x, m_Dims.y = m_Position.y, m_Dims.w = m_Width, m_Dims.h = m_Height;
		m_Texture->SetAlpha(m_Alpha);
		renderer->RenderTexture(m_Texture, &m_Clip, &m_Dims, m_Angle + 90.0f, nullptr, SDL_FLIP_NONE);
	}

} }