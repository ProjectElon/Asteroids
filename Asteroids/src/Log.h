#pragma once

#define DEBUG

#ifdef DEBUG
	
#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#define log(msg) std::cout << msg << std::endl;
#define SDL_LogError() std::cerr << "[SDL_Error] : " << SDL_GetError() << std::endl;
#define IMG_LogError() std::cerr << "[IMG_Error] : " << IMG_GetError() << std::endl;
#define TTF_LogError() std::cerr << "[TTF_Error] : " << TTF_GetError() << std::endl;
#define MIX_LogError() std::cerr << "[MIX_Error] : " << Mix_GetError() << std::endl;

#endif