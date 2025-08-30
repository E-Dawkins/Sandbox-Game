#include "core/particle_defines.h"

#include <iostream>

void Core::Particle_Water::HandleInteraction(const std::unique_ptr<Particle>& _other) {
	if (dynamic_cast<Particle_Sand*>(_other.get())) {
		std::cout << "WATER <-> SAND\n";
	}
}
