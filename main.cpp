#include <ctime>
#include <deque>
#include <raylib.h>
#include <raymath.h>

Color green{173, 204, 96, 255};
Color darkGreen{43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;

double lastUpdateTime = 0;

bool EventTriggered(const double interval)
{
    const double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

class Snake
{
public:

    std::deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1,0};

    void Draw() const
    {
        for (const auto [x, y]: body)
        {
            const auto segment = Rectangle{x * cellSize, y * cellSize, cellSize, cellSize};
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }

    void Update()
    {
        body.pop_back();
        body.push_front(Vector2Add(body[0], direction));
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
        if(EventTriggered(0.2))
        {
            snake.Update();
        }

        BeginDrawing();
        ClearBackground(green);

        food.Draw();
        snake.Draw();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
