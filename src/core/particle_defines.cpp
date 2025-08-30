#include "core/particle_defines.h"

#include <iostream>
#include "core/game.h"

void Core::Particle_Water::HandleInteraction(const Game& _g, const std::unique_ptr<Particle>& _other) {
	if (dynamic_cast<Particle_Fire*>(_other.get())) {
		// Replace ourself with steam particle
		const int storedPosX = posX, storedPosY = posY;

		_g.RemoveParticleFromSystem(storedPosX, storedPosY);
		_g.AddParticleToSystem(storedPosX, storedPosY, "steam");
	}
	else if (dynamic_cast<Particle_Cryo*>(_other.get())) {
		// Replace ourself with ice particle
		const int storedPosX = posX, storedPosY = posY;
		_g.RemoveParticleFromSystem(storedPosX, storedPosY);
		_g.AddParticleToSystem(storedPosX, storedPosY, "ice");
	}
}
