#include "core/particle.h"

#include "core/game.h"

void Core::Particle::TickPhysics(const Game& _g) {
	auto checkMoveTo = [&](int _x, int _y) {
		if (!_g.IsInScreenBounds(_x, _y)) {
			return false;
		}

		auto& p = _g.GetParticleAtPosition(_x, _y);
		if (p == nullptr) {
			posX = _x;
			posY = _y;
			return true;
		}

		if (p->mIsFalling) {
			return true;
		}

		return false;
	};

	if (checkMoveTo(posX, posY + 1) || checkMoveTo(posX - 1, posY + 1) || checkMoveTo(posX + 1, posY + 1)) {
		mIsFalling = true;
	}
	else {
		// Couldn't move
		mIsFalling = false;
	}
}

void Core::Particle::Draw() {
	DrawRectangle(posX * size, posY * size, size, size, color);
}
