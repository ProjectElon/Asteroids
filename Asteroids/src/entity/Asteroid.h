#pragma once

#include "Entity.h"

namespace astro { namespace entity {

	class Asteroid : Entity
	{
	private:
		float m_SpwanRange = 50.0f;

	public:
		Asteroid(graphics::Texture *texure, const math::Vector2f &ShipPos, math::Vector2f* position = nullptr, float *angle = nullptr);
		~Asteroid();

		void OnInput(const SDL_Event &event) override;
		void OnUpdate() override;
		void OnRender(graphics::Renderer2D *renderer) override;
	};

} }