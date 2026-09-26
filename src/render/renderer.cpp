#include "Renderer.h"

bool Renderer::Init(RendererConfig& rendererConfig) {

	m_gridWidth = rendererConfig.width / rendererConfig.cellSize;
	m_gridHeight = rendererConfig.height / rendererConfig.cellSize;

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		std::cout << "SDL_Init failed!" << SDL_GetError() << std::endl;
		return false;
	}

	m_window = SDL_CreateWindow(rendererConfig.name, rendererConfig.width, rendererConfig.height, 0);

	if (!m_window) {
		std::cout << "SDL_CreateWindow failed!" << SDL_GetError() << std::endl;
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, nullptr);

	if (!m_renderer) {
		std::cout << "SDL_CreateRenderer failed!" << SDL_GetError() << std::endl;
		return false;
	}

	if (!CreateTexture()) {
		std::cout << "CreateTexture failed!" << std::endl;
		return false;
	}

	return true;
}

bool Renderer::CreateTexture() {
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, m_gridWidth, m_gridHeight);

	if (!m_texture) {
		std::cout << "SDL_CreateTexture failed: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_SetTextureScaleMode(m_texture, SDL_SCALEMODE_NEAREST);

	return true;
}

void Renderer::UpdateRendererGrid(const std::vector<uint32_t>& rendererGrid) {
	m_rendererGrid = rendererGrid;
}

void Renderer::Render() {
	SDL_UpdateTexture(m_texture, nullptr, m_rendererGrid.data(), m_gridWidth * (int)sizeof(uint32_t));

	SDL_RenderClear(m_renderer);
	SDL_RenderTexture(m_renderer, m_texture, nullptr, nullptr);
	SDL_RenderPresent(m_renderer);
}

Renderer::~Renderer() {
	SDL_DestroyTexture(m_texture);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}
