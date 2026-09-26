#pragma once

#include <vector>
#include <cstdint>

#include "Material.h"

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

	void UpdateCell(int x, int y);
	void RebuildColorGrid();

	size_t GetIndex(int x, int y) const;
	bool InBounds(int x, int y) const;
	int GetMaterial(int x, int y) const;

	void SetMaterial(int x, int y, int materialId);
	void SwapMaterial(int x1, int y1, int x2, int y2);

	bool CanDisplace(int fromId, int toId) const;

	bool TryMoveVertical(int x, int y, int dir);
	bool TryMoveDiagonal(int x, int y, int dir);
	bool TryMoveSideways(int x, int y);
};
