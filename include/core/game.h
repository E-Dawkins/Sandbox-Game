#pragma once

#include "core/particle.h"
#include "ui/button.h"

#include <memory>
#include <string>
#include <vector>

namespace Core {
	class Particle;
	
	class Game {
	public:
		void Init();
		
		void Update();
		void Draw();

		void Shutdown();

		// Helpers

		bool IsRunning() const;
		const std::unique_ptr<Core::Particle>& GetParticleAtPosition(int _x, int _y) const;
		bool IsInScreenBounds(int _x, int _y) const;

	private:
		void SetupButtons();

		void ProcessInput();
		void AddParticleToSystem(int _posX, int _posY, std::string _type);
		void RemoveParticleFromSystem(int _posX, int _posY);

		void SpawnParticlesInRadius(int _posX, int _posY, int _radius, std::string _type);
		void RemoveParticlesInRadius(int _posX, int _posY, int _radius);

	private:
		std::vector<std::unique_ptr<Core::Particle>> mParticles = {};
		int mParticleSize = 10;

		std::vector<std::unique_ptr<Ui::Button>> mButtons = {};
		bool mMouseInputConsumed = false;

		int mRows = 0;
		int mCols = 0;

		std::string mTypeToSpawn = "sand";
	};
}