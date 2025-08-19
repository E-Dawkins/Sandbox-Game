#pragma once

#include <raylib.h>

namespace Core {
	class Game;

	class Particle {
	public:
		int posX = 0, posY = 0;
		int size = 10;
		Color color = WHITE;

	private:
		bool mIsFalling = true;
		int moveX = 0, moveY = 0;

	public:
		void PreCalculateMove(const Game& _g);
		void TickPhysics(const Game& _g);
		void Draw();
	};
}