#include "Engine.h"

Engine::Engine(RendererConfig& rendererConfig, float targetFps) {
	bool res = m_renderer.Init(rendererConfig);

	if (!res) {
		m_running = false;
		return;
	}

	m_simulation.Init(m_renderer.GetGridWidth(), m_renderer.GetGridHeight());

	if (targetFps <= 0.0f) {
		std::cout << "targetFps must be > 0, defaulting to 60" << std::endl;
		targetFps = 60.0f;
	}

	m_targetFps = targetFps;
	m_fixedDT = 1.0f / targetFps;
}

void Engine::Run() {
	Uint64 freq = SDL_GetPerformanceFrequency();
	Uint64 frameStart;

	while (m_running) {
		frameStart = SDL_GetPerformanceCounter();

		ProcessInput();
		Update(m_fixedDT);
		Render();

		Uint64 frameEnd = SDL_GetPerformanceCounter();
		float elapsed = (float)(frameEnd - frameStart) / freq;
		float remaining = m_fixedDT - elapsed;

		if (remaining > 0.0f) {
			SDL_Delay((Uint32)(remaining * 1000.0f));
		}
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
