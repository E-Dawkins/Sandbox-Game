#include "ui/button.h"

Ui::Button::Button(int _posX, int _posY, int _sizeX, int _sizeY, ButtonCallback _callback) {
	posX = _posX;
	posY = _posY;
	sizeX = _sizeX;
	sizeY = _sizeY;

	mCallback = _callback;

	// Create rectangle now, as the button shouldn't ever move
	ReconstructButton();
}

bool Ui::Button::Update(const Vector2 _mousePos) {
	// Check if the mouse position is overlapping the button area
	// Buttons are drawn from the top-left

	bool withinX = (_mousePos.x >= posX && _mousePos.x <= posX + sizeX);
	bool withinY = (_mousePos.y >= posY && _mousePos.y <= posY + sizeY);

	mIsHovered = withinX && withinY;

	if (mIsHovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		mCallback();

		return true;
	}

	return false;
}

void Ui::Button::Draw() {
	DrawRectangleRounded(mAreaRect, 0.5f, 4, mIsHovered ? hoveredColor : baseColor);
}

const Ui::Button::ButtonCallback& Ui::Button::GetCallback() const {
	return mCallback;
}

bool Ui::Button::IsHovered() const {
	return mIsHovered;
}

void Ui::Button::ReconstructButton() {
	mAreaRect = Rectangle{
		.x = static_cast<float>(posX),
		.y = static_cast<float>(posY),
		.width = static_cast<float>(sizeX),
		.height = static_cast<float>(sizeY)
	};
}
