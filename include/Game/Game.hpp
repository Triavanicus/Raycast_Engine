#ifndef GAME_GAME_HPP
#define GAME_GAME_HPP

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <math.h>

#include <Game/Player.hpp>
#include <Game/gfx/Color.hpp>
#include <Game/InputManager.hpp>

namespace tv {
    class Game {
      public:
        Game(SDL_Window* window, SDL_Renderer* renderer);
        ~Game();

      private:
        SDL_Renderer* _renderer;
        SDL_Window* _window;
        SDL_Texture* _screen;
        bool _running { true };
        float _angle{ 0.f };

        int map[16][16] = {
            { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
            { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
            { 1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1 },
            { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
            { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
            { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
            { 1,0,0,0,0,0,0,0,3,0,0,0,1,0,0,1 },
            { 1,0,0,0,0,0,0,0,2,0,0,0,0,0,0,1 },
            { 1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1 },
            { 1,0,0,0,0,0,0,1,2,0,0,0,0,0,0,1 },
            { 1,0,0,0,1,0,1,3,0,0,0,0,0,0,0,1 },
            { 1,0,0,0,0,1,2,0,0,0,0,0,0,0,0,1 },
            { 1,0,0,0,1,3,0,0,0,0,0,0,0,0,0,1 },
            { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
            { 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
            { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }
        };

        void run();
        void update();
        void render();
        inline void drawPoint(int x, int y, Color color);
        inline void drawLine(int x1, int y1, int x2, int y2, Color color);
        inline void drawRect(int x, int y, int width, int height, Color color);
        inline void fillRect(int x, int y, int width, int height, Color color);
        void castRays(int x, int y, float angle, float FOV, int numRays);
        void castRay(int x, int y, float angle, int rayNum);
        int getTile(int x, int y);
        Player _player;

        int _updates { 0 };
    };
}

#endif // GAME_GAME_HPP
