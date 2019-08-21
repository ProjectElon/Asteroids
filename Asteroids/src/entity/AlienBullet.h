#pragma once

#include "Entity.h"

namespace astro { namespace entity {

	class AlienBullet : Entity
	{
	public:
		AlienBullet(graphics::Texture *texture, const math::Vector2f &position, const math::Vector2f &direction);
		~AlienBullet();

		void OnInput(const SDL_Event &event) override;
		void OnUpdate() override;
		void OnRender(graphics::Renderer2D *renderer) override;
	};

} }