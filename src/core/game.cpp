#include "core/game.h"

#include <raylib.h>

void Core::Game::Init() {
	InitWindow(800, 600, "Sandbox Game");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
}

void Core::Game::Update() {
	
}

void Core::Game::Draw() {
	BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Sandbox Game!", 350, 280, 20, DARKGRAY);
	EndDrawing();
}

void Core::Game::Shutdown() {
	CloseWindow();
}

bool Core::Game::IsRunning() const {
	return !WindowShouldClose();
}
