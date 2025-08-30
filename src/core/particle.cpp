#include "core/particle.h"

#include "core/game.h"

void Core::Particle::TickPhysics(const Game& _g) {
	// Can't move
	if (isStatic) {
		return;
	}

	// Perform relevant short-range move
	const int verticalOffset = (state == ParticleState::GAS ? -1 : 1);

	if (TryMoveTo(_g, 0, verticalOffset)) {
		return;
	}

	if (TryMoveTo(_g, -1, verticalOffset)) {
		return;
	}

	if (TryMoveTo(_g, 1, verticalOffset)) {
		return;
	}

	if (state == ParticleState::LIQUID || state == ParticleState::GAS) {
		// Liquids and gases should check the furthest point that they can move towards
		// i.e. liquids check the lowest point, gases check the highest point
		const bool checkDown = (state == ParticleState::LIQUID);

		if (TryMoveToRanged(_g, range, true, checkDown)) {
			return;
		}

		if (TryMoveToRanged(_g, range, false, checkDown)) {
			return;
		}
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
		bool solidIntoLiquid = (state == ParticleState::SOLID && p->state == ParticleState::LIQUID);
		bool liquidIntoLiquid = (state == ParticleState::LIQUID && p->state == ParticleState::LIQUID && density > p->density);
		bool solidIntoGas = (state == ParticleState::SOLID && p->state == ParticleState::GAS);
		bool gasIntoGas = (state == ParticleState::GAS && p->state == ParticleState::GAS && density < p->density);

		// If any of the move rules are met, swap particle positions
		if (solidIntoLiquid || liquidIntoLiquid || solidIntoGas || gasIntoGas) {
			p->posX = posX;
			p->posY = posY;
		}
		// Move to location is not possible
		else {
			HandleInteraction(p);
			return false;
		}
	}

	// Successful move
	posX = offsetPosX;
	posY = offsetPosY;

	return true;
}

bool Core::Particle::TryMoveToRanged(const Game& _g, int _checkRange, bool _checkLeft, bool _checkDown) {
	const int sign = (_checkLeft ? -1 : 1);
	const int vertical = (_checkDown ? 1 : -1);

	for (int i = 1; i < _checkRange; i++) {
		// Check if direct sideways is possible
		if (IsMoveToOccupied(_g, i * sign, 0)) {
			break;
		}

		// If it is, check vertically
		if (!IsMoveToOccupied(_g, i * sign, vertical)) {
			posX += sign;
			break;
		}
	}

	return false;
}

bool Core::Particle::IsMoveToOccupied(const Game& _g, int _moveX, int _moveY) {
	int offsetPosX = posX + _moveX;
	int offsetPosY = posY + _moveY;

	// Treat off screen as 'occupied'
	if (!_g.IsInScreenBounds(offsetPosX, offsetPosY)) {
		return true;
	}

	// If particle is valid, position is occupied
	const auto& p = _g.GetParticleAtPosition(offsetPosX, offsetPosY);
	return p != nullptr;
}

void Core::Particle::HandleInteraction(const std::shared_ptr<Particle>& _other) {
	// By default do nothing
	_other;
}
