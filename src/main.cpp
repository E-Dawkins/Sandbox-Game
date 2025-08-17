#include <raylib.h>

int main() {
    InitWindow(800, 600, "Sandbox Game");
    
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Sandbox Game!", 350, 280, 20, DARKGRAY);
        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}