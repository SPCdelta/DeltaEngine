#pragma once

#include <SDL_mixer.h>
#include <string>
#include <memory>
#include "../MemLeakDetection/MemLeakDetection.hpp"

namespace Audio
{
	// Supported formats: FLAC, MP3, Ogg, VOC and WAV.
	class AudioLoader
	{
	public:
		static std::unique_ptr<Mix_Music, void (*)(Mix_Music*)> LoadMusic(std::string path);
		static std::unique_ptr<Mix_Chunk, void (*)(Mix_Chunk*)> LoadChunk(std::string path);
	};
}

