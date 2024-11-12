#include "Window.hpp"

Window::Window(const char* title, int width, int height)
{
	// Create Window
	_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if (!_window)
	{
		std::cerr << "Failed to create window" << std::endl;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!_renderer)
	{
		std::cerr << "Failed to create SDL_renderer: " << SDL_GetError() << std::endl;
	}
}

Window::~Window()
{
	Close();
}

void Window::Close()
{
	_shouldWindowClose = true;
	SDL_DestroyWindow(_window);
}

bool Window::ShouldWindowClose()
{
	return _shouldWindowClose;
}

void Window::Update()
{

}

void Window::SetTitle(const char* title)
{
	SDL_SetWindowTitle(_window, title);
}

const char* Window::GetTitle() const
{
	return SDL_GetWindowTitle(_window);
}
