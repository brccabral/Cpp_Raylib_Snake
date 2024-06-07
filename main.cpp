#include <ctime>
#include <deque>
#include <raylib.h>
#include <raymath.h>

Color green{173, 204, 96, 255};
Color darkGreen{43, 51, 24, 255};

int cellSize = 30;
int cellCount = 25;
int offset = 75;

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

bool ElementInDeque(const Vector2 element, const std::deque<Vector2> &deque)
{
    for (const Vector2 segment: deque)
    {
        if (Vector2Equals(segment, element))
        {
            return true;
        }
    }
    return false;
}

class Snake
{
public:

    Snake()
    {
        Reset();
    }

    std::deque<Vector2> body{};
    Vector2 direction{};
    bool addSegment{};

    void Draw() const
    {
        for (const auto [x, y]: body)
        {
            const auto cs = static_cast<float>(cellSize);
            const auto segment = Rectangle{x * cs + offset, y * cs + offset, cs, cs};
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);
        }
    }

    void Update()
    {
        if (addSegment)
        {
            addSegment = false;
        }
        else
        {
            body.pop_back();
        }
        body.push_front(Vector2Add(body[0], direction));
    }
    void Reset()
    {
        body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
        direction = {1, 0};
        addSegment = false;
    }
};

class Food
{
public:

    explicit Food(const std::deque<Vector2> &snakeBody)
    {
        const Image image = LoadImage("resources/Graphics/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos(snakeBody);
    }
    ~Food()
    {
        UnloadTexture(texture);
    }

    Vector2 position{5, 6};

    void Draw() const
    {
        DrawTexture(texture, position.x * cellSize + offset, position.y * cellSize + offset, WHITE);
    }

    static Vector2 GenerateRandomPos(const std::deque<Vector2> &snakeBody)
    {
        Vector2 newPos = {};
        do
        {
            const float x = GetRandomValue(0, cellCount - 1);
            const float y = GetRandomValue(0, cellCount - 1);
            newPos = {x, y};
        }
        while (ElementInDeque(newPos, snakeBody));
        return newPos;
    }

private:

    Texture2D texture{};
};

class Game
{
public:

    Snake snake{};
    Food food = Food(snake.body);
    bool running = true;
    int score = 0;

    void Draw() const
    {
        snake.Draw();
        food.Draw();
    }

    void Update()
    {
        if (running)
        {
            snake.Update();
            CheckCollisionWithFood();
            CheckCollisionWithEdges();
            if (CheckCollisionWithTail())
            {
                GameOver();
            }
        }
    }

    void HandleInput()
    {
        if (IsKeyPressed(KEY_UP) && snake.direction.y != 1)
        {
            snake.direction = {0, -1};
            running = true;
        }
        if (IsKeyPressed(KEY_DOWN) && snake.direction.y != -1)
        {
            snake.direction = {0, 1};
            running = true;
        }
        if (IsKeyPressed(KEY_LEFT) && snake.direction.x != 1)
        {
            snake.direction = {-1, 0};
            running = true;
        }
        if (IsKeyPressed(KEY_RIGHT) && snake.direction.x != -1)
        {
            snake.direction = {1, 0};
            running = true;
        }
    }

    void CheckCollisionWithFood()
    {
        if (Vector2Equals(snake.body[0], food.position))
        {
            food.position = Food::GenerateRandomPos(snake.body);
            snake.addSegment = true;
            ++score;
        }
    }

    void CheckCollisionWithEdges()
    {
        const auto [x, y] = snake.body[0];
        if (x == cellCount || x == -1)
        {
            GameOver();
        }
        if (y == cellCount || y == -1)
        {
            GameOver();
        }
    }

    [[nodiscard]] bool CheckCollisionWithTail() const
    {
        std::deque<Vector2> headless = snake.body;
        headless.pop_front();

        return ElementInDeque(snake.body[0], headless);
    }

    void GameOver()
    {
        snake.Reset();
        food.position = Food::GenerateRandomPos(snake.body);
        running = false;
        score = 0;
    }
};

int main()
{
    InitWindow(cellSize * cellCount + 2 * offset, cellSize * cellCount + 2 * offset, "Snake");
    SetTargetFPS(60);
    SetRandomSeed(time(nullptr));

    Game game{};

    while (!WindowShouldClose())
    {
        if (EventTriggered(0.2))
        {
            game.Update();
        }

        game.HandleInput();

        BeginDrawing();
        ClearBackground(green);
        DrawRectangleLinesEx(
                Rectangle{offset - 5, offset - 5, cellSize * cellCount + 10, cellSize * cellCount + 10}, 5, darkGreen);
        DrawText("Snake", offset - 5, 20, 40, darkGreen);
        DrawText(TextFormat("%i", game.score), offset - 5, offset + cellSize * cellCount + 10, 40, darkGreen);

        game.Draw();

        EndDrawing();
    }
    CloseWindow();
    return 0;
}
