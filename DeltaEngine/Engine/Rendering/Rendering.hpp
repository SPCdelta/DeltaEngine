#pragma once

#define SDL_MAIN_HANDLED

#include <SDL.h>
#include <SDL_image.h>

#include <string>

namespace Rendering
{
	constexpr int COLOR_ALPHA_VAL = 255;

	// Window constants
	constexpr auto WINDOW_FULLSCREEN = SDL_WINDOW_FULLSCREEN;
	constexpr auto WINDOWPOS_CENTERED = SDL_WINDOWPOS_CENTERED;
	constexpr auto WINDOWPOS_UNDEFINED = SDL_WINDOWPOS_UNDEFINED;
	constexpr auto WINDOW_RESIZABLE = SDL_WINDOW_RESIZABLE;
	constexpr auto WINDOW_MAXIMIZED = SDL_WINDOW_MAXIMIZED;

	// Init/Quit constants
	constexpr auto INIT_EVERYTHING = SDL_INIT_EVERYTHING;
	constexpr auto INIT_VIDEO = SDL_INIT_VIDEO;
	constexpr auto INIT_AUDIO = SDL_INIT_AUDIO;
	constexpr auto INIT_PNG = IMG_INIT_PNG;
	constexpr auto QUIT = SDL_QUIT;

	// Render constants
	constexpr auto RENDERER_ACCELERATED = SDL_RENDERER_ACCELERATED;
	constexpr auto RENDERER_PRESENTVSYNC = SDL_RENDERER_PRESENTVSYNC;

	// Mouse/Key event constants
	constexpr auto KEYDOWN = SDL_KEYDOWN;
	constexpr auto KEYUP = SDL_KEYUP;
	constexpr auto MOUSEBUTTONDOWN = SDL_MOUSEBUTTONDOWN;
	constexpr auto MOUSEBUTTONUP = SDL_MOUSEBUTTONUP;
	constexpr auto MOUSEMOTION = SDL_MOUSEMOTION;
	constexpr auto BUTTON_LEFT = SDL_BUTTON_LEFT;
	constexpr auto BUTTON_RIGHT = SDL_BUTTON_RIGHT;
	constexpr auto SCANCODE_W = SDL_SCANCODE_W;
	constexpr auto SCANCODE_A = SDL_SCANCODE_A;
	constexpr auto SCANCODE_S = SDL_SCANCODE_S;
	constexpr auto SCANCODE_D = SDL_SCANCODE_D;
	constexpr auto KEYCODE_LEFT = SDLK_LEFT;
	constexpr auto KEYCODE_RIGHT = SDLK_RIGHT;
	constexpr auto SCANCODE_LEFT = SDL_SCANCODE_LEFT;
	constexpr auto SCANCODE_RIGHT = SDL_SCANCODE_RIGHT;
	constexpr auto SCANCODE_UP = SDL_SCANCODE_UP;
	constexpr auto SCANCODE_DOWN = SDL_SCANCODE_DOWN;
	constexpr auto SCANCODE_SPACE = SDL_SCANCODE_SPACE;

	// Flip/Rotation constants
	constexpr auto FLIP_HORIZONTAL = SDL_FLIP_HORIZONTAL;
	constexpr auto FLIP_VERTICAL = SDL_FLIP_VERTICAL;
	constexpr auto FLIP_NONE = SDL_FLIP_NONE;

	using Window = SDL_Window;
	using Renderer = SDL_Renderer;
	using Texture = SDL_Texture;
	using Rect = SDL_Rect;
	using Event = SDL_Event;
	using Color = SDL_Color;
	using UnsignInt32 = Uint32;
	using UnsignInt8 = Uint8;
	using Surface = SDL_Surface;
	using RendererFlip = SDL_RendererFlip;
	using Point = SDL_Point;

	namespace Facade
	{
		// Initialize SDL
		inline int Initialize(Uint32 flags = SDL_INIT_EVERYTHING)
		{
			return SDL_Init(flags);
		}

		// Initialize SDL image
		inline int InitializeImage(int flags)
		{
			return IMG_Init(flags);
		}

		// Create window
		inline Window* CreateWindow(const char* title, int x, int y, int w, int h,
									Uint32 flags)
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
		inline int SetRenderDrawColor(SDL_Renderer* renderer, Uint8 r, Uint8 g, Uint8 b,
									  Uint8 a = COLOR_ALPHA_VAL)
		{
			return SDL_SetRenderDrawColor(renderer, r, g, b, a);
		}

		// Fill rect with draw color
		inline int RenderFillRect(SDL_Renderer* renderer, const SDL_Rect* rect)
		{
			return SDL_RenderFillRect(renderer, rect);
		}

		// Clear renderer
		inline int RenderClear(SDL_Renderer* renderer)
		{
			return SDL_RenderClear(renderer);
		}

		// Present the renderer
		inline void RenderPresent(SDL_Renderer* renderer)
		{
			SDL_RenderPresent(renderer);
		}

		// Copy a portion of the current rendering
		inline int RenderCopy(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* src, const SDL_Rect* dest)
		{
			return SDL_RenderCopy(renderer, texture, src, dest);
		}

		// Copy a portion of the current rendering, with optional rotation and flipping
		inline int RenderCopyEx(SDL_Renderer* renderer, SDL_Texture* texture, const SDL_Rect* src, const SDL_Rect* dest,
			const double angle, const SDL_Point* center, const SDL_RendererFlip flip)
		{
			return SDL_RenderCopyEx(renderer, texture, src, dest, angle, center, flip);
		}

		// Load a image texture from file
		inline Texture* LoadTexture(SDL_Renderer* renderer, const std::string& filePath)
		{
			return IMG_LoadTexture(renderer, filePath.c_str());
		}

		// Create a texture from a surface
		inline Texture* CreateTextureFromSurface(SDL_Renderer* renderer, SDL_Surface* surface)
		{
			return SDL_CreateTextureFromSurface(renderer, surface);
		}

		// Query the attributes of a texture
		inline int QueryTexture(SDL_Texture* texture, Uint32* format, int* access, int* w, int* h)
		{
			return SDL_QueryTexture(texture, format, access, w, h);
		}

		// Destroy a texture
		inline void DestroyTexture(Texture* texture)
		{
			SDL_DestroyTexture(texture);
		}

		// Free a surface
		inline void FreeSurface(SDL_Surface* surface)
		{
			SDL_FreeSurface(surface);
		}

		// Poll events
		inline int PollEvent(Event& event)
		{
			return SDL_PollEvent(&event);
		}

		// Get current mouse state
		inline UnsignInt32 GetMouseState(int* x, int* y)
		{
			return SDL_GetMouseState(x, y);
		}

		// Get current keyboard state
		inline const UnsignInt8* GetKeyboardState(int* numkeys)
		{
			return SDL_GetKeyboardState(numkeys);
		}

		// Get SDL ticks
		inline UnsignInt32 GetTicks()
		{
			return SDL_GetTicks();
		}

		// Get the last SDL error message
		inline const char* GetError()
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
		inline void QuitImage()
		{
			IMG_Quit();
		}
	}  // namespace Facade
}  // namespace Rendering