#include "AudioLoader.hpp"
#include <iostream>

using namespace Audio;

std::unique_ptr<Mix_Music, void (*)(Mix_Music*)> AudioLoader::LoadMusic(std::string path)
{
	auto* music = Mix_LoadMUS(path.c_str());
	if (!music)
	{
		std::cerr << "Could not load music.\n";
	}
	return std::unique_ptr<Mix_Music, void (*)(Mix_Music*)>{music, Mix_FreeMusic};
}

std::unique_ptr<Mix_Chunk, void (*)(Mix_Chunk*)> AudioLoader::LoadChunk(std::string path)
{
	auto* chunk = Mix_LoadWAV(path.c_str());
	if (!chunk)
	{
		std::cerr << "Could not load music.\n";
	}
	return std::unique_ptr<Mix_Chunk, void (*)(Mix_Chunk*)>{chunk, Mix_FreeChunk};
}
