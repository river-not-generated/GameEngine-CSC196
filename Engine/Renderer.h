#pragma once

#include "SDL3/SDL.h"

namespace nu
{
	class Renderer {
	public:
		bool Initialize(const char* name, int width, int height, bool fullscreen = false);

		void Clear();
		void Present();

		void SetColour(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
		void SetColour(SDL_Color colour);

		void DrawPoint(float x, float y);
		void DrawFillRect(float x, float y, float width, float height);
		void DrawFillRect(const SDL_FRect* rect);
		void DrawRect(float x, float y, float width, float height);
		void DrawRect(const SDL_FRect* rect);
		void DrawLine(float x1, float y1, float x2, float y2);

		void DrawDebugText(float x, float y, const char* text);

		void Shutdown();

	private:
		SDL_Window* m_window = nullptr;
		SDL_Renderer* m_renderer = nullptr;
	};
};