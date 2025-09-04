#include "core/game.h"

#include <format>
#include <raylib.h>

#include "core/particle_defines.h"
#include "core/raylib_helpers.h"
#include "ui/button_category.h"
#include "ui/button_simulation.h"

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

	if (mIsSimulating || mShouldStep) {
		for (const auto& p : mParticles) {
			p->TickPhysics(*this);
		}

		mShouldStep = false;
	}
}

void Core::Game::Draw() {
	BeginDrawing();
		ClearBackground(BLACK);
		for (const auto& p : mParticles) {
			p->Draw();
		}

		if (!mHoveringAnyButton) {
			const int mousePosX = static_cast<int>(GetMouseX()) / mParticleSize;
			const int mousePosY = static_cast<int>(GetMouseY()) / mParticleSize;

			ApplyFuncInRadius(mSpawnRadius, [&](int _x, int _y) {
				DrawRectangleLines((mousePosX + _x) * mParticleSize, (mousePosY + _y) * mParticleSize, mParticleSize, mParticleSize, MAGENTA);
			});
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
	// Category buttons
	auto particleButtonCallback = [&](std::string _s) { mTypeToSpawn = _s; };
	mButtons.emplace_back(std::make_unique<Ui::Button_Category>(10, 10, 75, 40, Core::ParticleState::SOLID, particleButtonCallback));
	mButtons.emplace_back(std::make_unique<Ui::Button_Category>(10, 80, 75, 40, Core::ParticleState::LIQUID, particleButtonCallback));
	mButtons.emplace_back(std::make_unique<Ui::Button_Category>(10, 150, 75, 40, Core::ParticleState::GAS, particleButtonCallback));

	// Simulation controls
	const int startX = GetRenderWidth() - 60;
	mButtons.emplace_back(std::make_unique<Ui::Button_Simulation>(startX, 10, 50, 50, Ui::SimulationControl::PLAY, [&]() { mIsSimulating = true; }));
	mButtons.emplace_back(std::make_unique<Ui::Button_Simulation>(startX, 70, 50, 50, Ui::SimulationControl::PAUSE, [&]() { mIsSimulating = false; }));
	mButtons.emplace_back(std::make_unique<Ui::Button_Simulation>(startX, 130, 50, 50, Ui::SimulationControl::STEP, [&]() { mShouldStep = true; }));
}

void Core::Game::ProcessInput() {
	// Spawn particles
	if (!mMouseInputConsumed && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		const int mousePosX = static_cast<int>(GetMouseX()) / mParticleSize;
		const int mousePosY = static_cast<int>(GetMouseY()) / mParticleSize;

		ApplyFuncInRadius(mSpawnRadius, [&](int _x, int _y) {
			AddParticleToSystem(mousePosX + _x, mousePosY + _y, mTypeToSpawn);
		});
	}

	// Remove particles
	if (!mMouseInputConsumed && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
		const int mousePosX = static_cast<int>(GetMouseX()) / mParticleSize;
		const int mousePosY = static_cast<int>(GetMouseY()) / mParticleSize;

		ApplyFuncInRadius(mSpawnRadius, [&](int _x, int _y) {
			RemoveParticleFromSystem(mousePosX + _x, mousePosY + _y);
		});
	}

	// Increase / decrease spawn radius
	mSpawnRadius += CLAMP(static_cast<int>(GetMouseWheelMove()), -1, 1);
	mSpawnRadius = CLAMP(mSpawnRadius, 0, 5); // completely arbitrary max radius value
}

void Core::Game::AddParticleToSystem(int _posX, int _posY, std::string _type) const {
	if (!IsInScreenBounds(_posX, _posY)) {
		return;
	}

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

void Core::Game::ReplaceParticleAtPos(int _posX, int _posY, std::string _type) const {
	RemoveParticleFromSystem(_posX, _posY);
	AddParticleToSystem(_posX, _posY, _type);
}

void Core::Game::ApplyFuncInRadius(int _r, std::function<void(int, int)> _f) {
	const int radiusSquared = _r * _r;
	for (int x = -_r; x <= _r; x++) {
		for (int y = -_r; y <= _r; y++) {
			if ((x * x) + (y * y) <= radiusSquared) {
				_f(x, y);
			}
		}
	}
}
