#include <raylib.h>

Color green{173, 204, 96, 255};
Color darkGreen{43, 51, 24, 255};

int main()
{
    InitWindow(750, 750, "Snake");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(green);

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
