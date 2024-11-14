#include "AudioLoader.hpp"

using namespace Audio;

std::unique_ptr<Mix_Music, void (*)(Mix_Music*)> AudioLoader::LoadMusic(std::string path)
{
	return std::unique_ptr<Mix_Music, void (*)(Mix_Music*)>{Mix_LoadMUS(path.c_str()), Mix_FreeMusic};
}

std::unique_ptr<Mix_Chunk, void (*)(Mix_Chunk*)> AudioLoader::LoadChunk(std::string path)
{
	return std::unique_ptr<Mix_Chunk, void (*)(Mix_Chunk*)>{Mix_LoadWAV(path.c_str()), Mix_FreeChunk};
}
