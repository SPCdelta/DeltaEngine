#pragma once

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_image.h>

#include <string>

namespace Rendering
{
	constexpr int SUCCESS = 0;
	constexpr int COLOR_ALPHA_VAL = 255;

	// Constants for SDL flags and event types
	constexpr auto WINDOW_FULLSCREEN = SDL_WINDOW_FULLSCREEN;
	constexpr auto WINDOWPOS_CENTERED = SDL_WINDOWPOS_CENTERED;
	constexpr auto INIT_EVERYTHING = SDL_INIT_EVERYTHING;
	constexpr auto KEYDOWN = SDL_KEYDOWN;
	constexpr auto KEYUP = SDL_KEYUP;
	constexpr auto MOUSEBUTTONDOWN = SDL_MOUSEBUTTONDOWN; 
	constexpr auto BUTTON_LEFT = SDL_BUTTON_LEFT; 
	constexpr auto QUIT = SDL_QUIT;
	constexpr auto RENDERER_ACCELERATED = SDL_RENDERER_ACCELERATED;
	constexpr auto RENDERER_PRESENTVSYNC = SDL_RENDERER_PRESENTVSYNC;
	constexpr auto INIT_VIDEO = SDL_INIT_VIDEO;
	constexpr auto INIT_AUDIO = SDL_INIT_AUDIO;
	constexpr auto INIT_PNG = IMG_INIT_PNG;

	using Window = SDL_Window;
	using Renderer = SDL_Renderer;
	using Texture = SDL_Texture;
	using Rect = SDL_Rect;
	using Event = SDL_Event;
	using Color = SDL_Color;
	using UnsignInt = Uint32;
	
	namespace Facade 
	{
		// Initialize SDL
		inline bool Initialize(Uint32 flags = SDL_INIT_EVERYTHING)
		{
			return SDL_Init(flags) == SUCCESS;
		}

		// Initialize SDL image
		inline bool Initialize_image(int flags)
		{
			return IMG_Init(flags) == SUCCESS; 
		}

		// Create window
		inline Window* CreateWindow(const char* title, int x, int y, int w, int h, Uint32 flags)
		{
			return SDL_CreateWindow(title, x, y, w, h, flags);
		}

		// Create renderer
		inline Renderer* CreateRenderer(SDL_Window* window, int index, Uint32 flags)
		{
			return SDL_CreateRenderer(window, index, flags);
		}

		// Get title of window
		inline const char* GetWindowTitle(SDL_Window* window)
		{
			return SDL_GetWindowTitle(window);
		}

		// Set title of window
		inline void SetWindowTitle(SDL_Window* window, const char* title)
		{
			SDL_SetWindowTitle(window, title);
		}

		// Get window size
		inline void GetWindowSize(SDL_Window* window, int* w, int* h)
		{
			return SDL_GetWindowSize(window, w, h);
		}

		// Destroy window
		inline void DestroyWindow(SDL_Window* window)
		{
			SDL_DestroyWindow(window);
		}

		// Destroy renderer
		inline void DestroyRenderer(SDL_Renderer* renderer)
		{
			SDL_DestroyRenderer(renderer);
		}

		// Set render draw color
		inline void SetRenderDrawColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a = COLOR_ALPHA_VAL) 
		{
			SDL_SetRenderDrawColor(renderer, r, g, b, a);
		}

		// Clear renderer
		inline void RenderClear(SDL_Renderer* renderer)
		{
			SDL_RenderClear(renderer);
		}

		// Present the renderer
		inline void RenderPresent(SDL_Renderer* renderer)
		{
			SDL_RenderPresent(renderer);
		}

		// Load a image texture from file
		inline Texture* LoadTexture(SDL_Renderer* renderer, const std::string& filePath)
		{
			return IMG_LoadTexture(renderer, filePath.c_str());
		}

		// Destroy a texture
		inline void DestroyTexture(Texture* texture)
		{
			SDL_DestroyTexture(texture);
		}

		// Poll events
		inline bool PollEvent(Event& event)
		{
			return SDL_PollEvent(&event) != SUCCESS;
		}

		// Get SDL ticks 
		inline UnsignInt GetTicks()
		{
			return SDL_GetTicks();
		}

		// Get the last SDL error message
		inline std::string GetError()
		{
			return SDL_GetError();
		}

		// Delay
		inline void Delay(Uint32 ms)
		{
			SDL_Delay(ms);
		}

		// Quit SDL
		inline void Quit()
		{
			SDL_Quit();
		}

		// Quit SDL image 
		inline void Quit_Image()
		{
			IMG_Quit();
		}
	}
}