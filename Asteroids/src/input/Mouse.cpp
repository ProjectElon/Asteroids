#include "Mouse.h"

namespace astro { namespace input {

	bool Mouse::s_ButtonStates[];
	SDL_Event* Mouse::s_Event;
	int Mouse::s_X, Mouse::s_Y;

	void Mouse::Init()
	{
		for (int i = 0; i < TOTAL_BUTTONS; ++i)
		{
			s_ButtonStates[i] = false;
		}

		s_Event = nullptr;
		
		s_X = s_Y = 0;
	}

	void Mouse::Register(SDL_Event *event)
	{
		if (event->type == SDL_MOUSEBUTTONDOWN)
		{
			switch (event->button.button)
			{
				case SDL_BUTTON_LEFT:
				{
					s_ButtonStates[LEFT] = true;
				}
				break;

				case SDL_BUTTON_MIDDLE:
				{
					s_ButtonStates[MIDDLE] = true;
				}
				break;

				case SDL_BUTTON_RIGHT:
				{
					s_ButtonStates[RIGHT] = true;
				}
				break;
			}
		}
		else if (event->type == SDL_MOUSEBUTTONUP)
		{
				switch (event->button.button)
				{
				case SDL_BUTTON_LEFT:
				{
					s_ButtonStates[LEFT] = false;
				}
				break;

				case SDL_BUTTON_MIDDLE:
				{
					s_ButtonStates[MIDDLE] = false;
				}
				break;

				case SDL_BUTTON_RIGHT:
				{
					s_ButtonStates[RIGHT] = false;
				}
				break;
			}
		}
		else if (event->type == SDL_MOUSEMOTION)
		{
			SDL_GetMouseState(&s_X, &s_Y);
		}
	}
	
	bool Mouse::IsButtonDown(const int& button)
	{
		return s_ButtonStates[button];
	}

	bool Mouse::IsButtonUp(const int& button)
	{
		return !s_ButtonStates[button];
	}
	
} }