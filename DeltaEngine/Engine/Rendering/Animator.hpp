#pragma once

#include <vector>

#include "Sprite.hpp"

class Animator
{
public:
	Animator(const char* spritePath);
	~Animator();

	void Play();
	void Stop();

	// TODO
	/*int fps;*/

private:
	// TODO
	/*std::vector<Sprite*> sprites;*/

};
