#include "core/particle.h"

#include "core/game.h"

void Core::Particle::PreCalculateMove(const Game& _g) {
	mMoveX = 0;
	mMoveY = 0;

	// Only run move checks on non-stationary particles
	if (!isStatic) {
		// Down
		if (auto& p1 = _g.GetParticleAtPosition(posX, posY + 1); p1 == nullptr || p1->mIsFalling) {
			if (_g.IsInScreenBounds(posX, posY + 1)) {
				mMoveY = 1;
			}
		}
		// Down-left
		else if (auto& p2 = _g.GetParticleAtPosition(posX - 1, posY + 1); p2 == nullptr || p1->mIsFalling) {
			if (_g.IsInScreenBounds(posX - 1, posY + 1)) {
				mMoveX = -1;
				mMoveY = 1;
			}
		}
		// Down-right
		else if (auto& p3 = _g.GetParticleAtPosition(posX + 1, posY + 1); p3 == nullptr || p1->mIsFalling) {
			if (_g.IsInScreenBounds(posX + 1, posY + 1)) {
				mMoveX = 1;
				mMoveY = 1;
			}
		}
	}

	mIsFalling = (mMoveX != 0 || mMoveY != 0);
}

void Core::Particle::TickPhysics(const Game& _g) {
	// No point running physics if we aren't going to move
	if (mMoveX == 0 && mMoveY == 0) {
		return;
	}

	// Double check the next move is still possible, otherwise re-calculate it
	if (auto& p = _g.GetParticleAtPosition(posX + mMoveX, posY + mMoveY)) {
		PreCalculateMove(_g);
	}

	posX += mMoveX;
	posY += mMoveY;
}

void Core::Particle::Draw() {
	DrawRectangle(posX * size, posY * size, size, size, color);
}
