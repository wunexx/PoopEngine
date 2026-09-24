#include "engine.h"

Engine::Engine(RendererConfig& rendererConfig) {
	bool res = m_renderer.Init(rendererConfig);

	if (!res) {
		m_running = false;
		return;
	}

	m_simulation.Init(m_renderer.GetGridWidth(), m_renderer.GetGridHeight());
}

void Engine::Run() {
	Uint64 lastTime = SDL_GetPerformanceCounter();

	while (m_running) {
		Uint64 currentTime = SDL_GetPerformanceCounter();
		float dt = (float)(currentTime - lastTime) / SDL_GetPerformanceFrequency();
		lastTime = currentTime;

		ProcessInput();
		Update(dt);
		Render();
	}
}

void Engine::Update(float dt) {
	m_simulation.Update(dt);
	m_renderer.UpdateRendererGrid(m_simulation.GetColorGrid());

	std::cout << dt << std::endl;
}

void Engine::Render() {
	m_renderer.Render();
}

void Engine::ProcessInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT)
			m_running = false;
	}
}
