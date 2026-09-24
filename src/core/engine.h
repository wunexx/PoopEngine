#pragma once 

#include "render/renderer.h"
#include "world/simulation.h"

#include <iostream>
#include <SDL3/SDL.h>

class Engine {
public:
	Engine(RendererConfig& rendererConfig);
	void Run();

private:
	Renderer m_renderer;
	Simulation m_simulation;

	bool m_running = true;

	void Update(float dt);
	void ProcessInput();
	void Render();
};
