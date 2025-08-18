#pragma once

#include "core/particle.h"

#include <memory>
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
		const std::shared_ptr<Core::Particle> GetParticleAtPosition(int _x, int _y) const;
		bool IsInScreenBounds(int _x, int _y) const;

	private:
		void ProcessInput();
		void AddParticleToSystem(int _posX, int _posY, Color _col);
		void RemoveParticleFromSystem(int _posX, int _posY);

		void SpawnParticlesInSquare(int _minX, int _maxX, int _minY, int _maxY, Color _col);
		void RemoveParticlesInSquare(int _minX, int _maxX, int _minY, int _maxY);

	private:
		std::vector<std::shared_ptr<Core::Particle>> mParticles = {};
		int mParticleSize = 10;

		int mRows = 0;
		int mCols = 0;
	};
}