#define SDL_MAIN_HANDLED

#include <iostream>

#include "Application.hpp"

#include <SDL_ttf.h>
#include <SDL_mixer.h>

// https://dev.to/noah11012/using-sdl2-scaling-and-moving-an-image-pj

int main()
{
	// Init SDL2
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		std::cerr << "Failed to initialize the SDL2 library" << std::endl;
		return -1;
	}

	// Init SDL2_image
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
	{
		std::cerr << "Failed to initialize the SDL2_image library" << std::endl;
		return -1;
	}

	// Init SDL2_ttf
	if (TTF_Init() < 0)
	{
		std::cerr << "Failed to initialize the SDL2_ttf library" << std::endl;
		return -1;
	}

	Application application{};
	application.Run();

	SDL_Quit();
	TTF_Quit();
	IMG_Quit();
	Mix_Quit();

	return 0;
}