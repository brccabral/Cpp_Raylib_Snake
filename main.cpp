#include <ctime>
#include <deque>
#include <raylib.h>

Color green{173, 204, 96, 255};
Color darkGreen{43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;

class Snake
{
public:

    std::deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};

    void Draw() const
    {
        for (const auto [x, y]: body)
        {
            const auto segment = Rectangle{x * cellSize, y * cellSize, cellSize, cellSize};
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }
};

class Food
{
public:

    Food()
    {
        const Image image = LoadImage("resources/Graphics/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos();
    }
    ~Food()
    {
        UnloadTexture(texture);
    }

    Vector2 position{5, 6};

    void Draw() const
    {
        DrawTexture(texture, position.x * cellSize, position.y * cellSize, WHITE);
    }

    static Vector2 GenerateRandomPos()
    {
        const float x = GetRandomValue(0, cellCount - 1);
        const float y = GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }

private:

    Texture2D texture{};
};

int main()
{
    InitWindow(750, 750, "Snake");
    SetTargetFPS(60);
    SetRandomSeed(time(nullptr));

    Food food;
    Snake snake;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(green);

        food.Draw();
        snake.Draw();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
