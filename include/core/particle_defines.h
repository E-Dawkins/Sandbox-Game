#pragma once

#include "core/particle.h"

#include <map>
#include <string>
#include <functional>
#include <memory>

namespace Core {
	enum class LiquidDensities : int {
		OIL,
		WATER,

		COUNT
	};

	enum class GasDensities : int {
		STEAM,
		SMOKE,
		FIRE,
		CRYO,

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
			color = Color{ 50, 131, 241, 255 };
			state = ParticleState::LIQUID;
			density = static_cast<int>(LiquidDensities::WATER);
			range = 8;
		}

	protected:
		void HandleInteraction(const Game& _g, const std::unique_ptr<Particle>& _other) override;
	};

	class Particle_Oil : public Particle {
	public:
		Particle_Oil() {
			color = Color{ 50, 50, 50, 255 }; // Darker gray
			state = ParticleState::LIQUID;
			density = static_cast<int>(LiquidDensities::OIL);
			range = 4;
		}
	};

	class Particle_Steam : public Particle {
	public:
		Particle_Steam() {
			color = RAYWHITE;
			state = ParticleState::GAS;
			density = static_cast<int>(GasDensities::STEAM);
			range = 10;
		}

	protected:
		void HandleInteraction(const Game& _g, const std::unique_ptr<Particle>& _other) override;
	};

	class Particle_Smoke : public Particle {
	public:
		Particle_Smoke() {
			color = DARKGRAY;
			state = ParticleState::GAS;
			density = static_cast<int>(GasDensities::SMOKE);
			range = 6;
		}
	};

	class Particle_Fire : public Particle {
	public:
		Particle_Fire() {
			color = Color{ 255, 130, 0, 255 };
			state = ParticleState::GAS;
			density = static_cast<int>(GasDensities::FIRE);
			range = 8;
		}
	};

	class Particle_Cryo : public Particle {
	public:
		Particle_Cryo() {
			color = SKYBLUE;
			state = ParticleState::GAS;
			density = static_cast<int>(GasDensities::CRYO);
			range = 3;
		}
	};

	class Particle_Ice : public Particle {
	public:
		Particle_Ice() {
			color = Color{ 170, 210, 255, 255 };
			isStatic = true;
		}

	protected:
		void HandleInteraction(const Game& _g, const std::unique_ptr<Particle>& _other) override;
	};

	static std::map<std::string, std::function<std::unique_ptr<Particle>()>> gParticleTypes = {
		{"sand",	[]() { return std::make_unique<Particle_Sand>(); }},
		{"stone",	[]() { return std::make_unique<Particle_Stone>(); }},
		{"water",	[]() { return std::make_unique<Particle_Water>(); }},
		{"oil",		[]() { return std::make_unique<Particle_Oil>(); }},
		{"steam",	[]() { return std::make_unique<Particle_Steam>(); }},
		{"smoke",	[]() { return std::make_unique<Particle_Smoke>(); }},
		{"fire",	[]() { return std::make_unique<Particle_Fire>(); }},
		{"cryo",	[]() { return std::make_unique<Particle_Cryo>(); }},
		{"ice",		[]() { return std::make_unique<Particle_Ice>(); }},
	};
}