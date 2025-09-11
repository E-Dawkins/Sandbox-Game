#include "ui/button_labeled.h"

#include "core/raylib_helpers.h"

Ui::Button_Labeled::Button_Labeled(int _posX, int _posY, int _sizeX, int _sizeY, std::string _label, ButtonCallback _callback)
	: Button(_posX, _posY, _sizeX, _sizeY, _callback), mLabel(_label)
{
	baseColor = DARKGRAY;
	hoveredColor = GRAY;
	mBgColor = Color(30, 30, 30, 255);

	ReconstructButton();
}

void Ui::Button_Labeled::Draw() {
	Button::Draw();

	DrawRectangleRounded(mBgRect, 0.5f, 4, mBgColor);
	Core::Raylib_Helpers::DrawTextCenteredEx(mLabel.c_str(), mLabelPos, 28, 4, WHITE);
}

void Ui::Button_Labeled::ReconstructButton() {
	Button::ReconstructButton();

	mLabelPos = {
		static_cast<float>(posX + (sizeX / 2)),
		static_cast<float>(posY + (sizeY / 2))
	};

	const int minPad = static_cast<int>(std::min(sizeX * 0.1f, sizeY * 0.1f));
	mBgRect = Rectangle{
		.x = static_cast<float>(posX + minPad),
		.y = static_cast<float>(posY + minPad),
		.width = static_cast<float>(sizeX - minPad * 2),
		.height = static_cast<float>(sizeY - minPad * 2),
	};
}
