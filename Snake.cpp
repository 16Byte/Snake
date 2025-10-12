#include "raylib.h"
#include "raymath.h"
#include "Snake.hpp"
#include "Game.hpp"
#include "Global.hpp"

using namespace std;

void Snake::Draw()
{
    for(unsigned int i = 0; i < body.size(); i++)
    {
        float x = body[i].x;
        float y = body[i].y;
        Rectangle segment = Rectangle{(Game::borderSize + x * Game::cellSize), (Game::borderSize + y * Game::cellSize), (float)Game::cellSize, (float)Game::cellSize};
        DrawRectangleRounded(segment, 0.5, 6, Global::snakeColor);
    }
}

void Snake::Update()
{
    body.push_front(Vector2Add(body[0], direction));

    if(addSegment == true)
        addSegment = false;
    else
        body.pop_back();
}

void Snake::Reset() //randomize this later
{
    SeekMusicStream(Global::easyAndNormalModeMusic, 0.0f);

    body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
    direction = {1, 0};
}
