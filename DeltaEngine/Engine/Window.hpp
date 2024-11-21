#pragma once

#include <iostream>

#include "Rendering/Rendering.hpp"
#include "Rendering/Viewport.hpp"

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

	void SetViewportSize(int width, int height);
	void SetViewportPos(int x, int y);
	ViewportData* GetViewport() const { return _viewportData; }
	void RenderViewport(Rendering::UnsignInt8 r, Rendering::UnsignInt8 g, Rendering::UnsignInt8 b, Rendering::UnsignInt8 a);

   private:
	Rendering::Window* _window;
	Rendering::Renderer* _renderer;

	ViewportData* _viewportData;

	bool _shouldWindowClose{false};
};