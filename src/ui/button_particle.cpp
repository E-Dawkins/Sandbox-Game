#include "ui/button_particle.h"

#include "core/particle_defines.h"
#include "core/raylib_helpers.h"

Ui::Button_Particle::Button_Particle(const Button& x)
	: Button(x.posX, x.posY, x.sizeX, x.sizeY, x.GetCallback()) 
{
	baseColor = DARKGRAY;
	hoveredColor = GRAY;
	mBgColor = Color(30, 30, 30, 255);
	mParticleColor = BLACK;
	mParticleDrawType = Core::ParticleDrawType::FILLED;

	int padX = static_cast<int>(sizeX * 0.1f);
	int padY = static_cast<int>(sizeY * 0.1f);
	mBgRect = Rectangle{
		.x = static_cast<float>(posX + padX),
		.y = static_cast<float>(posY + padY),
		.width = static_cast<float>(sizeX - padX * 2),
		.height = static_cast<float>(sizeY - padY * 2),
	};

	padX = static_cast<int>(sizeX * 0.35f);
	padY = static_cast<int>(sizeY * 0.35f);
	mItemRect = Rectangle{
		.x = static_cast<float>(posX + padX),
		.y = static_cast<float>(posY + padY),
		.width = static_cast<float>(sizeX - padX * 2),
		.height = static_cast<float>(sizeY - padY * 2),
	};

	mTextPos = Vector2{
		.x = static_cast<float>(posX + sizeX / 2),
		.y = static_cast<float>(posY + sizeY + 5)
	};
}

void Ui::Button_Particle::Draw() {
	Ui::Button::Draw();

	DrawRectangleRounded(mBgRect, 0.5f, 4, mBgColor);
	switch (mParticleDrawType) {
		case Core::ParticleDrawType::FILLED: DrawRectangleRec(mItemRect, mParticleColor); break;
		case Core::ParticleDrawType::OUTLINE: DrawRectangleLinesEx(mItemRect, 1.f, mParticleColor); break;
	}
	Core::Raylib_Helpers::DrawTextCenteredEx(mParticleType.c_str(), mTextPos, 14, 2, WHITE);
}

void Ui::Button_Particle::SetParticleType(std::string _type) {
	// Instantiating here is not ideal, but we know that this function
	// will only be called on button creation, so it should be fine
	const auto particleInst = Core::gParticleTypes[_type]();

	mParticleColor = particleInst->color;
	mParticleDrawType = particleInst->drawType;
	mParticleType = _type;
}
