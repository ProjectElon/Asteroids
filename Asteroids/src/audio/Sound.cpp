#include "Sound.h"

namespace astro { namespace audio {
	
	Sound::Sound(const char *path)
	{
		m_Chuck = Mix_LoadWAV(path);

		if (m_Chuck == nullptr)
			MIX_LogError();
	}
	
	Sound::~Sound()
	{
		if (m_Chuck != nullptr) 
		{
			Mix_FreeChunk(m_Chuck);
			m_Chuck = nullptr;
		}
	}

	void Sound::Play(const int &times)
	{
		Mix_PlayChannel(-1, m_Chuck, times);
	}

} }