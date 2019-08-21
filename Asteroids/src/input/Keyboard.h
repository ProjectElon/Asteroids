#pragma once

#include <SDL/SDL.h>

namespace astro { namespace input {

	class Keyboard
	{
	private:
		static const Uint8* s_State;

	public:
		static void Init();

		static bool IsKeyDown(const Uint8& key);
		static bool IsKeyUp(const Uint8& key);
	};

} }