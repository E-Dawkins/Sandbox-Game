#pragma once

#include "ui/button.h"

namespace Ui {
	enum class SimulationControl {
		PLAY,
		PAUSE,
		STEP,

		COUNT
	};

	class Button_Simulation : public Button {
	private:
		Ui::SimulationControl mControlType;

		Color mBgColor;
		Rectangle mBgRect;

		Color mFgColor;
		Vector2 mFgMin, mFgMax, mFgArea;

	public:
		Button_Simulation(int _posX, int _posY, int _sizeX, int _sizeY, Ui::SimulationControl _controlType, ButtonCallback _callback);

		void Draw() override;
		void ReconstructButton() override;
	};
}