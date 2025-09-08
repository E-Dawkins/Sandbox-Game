#include "core/particle_defines.h"

#include "core/game.h"

void Core::Particle_Water::HandleInteraction(const Game& _g, const std::unique_ptr<Particle>& _other) {
	if (_other->IsOfType<Particle_Fire>()) {
		_g.ApplyParticleInteraction(posX, posY, _other->posX, _other->posY, "steam");
	}

	if (_other->IsOfType<Particle_Cryo>()) {
		_g.ApplyParticleInteraction(posX, posY, _other->posX, _other->posY, "ice");
	}

	if (_other->IsOfType<Particle_Lava>()) {
		// Apple interaction to vertically lower particle
		if (posY < _other->posY) {
			_g.ApplyParticleInteraction(_other->posX, _other->posY, posX, posY, "stone");
		}
		else {
			_g.ApplyParticleInteraction(posX, posY, _other->posX, _other->posY, "stone");
		}
	}
}

void Core::Particle_Steam::HandleInteraction(const Game& _g, const std::unique_ptr<Particle>& _other) {
	if (_other->IsOfType<Particle_Cryo>()) {
		_g.ApplyParticleInteraction(posX, posY, _other->posX, _other->posY, "water");
	}
}

void Core::Particle_Ice::HandleInteraction(const Game& _g, const std::unique_ptr<Particle>& _other) {
	if (_other->IsOfType<Particle_Fire>()) {
		_g.ApplyParticleInteraction(posX, posY, _other->posX, _other->posY, "water");
	}
}

void Core::Particle_Oil::HandleInteraction(const Game& _g, const std::unique_ptr<Particle>& _other) {
	if (_other->IsOfType<Particle_Fire>()) {
		_g.ApplyParticleInteraction(posX, posY, _other->posX, _other->posY, "smoke");
	}
}

void Core::Particle_Sand::HandleInteraction(const Game& _g, const std::unique_ptr<Particle>& _other) {
	if (_other->IsOfType<Particle_Fire>()) {
		_g.ApplyParticleInteraction(posX, posY, _other->posX, _other->posY, "glass");
	}
}
