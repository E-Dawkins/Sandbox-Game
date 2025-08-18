#pragma once

namespace Core {
	class Game {
	public:
		void Init();
		
		void Update();
		void Draw();

		void Shutdown();

		// Helpers

		bool IsRunning() const;
	};
}