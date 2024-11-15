#include "Window.hpp"

Window::Window(const char* title, int width, int height)
{
	// Create Window
	_window = Rendering::CreateWindow(title, Rendering::WINDOWPOS_CENTERED, Rendering::WINDOWPOS_CENTERED, width, height, 0);
	if (!_window)
	{
		std::cerr << "Failed to create window" << std::endl;
	}

	// Create renderer
	_renderer = Rendering::CreateRenderer(_window, -1, Rendering::RENDERER_ACCELERATED | Rendering::RENDERER_PRESENTVSYNC);
	if (!_renderer)
	{
		std::cerr << "Failed to create renderer: " << Rendering::GetError() << std::endl;
	}

	// Set the initial viewport to match the window size
	if (!_viewportData)
	{
		_viewportData = new ViewportData();
	}

	_viewportData->width = width;
	_viewportData->height = height;
}

Window::~Window()
{
	Close();
}

void Window::Close()
{
	_shouldWindowClose = true;
	Rendering::DestroyWindow(_window);
	Rendering::DestroyRenderer(_renderer);
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
	Rendering::SetWindowTitle(_window, title);
}

const char* Window::GetTitle()
{
	return Rendering::GetWindowTitle(_window);
}

void Window::SetViewportSize(int width, int height)
{
	int windowWidth, windowHeight;
	Rendering::GetWindowSize(_window, &windowWidth, &windowHeight);

	if (width <= windowWidth && height <= windowHeight && width > 0 && height > 0)
	{
		_viewportData->width = width;
		_viewportData->height = height;
	}
	else
	{
		std::cerr << "Invalid viewport size" << std::endl;
	}	
}

void Window::SetViewportPos(int x, int y)
{
	int windowWidth, windowHeight;
	Rendering::GetWindowSize(_window, &windowWidth, &windowHeight);

	if (x + _viewportData->width <= windowWidth && y + _viewportData->height <= windowHeight && x >= 0 && y >= 0)
	{
		_viewportData->x = x;
		_viewportData->y = y;
	}
	else
	{
		std::cerr << "Invalid viewport position" << std::endl;
	}
}

void Window::RenderViewport(Rendering::UnsignInt8 r, Rendering::UnsignInt8 g,
							Rendering::UnsignInt8 b, Rendering::UnsignInt8 a)
{
	// Define viewport rectangle
	Rendering::Rect viewportRect = {_viewportData->x, _viewportData->y,
									_viewportData->width, _viewportData->height};

	// Set color and render the viewport
	Rendering::SetRenderDrawColor(_renderer, r, g, b, a); 
	Rendering::RenderFillRect(_renderer, &viewportRect);
}
