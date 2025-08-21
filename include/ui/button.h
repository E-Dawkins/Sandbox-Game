#pragma once

#include <functional>
#include <raylib.h>

namespace Ui {
	class Button {
	public:
		int posX, posY;
		int sizeX, sizeY;

		bool isActive = true;

	protected:
		bool mIsHovered = false;

		Rectangle mAreaRect;

		typedef std::function<void()> ButtonCallback;
		ButtonCallback mCallback;

	public:
		Button(int _posX, int _posY, ButtonCallback _callback);
		Button(int _posX, int _posY, int _sizeX, int _sizeY, ButtonCallback _callback);

		// @returns Whether the button has 'consumed' a mouse click
		virtual bool Update(const Vector2 _mousePos);
		virtual void Draw();
	};
}