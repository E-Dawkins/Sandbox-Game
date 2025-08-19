#include "core/game.h"

#include <raylib.h>

void Core::Game::Init() {
	InitWindow(800, 600, "Sandbox Game");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(24); // this has no effect on the simulation, just makes it look nicer

	mParticleSize = 10;
	mRows = GetRenderHeight() / mParticleSize;
	mCols = GetRenderWidth() / mParticleSize;
}

void Core::Game::Update() {
	ProcessInput();

	for (const auto& p : mParticles) {
		p->PreCalculateMove(*this);
	}

	for (const auto& p : mParticles) {
		p->TickPhysics(*this);
	}
}

void Core::Game::Draw() {
	BeginDrawing();
		ClearBackground(BLACK);
		for (const auto& p : mParticles) {
			p->Draw();
		}
	EndDrawing();
}

void Core::Game::Shutdown() {
	CloseWindow();
}

bool Core::Game::IsRunning() const {
	return !WindowShouldClose();
}

const std::shared_ptr<Core::Particle> Core::Game::GetParticleAtPosition(int _x, int _y) const {
	for (const auto& p : mParticles) {
		if (p->posX == _x && p->posY == _y) {
			return p;
		}
	}

	return nullptr;
}

bool Core::Game::IsInScreenBounds(int _x, int _y) const {
	return _x >= 0 && _x < mCols && _y >= 0 && _y < mRows;
}

void Core::Game::ProcessInput() {
	// Spawn particles
	if (IsMouseButtonPressed(0)) {
		Vector2 mousePos = GetMousePosition();

		const int mousePosX = static_cast<int>(mousePos.x) / mParticleSize;
		const int mousePosY = static_cast<int>(mousePos.y) / mParticleSize;

		SpawnParticlesInSquare(mousePosX - 3, mousePosX + 3, mousePosY - 3, mousePosY + 3, RED);
	}

	// Remove particles
	if (IsMouseButtonPressed(1)) {
		Vector2 mousePos = GetMousePosition();

		const int mousePosX = static_cast<int>(mousePos.x) / mParticleSize;
		const int mousePosY = static_cast<int>(mousePos.y) / mParticleSize;

		RemoveParticlesInSquare(mousePosX - 3, mousePosX + 3, mousePosY - 3, mousePosY + 3);
	}
}

void Core::Game::AddParticleToSystem(int _posX, int _posY, Color _col) {
	if (GetParticleAtPosition(_posX, _posY) != nullptr) {
		return;
	}
	
	Core::Particle p;
	p.posX = _posX;
	p.posY = _posY;
	p.size = mParticleSize;
	p.color = _col;

	mParticles.emplace_back(std::make_shared<Core::Particle>(p));
}

void Core::Game::RemoveParticleFromSystem(int _posX, int _posY) {
	auto& p = GetParticleAtPosition(_posX, _posY);
	
	if (p == nullptr) {
		return;
	}

	auto itr = std::find(mParticles.begin(), mParticles.end(), p);
	if (itr != mParticles.end()) {
		mParticles.erase(itr);
	}
}

void Core::Game::SpawnParticlesInSquare(int _minX, int _maxX, int _minY, int _maxY, Color _col) {
	for (int x = _minX; x <= _maxX; x++) {
		for (int y = _minY; y <= _maxY; y++) {
			if (IsInScreenBounds(x, y)) {
				AddParticleToSystem(x, y, _col);
			}
		}
	}
}

void Core::Game::RemoveParticlesInSquare(int _minX, int _maxX, int _minY, int _maxY) {
	for (int x = _minX; x <= _maxX; x++) {
		for (int y = _minY; y <= _maxY; y++) {
			if (IsInScreenBounds(x, y)) {
				RemoveParticleFromSystem(x, y);
			}
		}
	}
}
