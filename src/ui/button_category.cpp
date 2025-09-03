#include "ui/button_category.h"

#include <iostream>

#include "core/raylib_helpers.h"
#include "core/particle_defines.h"
#include "ui/button_particle.h"

Ui::Button_Category::Button_Category(int _posX, int _posY, int _sizeX, int _sizeY, Core::ParticleState _stateCategory, ParticleButtonCallback _callback)
	: Button(_posX, _posY, _sizeX, _sizeY) 
{
	mCallback = std::bind(&Ui::Button_Category::ClickCallback, this);
	mParticleButtonCallback = _callback;

	baseColor = DARKGRAY;
	hoveredColor = GRAY;
	mBgColor = Color(30, 30, 30, 255);

	mStateIndex = static_cast<int>(_stateCategory);

	mExpanded = false;
	mAnyChildrenHovered = false;

	ReconstructButton();
	InitialiseChildButtons(_stateCategory);
}

bool Ui::Button_Category::Update(const Vector2 _mousePos) {
	bool mouseInputConsumed = Ui::Button::Update(_mousePos);

	if (mouseInputConsumed) {
		return true;
	}

	// Only check child buttons when category is expanded
	if (!mExpanded) {
		return false;
	}

	mAnyChildrenHovered = false;
	for (const auto& b : mChildButtons) {
		if (b->IsHovered()) {
			mAnyChildrenHovered = true;
		}

		if (b->Update(_mousePos)) {
			return true;
		}
	}

	return false;
}

void Ui::Button_Category::Draw() {
	Ui::Button::Draw();

	DrawRectangleRounded(mBgRect, 0.5f, 4, mBgColor);
	Core::Raylib_Helpers::DrawTextCenteredEx(Core::gParticleStateNames[mStateIndex].c_str(), mTextPos, 14, 2, WHITE);

	// Only draw child buttons while expanded
	if (mExpanded) {
		for (const auto& b : mChildButtons) {
			b->Draw();
		}
	}
}

bool Ui::Button_Category::IsHovered() const {
	return mAnyChildrenHovered || Ui::Button::IsHovered();
}

void Ui::Button_Category::ReconstructButton() {
	Ui::Button::ReconstructButton();

	const int minPad = static_cast<int>(std::min(sizeX * 0.1f, sizeY * 0.1f));
	mBgRect = Rectangle{
		.x = static_cast<float>(posX + minPad),
		.y = static_cast<float>(posY + minPad),
		.width = static_cast<float>(sizeX - minPad * 2),
		.height = static_cast<float>(sizeY - minPad * 2),
	};

	mTextPos = Vector2{
		.x = static_cast<float>(posX + sizeX / 2),
		.y = static_cast<float>(posY + sizeY / 2)
	};
}

void Ui::Button_Category::ClickCallback() {
	mExpanded = !mExpanded;

	for (const auto& b : mChildButtons) {
		if (mExpanded) {
			b->posY = posY;
		}
		else {
			b->posY = -100;
		}

		b->ReconstructButton();
	}
}

void Ui::Button_Category::InitialiseChildButtons(Core::ParticleState _stateCategory) {
	const int startX = posX + (sizeX / 2);
	const int minSize = static_cast<int>(std::min(sizeX, sizeY));
	const int spacing = 10;

	for (const auto& [name, constructor] : Core::gParticleTypes) {
		const auto instance = constructor();

		if (instance->state == _stateCategory) {
			const int currentIndex = static_cast<int>(mChildButtons.size()) + 1;
			const int curPosX = startX + ((minSize + spacing) * currentIndex);

			// Initialise the child buttons off-screen, so it appears that the category is 'collapsed'
			Ui::Button_Particle particleButton = Ui::Button(curPosX, -100, minSize, minSize, [&]() { mParticleButtonCallback(name); });
			particleButton.SetParticleType(name);
			
			mChildButtons.emplace_back(std::make_unique<Ui::Button_Particle>(particleButton));
		}
	}
}
