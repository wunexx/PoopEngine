#pragma once

#include <string>

constexpr uint32_t MakeColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
	return (a << 24) | (b << 16) | (g << 8) | r;
}

enum class MaterialState {   
	Air, 
	Powder,
	Liquid,
	Solid,
	Gas
};

struct Material {
	std::string name;
	uint32_t color = MakeColor(0, 0, 0, 0);

	float density = 0.0;
	MaterialState state = MaterialState::Air;
};

//for testing and shit
inline const Material g_materials[] = {
	{ "Air", MakeColor(0, 0, 0, 0), 0.0f, MaterialState::Air },
	{ "Sand", MakeColor(255, 228, 120), 1500.0f, MaterialState::Powder },
	{ "Water", MakeColor(77, 166, 255, 200), 1000.0f, MaterialState::Liquid },
	{ "Stone", MakeColor(96, 96, 112), 2600.0f, MaterialState::Solid },
	{ "Smoke", MakeColor(194, 194, 209, 200), 500.0f, MaterialState::Gas },
};