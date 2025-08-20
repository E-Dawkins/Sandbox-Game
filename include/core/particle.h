#pragma once

#include <raylib.h>

namespace Core {
	class Game;

	class Particle {
	public:
		int posX = 0, posY = 0;
		int size = 10;
		Color color = WHITE;

		// Attributes

		bool isStatic = false;
		bool isLiquid = false;
		int liquidDensity = 0;

	private:
		bool mIsFalling = true;
		int mMoveX = 0, mMoveY = 0;
		int mLiquidMoveX = 0, mLiquidMoveY = 0;

	public:
		void PreCalculateMove(const Game& _g);
		void TickPhysics(const Game& _g);
		void Draw();
	};
}