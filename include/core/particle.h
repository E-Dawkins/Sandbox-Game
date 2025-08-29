#pragma once

#include <raylib.h>

namespace Core {
	class Game;

	enum class ParticleState {
		SOLID,
		LIQUID,
		GAS,

		COUNT
	};

	class Particle {
	public:
		int posX = 0, posY = 0;
		int size = 10;
		Color color = WHITE;

		// Attributes

		bool isStatic = false;							// should this particle be immovable?

		ParticleState state = ParticleState::SOLID;		// what state is this particle in?

		int density = 0;								// determines order that non-solids stack on each other
		int range = 0;									// how far does a non-solid check for elevation change?

	public:
		void TickPhysics(const Game& _g);
		void Draw();
		
	private:
		bool TryMoveTo(const Game& _g, int _moveX, int _moveY);
		bool TryMoveToRanged(const Game& _g, int _checkRange, bool _checkLeft, bool _checkDown);
		bool IsMoveToOccupied(const Game& _g, int _moveX, int _moveY);
	};
}