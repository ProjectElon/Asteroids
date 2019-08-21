#pragma once

#include "../Log.h"

#include <SDL/SDL_mixer.h>

namespace astro { namespace audio {

	class Music
	{
	private:
		Mix_Music *m_Music;

	public:
		Music(const char* path);
		~Music();

		void play();
		
		static bool IsPlaying();
		static bool IsPaused();

		static void Pause();
		static void Resume();
		static void Stop();
	};

} }