#include "core/game.h"

#include <raylib.h>

#include <format>

void Core::Game::Init() {
	InitWindow(800, 600, "Sandbox Game");
	SetWindowState(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(24); // this has no effect on the simulation, just makes it look nicer

	mParticleSize = 10;
	mRows = GetRenderHeight() / mParticleSize;
	mCols = GetRenderWidth() / mParticleSize;

	// This is temporary
	SetWindowTitle(std::format("Sandbox Game | SpawnStatic:{}", mSpawnStatic).c_str());
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

		SpawnParticlesInRadius(mousePosX, mousePosY, 3, (mSpawnStatic ? GREEN : RED));
	}

	// Remove particles
	if (IsMouseButtonPressed(1)) {
		Vector2 mousePos = GetMousePosition();

		const int mousePosX = static_cast<int>(mousePos.x) / mParticleSize;
		const int mousePosY = static_cast<int>(mousePos.y) / mParticleSize;

		RemoveParticlesInRadius(mousePosX, mousePosY, 3);
	}

	// Switch between static and falling particles
	if (IsKeyPressed(KEY_S)) {
		mSpawnStatic = !mSpawnStatic;

		SetWindowTitle(std::format("Sandbox Game | SpawnStatic:{}", mSpawnStatic).c_str());
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
	p.isStatic = mSpawnStatic;

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

void Core::Game::SpawnParticlesInRadius(int _posX, int _posY, int _radius, Color _col) {
	const int radiusSquared = _radius * _radius;
	for (int y = -_radius; y <= _radius; y++) {
		for (int x = -_radius; x <= _radius; x++) {
			// Outside circle radius
			if ((x * x) + (y * y) > radiusSquared) {
				continue;
			}

			const int offsetX = _posX + x;
			const int offsetY = _posY + y;

			if (IsInScreenBounds(offsetX, offsetY)) {
				AddParticleToSystem(offsetX, offsetY, _col);
			}
		}
	}
}

void Core::Game::RemoveParticlesInRadius(int _posX, int _posY, int _radius) {
	const int radiusSquared = _radius * _radius;
	for (int y = -_radius; y <= _radius; y++) {
		for (int x = -_radius; x <= _radius; x++) {
			// Outside circle radius
			if ((x * x) + (y * y) > radiusSquared) {
				continue;
			}

			const int offsetX = _posX + x;
			const int offsetY = _posY + y;

			if (IsInScreenBounds(offsetX, offsetY)) {
				RemoveParticleFromSystem(offsetX, offsetY);
			}
		}
	}
}
