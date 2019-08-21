#include "Game.h"

namespace astro
{
	int Game::s_ScreenWidth;
	int Game::s_ScreenHeight;
	
	Uint32 onHitCallback(Uint32 interval, void *param)
	{
		entity::Ship* ship = static_cast< entity::Ship* >(param);
		ship->SetIsHit(false);
		return 0;
	}

	Uint32 onResetCallback(Uint32 interval, void *param)
	{
		Game *game = (Game*)param;
		
		while (true)
		{
			// return -> space key 
			if (input::Keyboard::IsKeyDown(SDL_SCANCODE_RETURN))
			{
				game->SetPaused(false);
				break;
			}
		}

		return 0;
	}

	void Game::Init()
	{
		using namespace graphics;
		using namespace entity;
		using namespace input;

		srand(time(nullptr));

		Keyboard::Init();
		Mouse::Init();

		m_Running = true;
		m_Paused = false;

		m_Window      = new Window("Astro", 800, 600);

		s_ScreenWidth  = m_Window->GetWidth();
		s_ScreenHeight = m_Window->GetHeight();

		m_Renderer    = new Renderer2D(m_Window->GetHandle(), SDL_RENDERER_PRESENTVSYNC);
		m_Font	      = new StaticFont(m_Renderer->GetContext(), "res/Menlo.ttf", 50, "Game Over", {255, 255, 255, 255});
		m_DynamicFont = new DynamicFont(m_Renderer->GetContext(), "res/Menlo.ttf", 24);

		m_Background    = new Texture(m_Renderer->GetContext(), "res/background.jpg");
		m_SpaceShip     = new Texture(m_Renderer->GetContext(), "res/spaceship.png");
		m_Asteroid      = new Texture(m_Renderer->GetContext(), "res/rock.png");
		m_Bullet        = new Texture(m_Renderer->GetContext(), "res/fire_blue.png");
		m_SmallAsteroid = new Texture(m_Renderer->GetContext(), "res/rock_small.png");
		m_Alienship     = new Texture(m_Renderer->GetContext(), "res/alienShip.png");
		m_Alienbullet   = new Texture(m_Renderer->GetContext(), "res/fire_red.png");

		m_Manager = new EntityManager();
		m_Ship = new Ship(m_SpaceShip, math::Vector2f());
		m_Ship->SetPosition(math::Vector2f((m_Window->GetWidth() - m_Ship->GetWidth()) / 2.0f, (m_Window->GetHeight() - m_Ship->GetHeight()) / 2.0f));

		m_Manager->Submit(m_Ship);
		
		for (int i = 0; i < m_AsteroidsCount; ++i) 
		{
			m_Manager->Submit((Entity*)new Asteroid(m_Asteroid, m_Ship->GetPosition()));
		}
	}

	void Game::OnInput(const SDL_Event& event)
	{
		m_Manager->OnInput(event);

		if (m_Ship->IsShooting())
		{
			entity::Bullet* bullet = new entity::Bullet(m_Bullet, m_Ship->GetPosition(), m_Ship->GetAngle());
			m_Manager->Submit((entity::Entity*)bullet);
		}
	}

	void Game::OnUpdate()
	{
		using namespace entity;

		++m_Timer;

		if (m_Ship->GetNumOfLifes() <= 0)
		{
			OnReset();
		}

		entity::Entity* alienShipEntity = nullptr;
		
		for (size_t i = 0; i < m_Manager->GetCount(); ++i)
		{
			for (size_t j = 0; j < m_Manager->GetCount(); ++j)
			{
				if (i == j)
				{
					continue;
				}

				entity::Entity *currentEntity = m_Manager->GetEntityAtIndex(i),
							   *otherEntity   = m_Manager->GetEntityAtIndex(j);

				if (currentEntity->GetType() == EntityType::AlienShip)
				{
					alienShipEntity = currentEntity;
				}
				else if (otherEntity->GetType() == EntityType::AlienShip)
				{
					alienShipEntity = otherEntity;
				}

				if (!currentEntity->IsRemoved() && !otherEntity->IsRemoved() && currentEntity->IsHitWith(otherEntity))
				{
					if (currentEntity->GetType() == EntityType::SpaceShipBullet && otherEntity->GetType() == EntityType::Asteroid)
					{ 
						math::Vector2f posititon(otherEntity->GetPosition()); 
						math::Vector2f velocity(otherEntity->GetVelocity());
						
						int width  = otherEntity->GetWidth();
						int height = otherEntity->GetHeight();

						currentEntity->OnRemove();
						otherEntity->OnRemove();

						--m_AsteroidsCount;

						m_Score += 100;

						if (width > 30)
						{
							for (int k = 0; k < 2; ++k)
							{
								float angle = rand() % 360;
								Entity *entity = (Entity*)new Asteroid(m_SmallAsteroid, m_Ship->GetPosition(), &posititon, &angle);
								entity->SetWidth(width - 15);
								entity->SetHeight(height - 15);
								m_Manager->Submit(entity);
							}
						}

						for (int angle = 0; angle <= 360; angle += 72)
						{
							Entity* entity = new Particel(m_SmallAsteroid, posititon, angle, width, height, 360.0f / 72.f, 500);
							m_Manager->Submit(entity);
						}

					}
					else if (currentEntity->GetType() == EntityType::Ship  && otherEntity->GetType() == EntityType::Asteroid        ||
							 currentEntity->GetType() == EntityType::Ship  && otherEntity->GetType() == EntityType::AlienShipBullet ||
							 currentEntity->GetType() == EntityType::Ship  && otherEntity->GetType() == EntityType::AlienShip)
					{
						if (!m_Ship->IsHit()) 
						{
							m_Ship->SetNumOfLifes(m_Ship->GetNumOfLifes() - 1);
							m_Ship->SetIsHit(true);
							SDL_AddTimer(1000, onHitCallback, m_Ship);
						}
					}
					else if (currentEntity->GetType() == EntityType::AlienShipBullet && otherEntity->GetType() == EntityType::SpaceShipBullet)
					{
						currentEntity->OnRemove();
						otherEntity->OnRemove();
					}
					else if (currentEntity->GetType() == EntityType::AlienShip && otherEntity->GetType() == EntityType::SpaceShipBullet)
					{
						currentEntity->OnRemove();
						otherEntity->OnRemove();
						
						if (m_Ship->GetNumOfLifes() < 4)
						{
							m_Ship->SetNumOfLifes(m_Ship->GetNumOfLifes() + 1);
						}
					}

				}
			}
		}

		if (alienShipEntity != nullptr && m_Timer % 30 == 0)
		{
			m_Manager->Submit((Entity*)new AlienBullet(m_Alienbullet, alienShipEntity->GetPosition(), m_Ship->GetPosition()));
			m_Timer = 1;
		}

		for (size_t i = 0; i < m_Manager->GetCount(); ++i)
		{
			Entity *entity = m_Manager->GetEntityAtIndex(i);

			if (entity->IsRemoved())
			{
				m_Manager->RemoveEntityAtIndex(i);
				delete entity;
			}
		}

		if (m_Manager->GetCount() == 1)
		{
			m_AsteroidsCount = ++m_MaxAsteroidsCount;

			for (int i = 0; i < m_AsteroidsCount; ++i) 
			{
				m_Manager->Submit((Entity*)new Asteroid(m_Asteroid, m_Ship->GetPosition()));
			}

			m_Manager->Submit((Entity*)new AlienShip(m_Alienship, m_Ship->GetPosition()));
		}

		m_Manager->OnUpdate();
	}
	
	void Game::OnRender()
	{
		SDL_Rect rect = { 0, 0, m_Window->GetWidth(), m_Window->GetHeight() };
		m_Renderer->RenderTexture(m_Background, nullptr, &rect);
		
		std::string text = "Score: " + std::to_string(m_Score);
		m_DynamicFont->Post(text, { 255, 255, 255, 255 });
		m_DynamicFont->Render(10, 0);
		
		text = "Lifes: " + std::to_string(m_Ship->GetNumOfLifes());
		m_DynamicFont->Post(text, { 255, 255, 255, 255 });
		m_DynamicFont->Render(m_Window->GetWidth() - m_DynamicFont->GetWidth() - 10, 0);

		m_Manager->OnRender(m_Renderer);
	}

	void Game::OnReset()
	{
		using namespace entity;

		m_Paused = true;

		for (size_t i = 1; i < m_Manager->GetCount(); ++i)
		{
			Entity* entity	= m_Manager->GetEntityAtIndex(i);
			entity->OnRemove();
			m_Manager->RemoveEntityAtIndex(i);
			delete entity;
		}

		m_Manager->Clear();
		
		m_Ship->SetPosition(math::Vector2f((m_Window->GetWidth() - m_Ship->GetWidth()) / 2.0f, (m_Window->GetHeight() - m_Ship->GetHeight()) / 2.0f));
		m_Ship->SetNumOfLifes(4);

		m_AsteroidsCount = m_MaxAsteroidsCount = 5;
		m_TempScore = m_Score;
		m_Score = 0;
		m_Timer = 0;
		
		m_Manager->Submit(m_Ship);
		
		for (int i = 0; i < m_AsteroidsCount; ++i)
		{
			m_Manager->Submit((Entity*)new Asteroid(m_Asteroid, m_Ship->GetPosition()));
		}

		SDL_AddTimer(100, onResetCallback, this);
	}

	void Game::Run()
	{
		while (m_Running)
		{
			while (SDL_PollEvent(&m_Window->GetEvent()))
			{
				switch (m_Window->GetEvent().type)
				{
					case SDL_QUIT:
					{
						m_Running = false;
					}
					break;
				}

				input::Mouse::Register(&m_Window->GetEvent());
				OnInput(m_Window->GetEvent());
			}
			
			m_Renderer->Clear();
			
			if (!m_Paused) 
			{
				OnUpdate();
				OnRender();
			}
			else
			{
				m_Font->Render((m_Window->GetWidth() - m_Font->GetWidth()) / 2, (m_Window->GetHeight() - m_Font->GetHeight()) / 2);

				std::string text = "Your Score was " + std::to_string(m_TempScore);
				m_DynamicFont->Post(text, { 255, 255, 255, 255 });
				m_DynamicFont->Render((m_Window->GetWidth()- m_DynamicFont->GetWidth()) / 2, 150);
				
				text = "Press [ENTER] to try again ....";
				m_DynamicFont->Post(text, { 255, 255, 255, 255 });
				m_DynamicFont->Render((m_Window->GetWidth() - m_DynamicFont->GetWidth()) / 2, m_Window->GetHeight()-m_DynamicFont->GetHeight()-100);
			}

			m_Renderer->SetColor(0, 0, 0, 0);
			m_Renderer->SwapBuffers();
		}
	}

	void Game::Free()
	{
		delete m_Font;
		delete m_DynamicFont;
		delete m_Background;
		delete m_SpaceShip;
		delete m_Bullet;
		delete m_Asteroid;
		delete m_SmallAsteroid;
		delete m_Alienship;
		delete m_Alienbullet;
		delete m_Manager;
		delete m_Window;
		delete m_Renderer;
	}
}