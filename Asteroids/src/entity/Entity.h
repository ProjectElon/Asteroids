#pragma once

#include <SDL/SDL.h>

#include "../maths/Vector2f.h"
#include "../graphics/Renderer2D.h"
#include "../graphics/Texture.h"

namespace astro { namespace entity {
	
	enum class EntityType
	{
		Ship, 
		Asteroid, 
		SpaceShipBullet, 
		Particle, 
		AlienShip, 
		AlienShipBullet
	};

	class Entity
	{
	protected:
		EntityType         m_Type;
		math::Vector2f     m_Position; 
		math::Vector2f     m_Velocity;
		float			   m_Speed;
		graphics::Texture *m_Texture;
		int				   m_Width;
		int				   m_Height;
		bool			   m_IsRemoved;

	public:
		virtual ~Entity() {}

		virtual void OnInput(const SDL_Event &event) = 0;
		virtual void OnUpdate() = 0;
		virtual void OnRender(graphics::Renderer2D *renderer) = 0;

		inline const bool& IsRemoved() const { return m_IsRemoved; }
		inline const int& GetWidth()   const { return m_Width; }
		inline const int& GetHeight()  const { return m_Height; }
		inline const math::Vector2f& GetPosition() const { return m_Position; }
		inline const math::Vector2f& GetVelocity() const { return m_Velocity; }
		inline const EntityType& GetType() const { return m_Type; }

		inline void SetPosition(math::Vector2f position) { m_Position = position; }
		inline void SetWidth(int width) { m_Width = width; }
		inline void SetHeight(int height) { m_Height = height; }

		void PassThrowEdages(int sx, int sy, int xoffset, int yoffset)
		{
			if (m_Position.x < sx)
			{
				m_Position.x = xoffset - m_Width;
			}

			if (m_Position.y < sy)
			{
				m_Position.y = yoffset - m_Height;
			}

			if (m_Position.x > xoffset)
			{
				m_Position.x = sx + m_Width;
			}

			if (m_Position.y > yoffset)
			{
				m_Position.y = sy + m_Height;
			}
		}

		bool IsHitWith(Entity *other)
		{
			SDL_Rect rec1 = { m_Position.x, m_Position.y, m_Width, m_Height };
			SDL_Rect rec2 = { other->m_Position.x, other->m_Position.y, other->m_Width, other->m_Height };
			return SDL_HasIntersection(&rec1, &rec2);
		}
		
		inline void OnRemove()
		{
			m_Velocity = math::Vector2f();
			m_IsRemoved = true;
		}
	};

} }