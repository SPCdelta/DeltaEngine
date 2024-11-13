#pragma once

#include <iostream>

#include "Rendering/Rendering.hpp"

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

	Rendering::Renderer* GetRenderer() { return _renderer; }

	operator Rendering::Window*() const { return _window; }

private:
	Rendering::Window* _window;
	Rendering::Renderer* _renderer;

	bool _shouldWindowClose{ false };
};