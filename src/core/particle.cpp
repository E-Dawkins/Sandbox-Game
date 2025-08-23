#include "core/particle.h"

#include "core/game.h"

void Core::Particle::TickPhysics(const Game& _g) {
	// Can't move
	if (isStatic) {
		return;
	}

	// Perform relevant move
	if (TryMoveTo(_g, 0, 1)) {
		return;
	}

	if (TryMoveTo(_g, -1, 1)) {
		return;
	}

	if (TryMoveTo(_g, 1, 1)) {
		return;
	}
}

void Core::Particle::Draw() {
	DrawRectangle(posX * size, posY * size, size, size, color);
}

bool Core::Particle::TryMoveTo(const Game& _g, int _moveX, int _moveY) {
	int offsetPosX = posX + _moveX;
	int offsetPosY = posY + _moveY;

	// Can't move off screen
	if (!_g.IsInScreenBounds(offsetPosX, offsetPosY)) {
		return false;
	}

	// Is the move to location occupied?
	const auto& p = _g.GetParticleAtPosition(offsetPosX, offsetPosY);
	if (p != nullptr) {
		bool solidIntoLiquid = (!isLiquid && p->isLiquid);
		bool liquidIntoLiquid = (isLiquid && p->isLiquid && liquidDensity > p->liquidDensity);

		// If any of the move rules are met, swap particle positions
		if (solidIntoLiquid || liquidIntoLiquid) {
			p->posX = posX;
			p->posY = posY;
		}
		// Move to location is not possible
		else {
			return false;
		}
	}

	// Successful move
	posX = offsetPosX;
	posY = offsetPosY;

	return true;
}
