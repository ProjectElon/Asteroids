#include "AlienShip.h"
#include "../Game.h"

namespace astro { namespace entity {

	AlienShip::AlienShip(graphics::Texture *texture, const math::Vector2f &shipPosition)
	{
		m_Type = EntityType::AlienShip;
		m_Texture = texture;
		m_ShipPosition = shipPosition;
		m_Speed = 2.5f;
		
		m_Width = m_Height = 48;

		m_XRange[TOP] = 0;
		m_YRange[TOP] = -m_Height;

		m_XRange[DOWN] = 0;
		m_YRange[DOWN] = Game::GetScreenHeight() + m_Width;

		m_XRange[LEFT] = -m_Width;
		m_YRange[LEFT] = 0;

		m_XRange[RIGHT] = Game::GetScreenWidth() + m_Width;
		m_YRange[RIGHT] = 0;

		m_SpawnDirection = rand() % TOTAL;
		
		m_Position = math::Vector2f(m_XRange[m_SpawnDirection], m_YRange[m_SpawnDirection]);

		if (m_Position.x == 0) m_Position.x = rand() % Game::GetScreenWidth();
		if (m_Position.y == 0) m_Position.y = rand() % Game::GetScreenHeight();
		
		math::Vector2f direction = (shipPosition - m_Position);
		direction.Normalize();

		m_Velocity = direction * m_Speed;
	}
	
	AlienShip::~AlienShip() 
	{
	}

	void AlienShip::OnInput(const SDL_Event &event) 
	{

	}
	
	void AlienShip::OnUpdate()
	{
		if (m_SpawnDirection == TOP   && m_Position.y >= Game::GetScreenHeight() ||
			m_SpawnDirection == DOWN  && m_Position.y <= 0 ||
			m_SpawnDirection == RIGHT && m_Position.x <= 0 || 
			m_SpawnDirection == LEFT  && m_Position.x >= Game::GetScreenWidth())
		{
			OnRemove();
		}
		
		m_Position += m_Velocity;
	}
	
	void AlienShip::OnRender(graphics::Renderer2D *renderer) 
	{
		SDL_Rect bounds = { m_Position.x, m_Position.y, m_Width, m_Height };
		renderer->RenderTexture(m_Texture, nullptr, &bounds);
	}

} }