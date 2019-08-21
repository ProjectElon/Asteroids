#pragma once

#include "Entity.h"
#include "../input/Keyboard.h"

namespace astro { namespace entity {

	class Ship : public Entity
	{
	private:
		SDL_Rect m_Clip { 40, 0, 40, 40 };
		SDL_Rect m_Dims;
		bool	 m_IsBoosting, m_IsShooting, m_IsHit;
		float	 m_Angle;
		int		 m_Lifes;
		Uint8	 m_Alpha;

		float m_MaxSpeed = 16;
		float m_AngularSpeed = 16;

	public:
		Ship(graphics::Texture *texture, const math::Vector2f &position);
		~Ship();

		void OnInput(const SDL_Event &event) override;
		void OnUpdate() override;
		void OnRender(graphics::Renderer2D *renderer) override;

		inline const float GetAngle()      const { return m_Angle;      }
		inline const bool  IsShooting()    const { return m_IsShooting; }
		inline const int&  GetNumOfLifes() const { return m_Lifes;      }
		inline const bool& IsHit()	       const { return m_IsHit;      }

		inline void SetAngle(float angle) { m_Angle = angle; }
		inline void SetIsHit(bool isHit)  { m_IsHit = isHit; }
		inline void SetNumOfLifes(int numOfLifes) { m_Lifes = numOfLifes; }

	};

} }