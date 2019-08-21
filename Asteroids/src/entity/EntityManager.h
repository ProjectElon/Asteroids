#pragma once

#include <vector>

#include "Entity.h"

namespace astro { namespace entity {

	class EntityManager
	{
	private:
		std::vector<Entity*> m_Entities;

	public:
		EntityManager();
		~EntityManager();

		void Submit(Entity* entity);
		void RemoveEntityAtIndex(const int& index);
		void Clear();

		void OnInput(const SDL_Event &event);
		void OnUpdate();
		void OnRender(graphics::Renderer2D *renderer);
		
		Entity* GetEntityAtIndex(const size_t& index) { return m_Entities[index]; }
		inline const size_t& GetCount() { return m_Entities.size(); }
	};

} }