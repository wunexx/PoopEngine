#include "Simulation.h"

void Simulation::Init(int width, int height) {
	m_width = width;
	m_height = height;

	m_materialGrid.assign((size_t)width * height, 0);
	m_colorGrid.assign((size_t)width * height, g_materials[0].color);

	const int AIR = 0, SAND = 1, WATER = 2, STONE = 3, SMOKE = 4;

	int centerX = m_width / 2;
	int centerY = m_height / 2;
	int blobRadius = m_width / 10;

	for (int y = -blobRadius; y <= blobRadius; y++) {
		for (int x = -blobRadius; x <= blobRadius; x++) {
			if (x * x + y * y > blobRadius * blobRadius) continue;
			int gx = centerX + x, gy = centerY + y;
			if (!InBounds(gx, gy)) continue;
			SetMaterial(gx, gy, STONE);
		}
	}

	int waterW = m_width / 6;
	int waterH = m_height / 8;
	int waterStartX = centerX - waterW / 2;
	int waterStartY = centerY - blobRadius - waterH - 10;

	for (int y = 0; y < waterH; y++) {
		for (int x = 0; x < waterW; x++) {
			int gx = waterStartX + x, gy = waterStartY + y;
			if (!InBounds(gx, gy)) continue;
			SetMaterial(gx, gy, WATER);
		}
	}

	int sandW = m_width / 10;
	int sandH = m_height / 10;
	int sandStartX = centerX - sandW / 2;
	int sandStartY = waterStartY - sandH - 20;

	for (int y = 0; y < sandH; y++) {
		for (int x = 0; x < sandW; x++) {
			int gx = sandStartX + x, gy = sandStartY + y;
			if (!InBounds(gx, gy)) continue;
			SetMaterial(gx, gy, SAND);
		}
	}

	int smokeW = m_width / 8;
	int smokeH = m_height / 10;
	int smokeStartX = centerX - smokeW / 2;
	int smokeStartY = centerY + blobRadius + 10;

	for (int y = 0; y < smokeH; y++) {
		for (int x = 0; x < smokeW; x++) {
			int gx = smokeStartX + x, gy = smokeStartY + y;
			if (!InBounds(gx, gy)) continue;
			SetMaterial(gx, gy, SMOKE);
		}
	}

	RebuildColorGrid();
}

size_t Simulation::GetIndex(int x, int y) const {
	return (size_t)y * m_width + x;
}

bool Simulation::InBounds(int x, int y) const {
	return x >= 0 && x < m_width && y >= 0 && y < m_height;
}

int Simulation::GetMaterial(int x, int y) const {
	if (!InBounds(x, y)) return -1;
	return m_materialGrid[GetIndex(x, y)];
}

void Simulation::SetMaterial(int x, int y, int materialId) {
	if (!InBounds(x, y)) return;
	m_materialGrid[GetIndex(x, y)] = materialId;
}

void Simulation::SwapMaterial(int x1, int y1, int x2, int y2) {
	int a = GetMaterial(x1, y1);
	int b = GetMaterial(x2, y2);
	SetMaterial(x1, y1, b);
	SetMaterial(x2, y2, a);
}

bool Simulation::CanDisplace(int fromId, int toId) const {
	if (toId == -1) return false;

	MaterialState toState = g_materials[toId].state;

	if (toState == MaterialState::Air) return true;
	if (toState == MaterialState::Solid) return false;

	return g_materials[fromId].density > g_materials[toId].density;
}

bool Simulation::TryMoveVertical(int x, int y, int dir) {
	int self = GetMaterial(x, y);
	int below = GetMaterial(x, y + dir);

	if (CanDisplace(self, below)) {
		SwapMaterial(x, y, x, y + dir);
		return true;
	}

	return false;
}

bool Simulation::TryMoveDiagonal(int x, int y, int dir) {
	int self = GetMaterial(x, y);

	bool leftFirst = (rand() % 2) == 0;
	int dxs[2] = { leftFirst ? -1 : 1, leftFirst ? 1 : -1 };

	for (int dx : dxs) {
		int diag = GetMaterial(x + dx, y + dir);

		if (CanDisplace(self, diag)) {
			SwapMaterial(x, y, x + dx, y + dir);
			return true;
		}
	}

	return false;
}

bool Simulation::TryMoveSideways(int x, int y) {
	int self = GetMaterial(x, y);

	bool leftFirst = (rand() % 2) == 0;
	int dxs[2] = { leftFirst ? -1 : 1, leftFirst ? 1 : -1 };

	for (int dx : dxs) {
		int side = GetMaterial(x + dx, y);

		if (CanDisplace(self, side)) {
			SwapMaterial(x, y, x + dx, y);
			return true;
		}
	}

	return false;
}

void Simulation::UpdateCell(int x, int y) {
	Material mat = g_materials[(size_t)GetMaterial(x, y)];

	switch (mat.state) {
		case MaterialState::Powder:
			if (TryMoveVertical(x, y, 1)) return;
			TryMoveDiagonal(x, y, 1);
			break;

		case MaterialState::Liquid:
			if(TryMoveVertical(x, y, 1)) return;
			if(TryMoveDiagonal(x, y, 1)) return;
			TryMoveSideways(x, y);
			break;

		case MaterialState::Gas:
			if (TryMoveVertical(x, y, -1)) return;
			if (TryMoveDiagonal(x, y, -1)) return;
			TryMoveSideways(x, y);
			break;
	}
}

void Simulation::Update(float dt) {
	static bool sweepRightToLeft = false;

	int xStart = sweepRightToLeft ? m_width - 1 : 0;
	int xEnd = sweepRightToLeft ? -1 : m_width;
	int xStep = sweepRightToLeft ? -1 : 1;

	for (int y = m_height - 1; y >= 0; y--) {
		for (int x = xStart; x != xEnd; x += xStep) {
			int id = GetMaterial(x, y);
			if (id <= 0) continue;
			MaterialState state = g_materials[id].state;
			if (state == MaterialState::Powder || state == MaterialState::Liquid) {
				UpdateCell(x, y);
			}
		}
	}

	for (int y = 0; y < m_height; y++) {
		for (int x = xStart; x != xEnd; x += xStep) {
			int id = GetMaterial(x, y);
			if (id <= 0) continue;
			if (g_materials[id].state == MaterialState::Gas) UpdateCell(x, y);
		}
	}

	sweepRightToLeft = !sweepRightToLeft;
	RebuildColorGrid();
}

void Simulation::RebuildColorGrid() {
	for (size_t i = 0; i < m_materialGrid.size(); i++) {
		int id = m_materialGrid[i];
		m_colorGrid[i] = g_materials[id].color;
	}
}
