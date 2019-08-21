#pragma once

#include "Entity.h"

namespace astro { namespace entity {

	class Bullet : Entity
	{
	private:
		float m_Angle;

	public:
		Bullet(graphics::Texture *texture, const math::Vector2f& position, const float& angle);
		~Bullet();

		void OnInput(const SDL_Event &event) override;
		void OnUpdate() override;
		void OnRender(graphics::Renderer2D *renderer) override;
	};

} }