#pragma once

#include "Entity.h"

#include <climits>

namespace astro { namespace entity {

	enum Dirs 
	{
		TOP, DOWN, LEFT, RIGHT, TOTAL
	};

	class AlienShip : public Entity 
	{
	private:
		math::Vector2f m_ShipPosition;
		int m_SpawnDirection;
		int m_XRange[TOTAL];
		int m_YRange[TOTAL];
		
	public:
		AlienShip(graphics::Texture *texture, const math::Vector2f &shipPos);
		~AlienShip();

		void OnInput(const SDL_Event &event) override;
		void OnUpdate() override;
		void OnRender(graphics::Renderer2D *renderer) override;
	};

} }