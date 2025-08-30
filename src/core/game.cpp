#include "core/game.h"

#include <format>
#include <raylib.h>

#include "core/particle_defines.h"
#include "core/raylib_helpers.h"
#include "ui/button_particle.h"

void Core::Game::Init() {
	InitWindow(800, 600, "Sandbox Game");
	SetTargetFPS(24); // this has no effect on the simulation, just makes it look nicer

	mParticleSize = 10;
	mRows = GetRenderHeight() / mParticleSize;
	mCols = GetRenderWidth() / mParticleSize;

	SetupButtons();
}

void Core::Game::Update() {
	const Vector2 mousePos = GetMousePosition();

	mMouseInputConsumed = false;
	mHoveringAnyButton = false;

	for (const auto& b : mButtons) {
		// Has any button consumed mouse input?
		if (b->Update(mousePos)) {
			mMouseInputConsumed = true;
		}

		// Are we hovering any button?
		if (b->IsHovered()) {
			mHoveringAnyButton = true;
		}
	}

	ProcessInput();

	for (const auto& p : mParticles) {
		p->TickPhysics(*this);
	}
}

void Core::Game::Draw() {
	BeginDrawing();
		ClearBackground(BLACK);
		if (!mHoveringAnyButton) {
			DrawSpawnRadius();
		}

		for (const auto& p : mParticles) {
			p->Draw();
		}

		for (const auto& b : mButtons) {
			b->Draw();
		}
	EndDrawing();
}

void Core::Game::Shutdown() {
	CloseWindow();
}

bool Core::Game::IsRunning() const {
	return !WindowShouldClose();
}

const std::unique_ptr<Core::Particle>& Core::Game::GetParticleAtPosition(int _x, int _y) const {
	for (const auto& p : mParticles) {
		if (p->posX == _x && p->posY == _y) {
			return p;
		}
	}

	// Probably not advised, but it does work
	static auto nullParticle = std::unique_ptr<Core::Particle>{};
	return nullParticle;
}

bool Core::Game::IsInScreenBounds(int _x, int _y) const {
	return _x >= 0 && _x < mCols && _y >= 0 && _y < mRows;
}

void Core::Game::SetupButtons() {
	// Particle selection buttons
	const int particleButtonSize = 50;
	const int particleButtonSpacing = 20;

	const int particleButtonCount = static_cast<int>(Core::gParticleTypes.size());
	const int particleButtonTotalWidth = (particleButtonSize * particleButtonCount) + ((particleButtonCount + 1) * particleButtonSpacing);
	const int particleButtonStartX = (GetRenderWidth() / 2) - (particleButtonTotalWidth / 2);

	int count = 0;
	for (const auto& pair : Core::gParticleTypes) {
		const int buttonX = particleButtonStartX + ((particleButtonSize + particleButtonSpacing) * count);

		Ui::Button_Particle ParticleButton = Ui::Button(buttonX, 20, 50, 50, [&]() { mTypeToSpawn = pair.first; });
		ParticleButton.SetParticleType(pair.first);
		mButtons.emplace_back(std::make_unique<Ui::Button_Particle>(ParticleButton));

		count++;
	}
}

void Core::Game::ProcessInput() {
	// Spawn particles
	if (!mMouseInputConsumed && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		Vector2 mousePos = GetMousePosition();

		const int mousePosX = static_cast<int>(mousePos.x) / mParticleSize;
		const int mousePosY = static_cast<int>(mousePos.y) / mParticleSize;

		SpawnParticlesInRadius(mousePosX, mousePosY, mSpawnRadius, mTypeToSpawn);
	}

	// Remove particles
	if (!mMouseInputConsumed && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
		Vector2 mousePos = GetMousePosition();

		const int mousePosX = static_cast<int>(mousePos.x) / mParticleSize;
		const int mousePosY = static_cast<int>(mousePos.y) / mParticleSize;

		RemoveParticlesInRadius(mousePosX, mousePosY, mSpawnRadius);
	}
}

void Core::Game::AddParticleToSystem(int _posX, int _posY, std::string _type) const {
	if (GetParticleAtPosition(_posX, _posY) != nullptr) {
		return;
	}
	
	auto p = Core::gParticleTypes[_type]();
	p->posX = _posX;
	p->posY = _posY;
	p->size = mParticleSize;
	p->color = Core::Raylib_Helpers::RandomOffsetColor(p->color, 20);

	mParticles.emplace_back(std::move(p));
}

void Core::Game::RemoveParticleFromSystem(int _posX, int _posY) const {
	auto& p = GetParticleAtPosition(_posX, _posY);
	
	if (p == nullptr) {
		return;
	}

	auto itr = std::find(mParticles.begin(), mParticles.end(), p);
	if (itr != mParticles.end()) {
		mParticles.erase(itr);
	}
}

void Core::Game::SpawnParticlesInRadius(int _posX, int _posY, int _radius, std::string _type) {
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
				AddParticleToSystem(offsetX, offsetY, _type);
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

void Core::Game::DrawSpawnRadius() {
	const Vector2 mousePos = GetMousePosition();
	const int mousePosX = static_cast<int>(mousePos.x) / mParticleSize;
	const int mousePosY = static_cast<int>(mousePos.y) / mParticleSize;

	const int radiusSquared = mSpawnRadius * mSpawnRadius;
	for (int y = -mSpawnRadius; y <= mSpawnRadius; y++) {
		for (int x = -mSpawnRadius; x <= mSpawnRadius; x++) {
			// Outside circle radius
			if ((x * x) + (y * y) > radiusSquared) {
				continue;
			}

			const int offsetX = mousePosX + x;
			const int offsetY = mousePosY + y;

			if (IsInScreenBounds(offsetX, offsetY)) {
				DrawRectangleLines(offsetX * mParticleSize, offsetY * mParticleSize, mParticleSize, mParticleSize, MAGENTA);
			}
		}
	}
}
