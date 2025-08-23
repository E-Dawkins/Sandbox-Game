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

	public:
		void TickPhysics(const Game& _g);
		void Draw();
		
	private:
		bool TryMoveTo(const Game& _g, int _moveX, int _moveY);
	};
}