#pragma once

#include "Entity.h"

namespace astro { namespace entity {

	class Particel : public Entity
	{
	private:
		float m_Angle;
		float m_MaxSpeed = 2.5f;
		
	public:
		Particel(graphics::Texture *tex, const math::Vector2f &pos, const float &angle, const int &width, const int &height, const int& count, const int &time);
		~Particel();

		void OnInput(const SDL_Event &event) override;
		void OnUpdate() override;
		void OnRender(graphics::Renderer2D *renderer) override;

		static Uint32 OnRemoveCallback(Uint32 interval, void*param);
	};

} }