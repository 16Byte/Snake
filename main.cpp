#include "raylib.h"
#include <deque>
#include "raymath.h"
#include <iostream>
#include "Global.hpp"
#include "Game.hpp"
#include "Snake.hpp"
#include "Food.hpp"

using namespace std;

Game Init()
{
    InitWindow(2 * Game::borderSize + Game::cellSize * Game::cellCount, 2 * Game::borderSize + Game::cellSize * Game::cellCount, "Snake");
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
    ClearBackground(Global::backgroundColor);

    DrawRectangleLinesEx(Rectangle{(float)Game::borderSize - 5, (float)Game::borderSize - 5, (float)Game::cellSize * Game::cellCount + 10, (float)Game::cellSize * Game::cellCount + 10}, 5, Global::snakeColor);
    
    DrawText("Snake Clone by Navi", Game::borderSize - 5, 20, 40, Global::snakeColor);
    DrawText(TextFormat("Score: %i", game.score), Game::borderSize - 5, Game::borderSize + Game::cellSize * Game::cellCount + 10, 40, Global::snakeColor);
}

void Update(Game& game)
{
    DrawWindow(game);

    if(game.running)
        UpdateMusicStream(Global::easyAndNormalModeMusic);

    if(Global::EventTriggered(0.2))
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
