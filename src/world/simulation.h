#pragma once
#include <vector>
#include <cstdint>

class Simulation {
public:
	void Init(int width, int height);

	void Update(float dt);

	const std::vector<uint32_t>& GetColorGrid() const { return m_colorGrid; };

private:
	int m_width = 0;
	int m_height = 0;

	std::vector<int> m_materialGrid;
	std::vector<uint32_t> m_colorGrid;
};
