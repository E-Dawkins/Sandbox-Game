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

		bool isStatic = false;		// should this particle be immovable?
		bool isLiquid = false;		// is this particle a liquid?
		int liquidDensity = 0;		// determines order that liquids stack on each other
		int liquidRange = 0;		// how far does the liquid check for lower elevation?

	public:
		void TickPhysics(const Game& _g);
		void Draw();
		
	private:
		bool TryMoveTo(const Game& _g, int _moveX, int _moveY);
		bool TryMoveToLower(const Game& _g, int _checkRange, bool _checkLeft);
		bool IsMoveToOccupied(const Game& _g, int _moveX, int _moveY);
	};
}