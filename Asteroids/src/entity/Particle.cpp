#include "Particle.h"
#include "../Game.h"

namespace astro { namespace entity {

	Uint8 onRemoveCallback(int interval, void*param)
	{
		Particel *particel = (Particel*)param;
		particel->OnRemove();
		return 0;
	}

	Particel::Particel(graphics::Texture *tex, const math::Vector2f &pos, const float &angle, 
		const int &w, const int &h, const int& count, const int &time) 
	{
		m_Texture    = tex;
		m_Position.x = pos.x;
		m_Position.y = pos.y;
		m_Angle	     = angle;
		m_Width	     = w / count;
		m_Height     = h / count;
		m_Type	     = EntityType::Particle;

		m_Speed = 2.0f;

		m_Velocity = math::Vector2f(cos(m_Angle * PI / 180.0f) * m_Speed, sin(m_Angle * PI / 180.0f) * m_Speed);
		SDL_AddTimer(time, OnRemoveCallback, this);
	}
	
	Particel::~Particel() 
	{
	}

	void Particel::OnInput(const SDL_Event &event)
	{

	}
	
	void Particel::OnUpdate()
	{
		if (m_Position.x <= 0 || m_Position.x >= Game::GetScreenWidth() || m_Position.y <= 0 || m_Position.y >= Game::GetScreenHeight())
		{
			OnRemove();
		}

		m_Position += m_Velocity;
	}
	
	Uint32 Particel::OnRemoveCallback(Uint32 interval, void*param)
	{
		Entity* entity = (Entity*)param;
		entity->OnRemove();
		return 0;
	}

	void Particel::OnRender(graphics::Renderer2D *renderer) 
	{
		SDL_Rect rect = { m_Position.x, m_Position.y, m_Width, m_Height };
		SDL_Rect clip = { 10, 10, 45, 45 };

		renderer->RenderTexture(m_Texture, &clip, &rect);
	}

} }