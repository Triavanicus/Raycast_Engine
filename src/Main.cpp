
#include <iostream>
#include <SDL2/SDL.h>

#define HEIGHT 720
#define WIDTH 1280
#define TITLE "This is a game"

bool init();

int main(int argc, char* args[])
{
    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize: " << SDL_GetError() << "\n";
        return 1;
    }

    window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT,
                              SDL_WINDOW_SHOWN);

    if(window == nullptr)
    {
        std::cout << "Window could not be created: " << SDL_GetError() << "\n";
        return 1;
    }

    screenSurface = SDL_GetWindowSurface(window);
    SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format,
                                                 0x00,
                                                 0x00,
                                                 0x00
    ));

    SDL_UpdateWindowSurface(window);
    SDL_Delay(2000);

    return 0;
}

bool init()
{

    return true;
}
