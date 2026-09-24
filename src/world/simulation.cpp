#include "simulation.h"

void Simulation::Init(int width, int height) {
	m_width = width;
	m_height = height;

	m_colorGrid.assign((size_t)m_width * m_height, 0x000000FF);

	int squareSize = 20;
	int startX = (m_width - squareSize) / 2;
	int startY = (m_height - squareSize) / 2;

	for (int y = 0; y < squareSize; y++) {
		for (int x = 0; x < squareSize; x++) {
			int gridX = startX + x;
			int gridY = startY + y;

			if (gridX < 0 || gridX >= m_width || gridY < 0 || gridY >= m_height) continue;

			m_colorGrid[(size_t)gridY * m_width + gridX] = 0xFF0000FF;
		}
	}
}

void Simulation::Update(float dt) {

}
