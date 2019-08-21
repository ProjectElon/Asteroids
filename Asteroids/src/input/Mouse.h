#pragma once

#include <SDL/SDL.h>

#define MAX_BUTTONS 3

enum Buttons
{
	LEFT, 
	MIDDLE, 
	RIGHT,
	TOTAL_BUTTONS
};

namespace astro { namespace input {

	class Mouse
	{
	private:
		static bool s_ButtonStates[MAX_BUTTONS];
		static SDL_Event *s_Event;
		static int s_X;
		static int s_Y;

	public:
		static void Init();
		static void Register(SDL_Event *event);

		static bool IsButtonDown(const int& button);
		static bool IsButtonUp(const int& button);
		
		inline static int GetX() { return s_X; }
		inline static int GetY() { return s_Y; }
	};

} }