#pragma once

#include "ui/button.h"

#include <string>

namespace Ui {
	class Button_Labeled : public Button {
	private:
		std::string mLabel;
		Vector2 mLabelPos;

		Color mBgColor;
		Rectangle mBgRect;

	public:
		Button_Labeled(int _posX, int _posY, int _sizeX, int _sizeY, std::string _label, ButtonCallback _callback);

		void Draw() override;
		void ReconstructButton() override;
	};
}