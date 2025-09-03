#pragma once

#include "ui/button.h"

#include <memory>
#include <raylib.h>
#include <string>
#include <vector>

namespace Core {
	enum class ParticleState;
}

namespace Ui {
	class Button_Category : public Button {
	private:
		Rectangle mBgRect;
		Color mBgColor;

		Vector2 mTextPos;
		int mStateIndex;

		std::vector<std::unique_ptr<Ui::Button>> mChildButtons;

		typedef std::function<void(std::string)> ParticleButtonCallback;
		ParticleButtonCallback mParticleButtonCallback;

		bool mExpanded;
		bool mAnyChildrenHovered;

	public:
		Button_Category(int _posX, int _posY, int _sizeX, int _sizeY, Core::ParticleState _stateCategory, ParticleButtonCallback _callback);

		bool Update(const Vector2 _mousePos) override;
		void Draw() override;

		bool IsHovered() const override;

		void ReconstructButton() override;

	private:
		void ClickCallback();
		void InitialiseChildButtons(Core::ParticleState _stateCategory);
	};
}