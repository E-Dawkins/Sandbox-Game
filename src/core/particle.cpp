#include "core/particle.h"

#include "core/game.h"

void Core::Particle::PreCalculateMove(const Game& _g) {
	moveX = 0;
	moveY = 0;

	// Down
	if (auto& p1 = _g.GetParticleAtPosition(posX, posY + 1); p1 == nullptr || p1->mIsFalling) {
		if (_g.IsInScreenBounds(posX, posY + 1)) {
			moveY = 1;
		}
	}
	// Down-left
	else if (auto& p2 = _g.GetParticleAtPosition(posX - 1, posY + 1); p2 == nullptr || p1->mIsFalling) {
		if (_g.IsInScreenBounds(posX - 1, posY + 1)) {
			moveX = -1;
			moveY = 1;
		}
	}
	// Down-right
	else if (auto& p3 = _g.GetParticleAtPosition(posX + 1, posY + 1); p3 == nullptr || p1->mIsFalling) {
		if (_g.IsInScreenBounds(posX + 1, posY + 1)) {
			moveX = 1;
			moveY = 1;
		}
	}

	mIsFalling = (moveX != 0 || moveY != 0);
}

void Core::Particle::TickPhysics(const Game& _g) {
	// Double check the next move is still possible, otherwise re-calculate it
	if (auto& p = _g.GetParticleAtPosition(posX + moveX, posY + moveY)) {
		PreCalculateMove(_g);
	}

	posX += moveX;
	posY += moveY;
}

void Core::Particle::Draw() {
	DrawRectangle(posX * size, posY * size, size, size, color);
}
