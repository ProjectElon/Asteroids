#include "Keyboard.h"

namespace astro { namespace input {

	const Uint8* Keyboard::s_State;

	void Keyboard::Init()
	{
		s_State = SDL_GetKeyboardState(nullptr);
	}

	bool Keyboard::IsKeyDown(const Uint8& key)
	{
		return s_State[key];
	}

	bool Keyboard::IsKeyUp(const Uint8& key)
	{
		return !s_State[key];
	}

} }