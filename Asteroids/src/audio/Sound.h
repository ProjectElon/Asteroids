#pragma once

#include "../Log.h"

#include <SDL/SDL_mixer.h>

namespace astro { namespace audio {

	class Sound
	{
	private:
		Mix_Chunk *m_Chuck;

	public:
		Sound(const char *path);
		~Sound();

		void Play(const int &times = 0);

	};

} }