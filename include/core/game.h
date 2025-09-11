#pragma once

#include "core/particle.h"
#include "ui/button.h"

#include <memory>
#include <string>
#include <vector>

namespace Core {
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

		void ReplaceParticleAtPos(int _posX, int _posY, std::string _type) const;

		// Replace (1) with _resultType, and (2) with "null"
		void ApplyParticleInteraction(int _posX1, int _posY1, int _posX2, int _posY2, std::string _resultType) const;

	private:
		void SetupButtons();

		void ProcessInput();
		void AddParticleToSystem(int _posX, int _posY, std::string _type) const;
		void RemoveParticleFromSystem(int _posX, int _posY) const;
		void RemoveAllParticles();

		void ApplyFuncInRadius(int _r, std::function<void(int, int)> _f);

		void SaveCurrentGameState();
		void LoadNewGameState();

	private:
		// This is mutable to allow 'AddParticleToSystem' and 'RemoveParticleFromSystem' to work on const Game objects
		// i.e. for particles to call these functions on interaction events
		mutable std::vector<std::unique_ptr<Core::Particle>> mParticles = {};
		int mParticleSize = 10;

		std::vector<std::unique_ptr<Ui::Button>> mButtons = {};
		bool mMouseInputConsumed = false;
		bool mHoveringAnyButton = false;

		int mRows = 0;
		int mCols = 0;

		std::string mTypeToSpawn = "sand";
		int mSpawnRadius = 3;

		bool mIsSimulating = true;
		bool mShouldStep = false;
	};
}