#include "ui/button_simulation.h"

Ui::Button_Simulation::Button_Simulation(int _posX, int _posY, int _sizeX, int _sizeY, Ui::SimulationControl _controlType, ButtonCallback _callback)
	: Button(_posX, _posY, _sizeX, _sizeY, _callback)
{
	baseColor = DARKGRAY;
	hoveredColor = GRAY;
	mBgColor = Color(30, 30, 30, 255);
	mFgColor = RAYWHITE;

	mControlType = _controlType;

	ReconstructButton();
}

void Ui::Button_Simulation::Draw() {
	Ui::Button::Draw();

	DrawRectangleRounded(mBgRect, 0.5f, 4, mBgColor);

	switch (mControlType) {
		case Ui::SimulationControl::PLAY: {
			DrawTriangle(
				mFgMin,
				{ mFgMin.x, mFgMax.y },
				{ mFgMax.x, (mFgMin.y + mFgMax.y) / 2.f },
				mFgColor
			);
		} break;

		case Ui::SimulationControl::PAUSE: {
			const float thickness = 5.f;

			DrawRectangleV({ mFgMin.x, mFgMin.y }, { thickness, mFgArea.y }, mFgColor);
			DrawRectangleV({ mFgMax.x - thickness, mFgMin.y }, { thickness, mFgArea.y }, mFgColor);
		} break;

		case Ui::SimulationControl::STEP: {
			DrawTriangle(
				mFgMin,
				{ mFgMin.x, mFgMax.y }, 
				{ mFgMax.x, (mFgMin.y + mFgMax.y) / 2.f },
				mFgColor
			);

			const float thickness = 5.f;
			DrawRectangleV({ mFgMax.x - thickness, mFgMin.y }, { thickness, mFgArea.y }, mFgColor);
		} break;
	}
}

void Ui::Button_Simulation::ReconstructButton() {
	Ui::Button::ReconstructButton();

	const int minPad = static_cast<int>(std::min(sizeX * 0.1f, sizeY * 0.1f));
	mBgRect = Rectangle{
		.x = static_cast<float>(posX + minPad),
		.y = static_cast<float>(posY + minPad),
		.width = static_cast<float>(sizeX - minPad * 2),
		.height = static_cast<float>(sizeY - minPad * 2),
	};

	const int fgPad = minPad * 3;
	mFgMin = {
		static_cast<float>(posX + fgPad),
		static_cast<float>(posY + fgPad)
	};

	mFgMax = {
		static_cast<float>(posX + sizeX - fgPad),
		static_cast<float>(posY + sizeY - fgPad)
	};

	mFgArea = {
		mFgMax.x - mFgMin.x,
		mFgMax.y - mFgMin.y
	};
}
