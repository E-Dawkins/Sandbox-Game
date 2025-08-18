#include "core/game.h"

int main() {
    Core::Game game{};

    game.Init();

    while (game.IsRunning()) {
        game.Update();
        game.Draw();
    }

    game.Shutdown();
    
    return 0;
}