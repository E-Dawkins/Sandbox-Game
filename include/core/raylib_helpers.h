#pragma once

#include <raylib.h>
#include <cmath>

namespace Core {
	namespace Raylib_Helpers {
		#define CLAMP(x, minVal, maxVal) std::max(minVal, std::min(maxVal, x))

		inline Color RandomOffsetColor(Color _original, int _offset) {
			const int randomOffset = GetRandomValue(-_offset, _offset);

			_original.r = static_cast<unsigned char>(CLAMP(_original.r + randomOffset, 0, 255));
			_original.g = static_cast<unsigned char>(CLAMP(_original.g + randomOffset, 0, 255));
			_original.b = static_cast<unsigned char>(CLAMP(_original.b + randomOffset, 0, 255));
			
			return _original;
		}

		inline void DrawTextCenteredEx(const char* _text, Vector2 _position, float _fontSize, float _spacing, Color _tint) {
			const int textWidth = MeasureText(_text, static_cast<int>(_fontSize));

			const Vector2 offsetPosition{
				.x = _position.x - textWidth / 2.f,
				.y = _position.y
			};

			DrawTextEx(GetFontDefault(), _text, offsetPosition, _fontSize, _spacing, _tint);
		}
	}
}