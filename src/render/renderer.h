#pragma once

#include "rendererConfig.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <vector>

class Renderer {
public:
	bool Init(RendererConfig& windowConfig);
	~Renderer();

	void UpdateRendererGrid(const std::vector<uint32_t>& rendererGrid);
	void Render();

	int GetGridWidth() const { return m_gridWidth; }
	int GetGridHeight() const { return m_gridHeight; }

private:
	SDL_Window* m_window = nullptr;
	SDL_Renderer* m_renderer = nullptr;
	SDL_Texture* m_texture = nullptr;

	int m_gridWidth = 0;
	int m_gridHeight = 0;

	std::vector<uint32_t> m_rendererGrid;

	bool CreateTexture();
};
