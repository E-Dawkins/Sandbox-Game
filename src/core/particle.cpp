#include "core/particle.h"

#include "core/game.h"

void Core::Particle::PreCalculateMove(const Game& _g) {
	// No point calculating next move if we can't move
	if (isStatic) {
		return;
	}

	mMoveX = 0;
	mMoveY = 0;

	// Only run move checks on non-stationary particles
	auto checkMoveTo = [&](int _offsetX, int _offsetY) {
		if (auto& p = _g.GetParticleAtPosition(posX + _offsetX, posY + _offsetY); p == nullptr || p->mIsFalling) {
			if (_g.IsInScreenBounds(posX + _offsetX, posY + _offsetY)) {
				mMoveX = _offsetX;
				mMoveY = _offsetY;
			}
		}
		else if (p->isLiquid && !isLiquid) {
			p->mLiquidMoveX = -_offsetX;
			p->mLiquidMoveY = -_offsetY;
		}
		else {
			return false;
		}

		return true;
	};

	if (!checkMoveTo(0, 1)) {			// Down
		if (!checkMoveTo(-1, 1)) {		// Down-left
			if (!checkMoveTo(1, 1)) {	// Down-right
				// hate this nesting, but this works
			}
		}
	}

	mIsFalling = (mMoveX != 0 || mMoveY != 0);
}

void Core::Particle::TickPhysics(const Game& _g) {
	// No point running physics if we aren't going to move
	if (isStatic) {
		mIsFalling = false; // this is necessary for other particle logic
		return;
	}

	// Double check the next move is still possible
	if (auto& p = _g.GetParticleAtPosition(posX + mMoveX, posY + mMoveY); p == nullptr) {
		posX += mMoveX;
		posY += mMoveY;
	}

	// Special case for liquids
	if (isLiquid && (mLiquidMoveX != 0 || mLiquidMoveY != 0)) {
		auto& p = _g.GetParticleAtPosition(posX + mLiquidMoveX, posY + mLiquidMoveY);
		p->posX -= mLiquidMoveX;
		p->posY -= mLiquidMoveY;

		posX += mLiquidMoveX;
		posY += mLiquidMoveY;

		mLiquidMoveX = 0;
		mLiquidMoveY = 0;
	}
}

void Core::Particle::Draw() {
	DrawRectangle(posX * size, posY * size, size, size, color);
}
