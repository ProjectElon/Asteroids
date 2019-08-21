#pragma once

#include "graphics/Window.h"
#include "graphics/Renderer2D.h"
#include "graphics/StaticFont.h"
#include "graphics/DynamicFont.h"

#include "input/Keyboard.h"

#include "entity/EntityManager.h"
#include "entity/Ship.h"
#include "entity/Bullet.h"
#include "entity/Asteroid.h"
#include "entity/Particle.h"
#include "entity/AlienShip.h"
#include "entity/AlienBullet.h"

#include <time.h>

namespace astro
{
	class Game
	{
	private:
		// Graphics Context
		graphics::Window*      m_Window;
		graphics::Renderer2D*  m_Renderer;

		static int s_ScreenWidth;
		static int s_ScreenHeight;

		// Game Variables
		bool m_Running;
		bool m_Paused;

		int m_AsteroidsCount = 5;
		int m_MaxAsteroidsCount = 5;

		int m_Score = 0;
		int m_TempScore = 0;
		int m_Timer = 0;
		
		// Resources
		graphics::StaticFont  *m_Font;
		graphics::DynamicFont *m_DynamicFont;
		graphics::Texture     *m_Background,
						      *m_SpaceShip,
						      *m_Bullet,
						      *m_Asteroid,
						      *m_SmallAsteroid,
						      *m_Alienship,
						      *m_Alienbullet;

		// Entites
		entity::EntityManager *m_Manager;
		entity::Ship	      *m_Ship;

		void OnInput(const SDL_Event& event);
		void OnUpdate();
		void OnRender();
		void OnReset();
		
	public:
		Game() = default;
		~Game() {}

		void Init();
		void Run();
		void Free();

		inline const bool& IsPaused() const { return m_Paused; }
		inline void SetPaused(bool paused) { m_Paused = paused; }

		inline static int GetScreenWidth()  { return s_ScreenWidth; }
		inline static int GetScreenHeight() { return s_ScreenHeight; }
	};
}