#pragma once
#include "raylib.h"
#include "Snake.hpp"
#include "Food.hpp"

class Game
{
    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void CheckCollisionWithFood();
        void CheckCollisionWithEdges();
        void CheckCollisionWithTail();
        void GameOver();
        Snake snake = Snake();
        Food food = Food(snake.body);
        const static int cellSize = 30;
        const static int cellCount = 25;
        const static int borderSize = 75; //border size
        int score = 0;
        bool running = true;
        Sound consumptionSound = LoadSound("Sounds/SFX/Consumption 1.wav");
        Sound deathSound = LoadSound("Sounds/SFX/Death (from Galaga).wav");
        
};