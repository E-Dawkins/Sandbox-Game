#pragma once

#include "core/particle.h"

#include <map>
#include <string>

namespace Core {
	enum class LiquidDensities : int {
		OIL,
		WATER,

		COUNT
	};

	class Particle_Sand : public Particle {
	public:
		Particle_Sand() {
			color = ORANGE;
		}
	};

	class Particle_Stone : public Particle {
	public:
		Particle_Stone() {
			color = GRAY;
			isStatic = true;
		}
	};

	class Particle_Water : public Particle {
	public:
		Particle_Water() {
			color = SKYBLUE;
			isLiquid = true;
			liquidDensity = static_cast<int>(LiquidDensities::WATER);
			liquidRange = 8;
		}
	};

	class Particle_Oil : public Particle {
	public:
		Particle_Oil() {
			color = Color{ 50, 50, 50, 255 }; // Darker gray
			isLiquid = true;
			liquidDensity = static_cast<int>(LiquidDensities::OIL);
			liquidRange = 4;
		}
	};

	static std::map<std::string, Particle> gParticleTypes = {
		{"sand", Particle_Sand()},
		{"stone", Particle_Stone()},
		{"water", Particle_Water()},
		{"oil", Particle_Oil()},
	};
}