#pragma once

#include "ui/button.h"
#include "core/particle.h"

#include <string>

namespace Ui {
	class Button_Particle : public Button {
	private:
		Color mParticleColor;
		Color mBgColor;

		Rectangle mBgRect;
		Rectangle mItemRect;

		std::string mParticleType;
		Vector2 mTextPos;

		Core::ParticleDrawType mParticleDrawType;

	public:
		Button_Particle(const Button& x);

		void Draw() override;

		void SetParticleType(std::string _type);
	};
}