#pragma once 

#include "render/Renderer.h"
#include "world/Simulation.h"

#include <iostream>
#include <SDL3/SDL.h>

class Engine {
public:
	Engine(RendererConfig& rendererConfig, float targetFps);
	void Run();

private:
	float m_targetFps = 60.0f;
	float m_fixedDT = 1.0f / 60.0f;

	Renderer m_renderer;
	Simulation m_simulation;

	bool m_running = true;

	void Update(float dt);
	void ProcessInput();
	void Render();
};
