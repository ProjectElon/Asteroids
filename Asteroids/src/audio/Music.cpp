#include "Music.h"

namespace astro { namespace audio {

	Music::Music(const char* path)
	{
		m_Music = Mix_LoadMUS(path);
		
		if (m_Music == nullptr)
			MIX_LogError();
	}

	Music::~Music()
	{
		if (m_Music != nullptr)
		{
			Mix_FreeMusic(m_Music);
			m_Music = nullptr;
		}
	}

	void Music::play()
	{
		Mix_PlayMusic(m_Music, -1);
	}
	
	bool Music::IsPlaying()
	{
		return Mix_PlayingMusic();
	}

	bool Music::IsPaused()
	{
		return Mix_PausedMusic();
	}

	void Music::Pause() 
	{
		Mix_PauseMusic();
	}
	
	void Music::Resume()
	{
		Mix_ResumeMusic();
	}

	void Music::Stop()
	{
		Mix_HaltMusic();
	}

} }