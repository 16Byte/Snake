#include "Food.hpp"
#include "Snake.hpp"
#include "Global.hpp"
#include "raylib.h"
#include "raymath.h"
#include "Game.hpp"
#include <deque>

using namespace std;

Game::Game()
{
    InitAudioDevice();

    Global::easyAndNormalModeMusic = LoadMusicStream("Sounds/Music/Breaking News by SAKUMAMATATA.mp3");
    PlayMusicStream(Global::easyAndNormalModeMusic);
    SetMusicVolume(Global::easyAndNormalModeMusic, .25f);
}

Game::~Game()
{
    UnloadSound(consumptionSound);
    UnloadSound(deathSound);
    CloseAudioDevice();
}

void Game::Draw()
{
    food.Draw();
    snake.Draw();
}

void Game::Update()
{
    if(running)
    {
        snake.Update();
        CheckCollisionWithFood();
        CheckCollisionWithEdges();
        CheckCollisionWithTail();
    }
}

void Game::CheckCollisionWithFood()
{
    if(Vector2Equals(snake.body[0], food.position))
    {
        food.position = food.GenerateRandomPos(snake.body);
        snake.addSegment = true;
        score++;
        PlaySound(consumptionSound);
    }
}

void Game::CheckCollisionWithEdges()
{
    if((snake.body[0].x == cellCount || snake.body[0].x == -1) || snake.body[0].y == cellCount || snake.body[0].y == -1)
        GameOver();
}

void Game::CheckCollisionWithTail()
{
    deque<Vector2> headlessBody = snake.body; //when we rewrite this, make the body body and the head head. Instead of body[0] for head or having to write variables like headlessBody
    headlessBody.pop_front();

    if(Global::ElementInDeque(snake.body[0], headlessBody))
        GameOver();
}

void Game::GameOver()
{
    snake.Reset();
    food.position = food.GenerateRandomPos(snake.body);
    running = false;
    score = 0;
    PlaySound(deathSound);
}