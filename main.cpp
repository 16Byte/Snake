#include "raylib.h"
#include <deque>
#include "raymath.h"
#include <iostream>

using namespace std;

Color snakeColor = RAYWHITE;
Color foodColor = RED;
Color backgroundColor = Color{ 40, 40, 40, 255};

// 25 * 30 = 750; thus 750x750 grid
int cellSize = 30;
int cellCount = 25;
int borderSize = 75; //border size

Music easyAndNormalModeMusic;

double lastUpdateTime = 0;

bool ElementInDeque(Vector2 element, deque<Vector2> deque)
{
    for (unsigned int i = 0; i < deque.size(); i++)
        if(Vector2Equals(deque[i], element))
            return true;
    return false;
}

bool eventTriggered(double interval)
{
    double currentTime = GetTime();

    if(currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

class Snake
{
    public:
        deque<Vector2> body = { Vector2{6,9}, Vector2{5,9}, Vector2{4,9} };
        Vector2 direction = {1, 0};
        bool addSegment = false;

        void Draw()
        {
            for(unsigned int i = 0; i < body.size(); i++)
            {
                float x = body[i].x;
                float y = body[i].y;
                Rectangle segment = Rectangle{(borderSize + x * cellSize), (borderSize + y * cellSize), (float)cellSize, (float)cellSize};
                DrawRectangleRounded(segment, 0.5, 6, snakeColor);
            }
        }

        void Update()
        {
            body.push_front(Vector2Add(body[0], direction));

            if(addSegment == true)
                addSegment = false;
            else
                body.pop_back();
        }

        void Reset() //randomize this later
        {
            SeekMusicStream(easyAndNormalModeMusic, 0.0f);

            body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
            direction = {1, 0};
        }
};

class Food
{
    public:
        Vector2 position;
        Texture2D texture;

        Food(deque<Vector2> snakeBody)
        {
            Image image = LoadImage("Graphics/Sprites/Food_Cherry.png");
            texture = LoadTextureFromImage(image);
            UnloadImage(image);
            position = GenerateRandomPos(snakeBody);
        }

        ~Food()
        {
            UnloadTexture(texture);
        }

        void Draw()
        {
            DrawTexture(texture, borderSize + position.x * cellSize, borderSize + position.y * cellSize, WHITE);
        }

        Vector2 GenerateRandomCell()
        {
            float x = GetRandomValue(0, cellCount - 1);
            float y = GetRandomValue(0, cellCount - 1);

            return Vector2{x, y};
        }

        Vector2 GenerateRandomPos(deque<Vector2> snakeBody)
        {
            Vector2 position = GenerateRandomCell();

            while(ElementInDeque(position, snakeBody))
                position = GenerateRandomCell();

            return position;
        }
};

class Game
{
    public:
        Snake snake = Snake();
        Food food = Food(snake.body);

        int score = 0;

        bool running = true;

        Sound consumptionSound;
        Sound deathSound;
        
        //Music hardModeMusic; //TODO

        Game()
        {
            InitAudioDevice();
            consumptionSound = LoadSound("Sounds/SFX/Consumption 1.wav");
            deathSound = LoadSound("Sounds/SFX/Death (from Galaga).wav");

            easyAndNormalModeMusic = LoadMusicStream("Sounds/Music/Breaking News by SAKUMAMATATA.mp3");
            PlayMusicStream(easyAndNormalModeMusic);
            SetMusicVolume(easyAndNormalModeMusic, .25f);
        }

        ~Game()
        {
            UnloadSound(consumptionSound);
            UnloadSound(deathSound);
            CloseAudioDevice();
        }

        void Draw()
        {
            food.Draw();
            snake.Draw();
        }

        void Update()
        {
            if(running)
            {
                snake.Update();
                CheckCollisionWithFood();
                CheckCollisionWithEdges();
                CheckCollisionWithTail();
            }
        }

        void CheckCollisionWithFood()
        {
            if(Vector2Equals(snake.body[0], food.position))
            {
                food.position = food.GenerateRandomPos(snake.body);
                snake.addSegment = true;
                score++;
                PlaySound(consumptionSound);
            }
        }

        void CheckCollisionWithEdges()
        {
            if((snake.body[0].x == cellCount || snake.body[0].x == -1) || snake.body[0].y == cellCount || snake.body[0].y == -1)
                GameOver();
        }

        void CheckCollisionWithTail()
        {
            deque<Vector2> headlessBody = snake.body; //when we rewrite this, make the body body and the head head. Instead of body[0] for head or having to write variables like headlessBody
            headlessBody.pop_front();

            if(ElementInDeque(snake.body[0], headlessBody))
                GameOver();
        }

        void GameOver()
        {
            snake.Reset();
            food.position = food.GenerateRandomPos(snake.body);
            running = false;
            score = 0;
            PlaySound(deathSound);
        }
};

Game Init()
{
    InitWindow(2 * borderSize + cellSize * cellCount, 2 * borderSize + cellSize * cellCount, "Snake");
    SetTargetFPS(165);
    Game game = Game();
    return game;
}

void GetInput(Game& game)
{
    if((IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) && game.snake.direction.y != 1)
    {
        //up
        game.running = true;
        game.snake.direction = {0, -1};
    }
    else if((IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) && game.snake.direction.y != -1)
    {
        //down
        game.running = true;
        game.snake.direction = {0, 1};
    }
    else if((IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) && game.snake.direction.x != 1)
    {
        //left
        game.running = true;
        game.snake.direction = {-1, 0};
    }
    else if((IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) && game.snake.direction.x != -1)
    {
        //right
        game.running = true;
        game.snake.direction = {1, 0};
    }
}

void DrawWindow(Game& game)
{
    BeginDrawing();
    ClearBackground(backgroundColor);

    DrawRectangleLinesEx(Rectangle{(float)borderSize - 5, (float)borderSize - 5, (float)cellSize*cellCount+10, (float)cellSize*cellCount+10}, 5, snakeColor);
    
    DrawText("Snake Clone by Navi", borderSize - 5, 20, 40, snakeColor);
    DrawText(TextFormat("Score: %i", game.score), borderSize - 5, borderSize + cellSize * cellCount + 10, 40, snakeColor);
}

void Update(Game& game)
{
    DrawWindow(game);

    if(game.running)
        UpdateMusicStream(easyAndNormalModeMusic);

    if(eventTriggered(0.2))
        game.Update();

    GetInput(game);

    game.Draw();
    EndDrawing();
}

int main() 
{
    Game game = Init();

    while(WindowShouldClose() == false) 
        Update(game);

    CloseWindow();

    return 0;
}
