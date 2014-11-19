#ifndef GAME_GAME_HPP
#define GAME_GAME_HPP


#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

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

        Uint32* _pixels;

        void run();
        void update();
        void render();

        int _updates { 0 };

    };
}


#endif // GAME_GAME_HPP
