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

	enum class GasDensities : int {
		STEAM,
		SMOKE,

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

	class Particle_Steam : public Particle {
	public:
		Particle_Steam() {
			color = RAYWHITE;
			isGas = true;
			gasRange = 10;
			gasDensity = static_cast<int>(GasDensities::STEAM);
		}
	};

	class Particle_Smoke : public Particle {
	public:
		Particle_Smoke() {
			color = DARKGRAY;
			isGas = true;
			gasRange = 6;
			gasDensity = static_cast<int>(GasDensities::SMOKE);
		}
	};

	static std::map<std::string, Particle> gParticleTypes = {
		{"sand", Particle_Sand()},
		{"stone", Particle_Stone()},
		{"water", Particle_Water()},
		{"oil", Particle_Oil()},
		{"steam", Particle_Steam()},
		{"smoke", Particle_Smoke()},
	};
}