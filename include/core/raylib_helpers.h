#pragma once

#include <raylib.h>
#include <cmath>

namespace Core {
	namespace Raylib_Helpers {
		#define CLAMP(x, minVal, maxVal) std::max(minVal, std::min(maxVal, x))

		Color RandomOffsetColor(Color _original, int _offset) {
			const int randomOffset = GetRandomValue(-_offset, _offset);

			_original.r = static_cast<unsigned char>(CLAMP(_original.r + randomOffset, 0, 255));
			_original.g = static_cast<unsigned char>(CLAMP(_original.g + randomOffset, 0, 255));
			_original.b = static_cast<unsigned char>(CLAMP(_original.b + randomOffset, 0, 255));
			
			return _original;
		}
	}
}