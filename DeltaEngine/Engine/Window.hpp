#pragma once

#include <iostream>

#include <SDL.h>

class Window
{
public:
	Window(const char* title, int width, int height);
	~Window();

	void Close();
	bool ShouldWindowClose();
	void Update();

	void SetTitle(const char* title);
	const char* GetTitle();

	SDL_Renderer* GetRenderer()
	{
		return _renderer;
	}

	operator SDL_Window* () const
	{
		return _window;
	}

private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	bool _shouldWindowClose{ false };
};