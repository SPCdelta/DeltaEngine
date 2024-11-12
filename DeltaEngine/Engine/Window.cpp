#include "Window.hpp"

Window::Window(const char* title, int width, int height)
{
	// Create Window
	_window = Rendering::Facade::CreateWindow(title, Rendering::WINDOWPOS_CENTERED, Rendering::WINDOWPOS_CENTERED, width, height, 0); 
	if (!_window)
	{
		std::cerr << "Failed to create window" << std::endl;
	}

	// Create renderer
	_renderer = Rendering::Facade::CreateRenderer(_window, -1, Rendering::RENDERER_ACCELERATED | Rendering::RENDERER_PRESENTVSYNC); 
	if (!_renderer)
	{
		std::cerr << "Failed to create renderer: " << Rendering::Facade::GetError() << std::endl;
	}
}

Window::~Window()
{
	Close();
}

void Window::Close()
{
	_shouldWindowClose = true;
	Rendering::Facade::DestroyWindow(_window);
	Rendering::Facade::DestroyRenderer(_renderer);
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
	Rendering::Facade::SetWindowTitle(_window, title);
}

const char* Window::GetTitle()
{
	return Rendering::Facade::GetWindowTitle(_window);
}
