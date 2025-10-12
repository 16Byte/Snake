#include "raylib.h"
#include <deque>
#include "Food.hpp"
#include "Game.hpp"
#include "Global.hpp"

using namespace std;

Food::Food(deque<Vector2> snakeBody)
{
    Image image = LoadImage("Graphics/Sprites/Food_Cherry.png");
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
    position = GenerateRandomPos(snakeBody);
}

Food::~Food()
{
    UnloadTexture(texture);
}

void Food::Draw()
{
    DrawTexture(texture, Game::borderSize + position.x * Game::cellSize, Game::borderSize + position.y * Game::cellSize, WHITE);
}

Vector2 Food::GenerateRandomCell()
{
    float x = GetRandomValue(0, Game::cellCount - 1);
    float y = GetRandomValue(0, Game::cellCount - 1);

    return Vector2{x, y};
}

Vector2 Food::GenerateRandomPos(deque<Vector2> snakeBody)
{
    Vector2 position = GenerateRandomCell();

    while(Global::ElementInDeque(position, snakeBody))
        position = GenerateRandomCell();

    return position;
}