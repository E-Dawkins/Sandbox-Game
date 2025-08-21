#pragma once

#include "ui/button.h"

#include <string>

namespace Ui {
	class Button_Particle : public Button {
	private:
		Color mParticleColor;
		Color mBgColor;

		Rectangle mBgRect;
		Rectangle mItemRect;

	public:
		Button_Particle(const Button& x);

		void Draw() override;

		void SetParticleType(std::string _type);
	};
}