#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <SDL.h>
#include <math.h>

#include "gfx/Color.hpp"
#include "InputManager.hpp"
#include "Player.hpp"

#define HEIGHT 720
#define HALF_HEIGHT 360
#define WIDTH 1280
#define TEXTURE_WIDTH 32
#define TEXTURE_HEIGHT 32

namespace tv {
    class Game {
    public:
        Game(SDL_Window* window, SDL_Renderer* renderer);
        ~Game();

        static int map[16][16];
    private:
        SDL_Renderer* _renderer;
        SDL_Window* _window;

        SDL_Texture* _screen;
        bool _running { true };

        void run();
        void update();
        void render();

        inline void drawPoint(int x, int y, Color color);
        inline void drawLine(int x1, int y1, int x2, int y2, Color color);
        inline void drawRect(int x, int y, int width, int height, Color color);
        inline void fillRect(int x, int y, int width, int height, Color color);

        inline void drawCircle(int n_cx, int n_cy, int radius, Color color);
        inline void fillCircle(int cx, int cy, int radius, Color color);

        void castRays(Player player);

        Player _player;

        int _updates { 0 };
    };
}
