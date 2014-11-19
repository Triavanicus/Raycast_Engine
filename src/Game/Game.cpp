#include <Game/Game.hpp>

using namespace tv;

Game::Game(SDL_Window* window, SDL_Renderer* renderer): _renderer(renderer), _window(window) {
    _pixels = new Uint32[WIDTH*HEIGHT];
    _screen = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);

    run();
}

Game::~Game() {
    SDL_DestroyTexture(_screen);
    _screen = nullptr;
    delete _pixels;
    _pixels = nullptr;
}

void Game::run() {

    float delta = 0.f;
    Uint32 then = SDL_GetTicks();
    const float tups = 1000.f / 60.f;

    Uint32 last = SDL_GetTicks();

    int ups = 0;
    int fps = 0;

    SDL_Event e;
    while(_running) {
        Uint32 now = SDL_GetTicks();
        delta += static_cast<float>(now - then) / tups;
        then = now;

        while(SDL_PollEvent(&e) != 0) {
            switch(e.type) {
                case SDL_QUIT:
                    _running = false;
                    break;
                default:
                    break;
            }
        }

        while(delta >= 1.f) {
            update();
            ups++;

            delta -= 1.f;
        }
        render();
        fps++;

        if (last + 1000 <= SDL_GetTicks()) {
            std::cout << "ups: " << ups << ", fps: " << fps << "\n";
            ups = 0; fps = 0;
            last += 1000;
        }
    }
}

void Game::update() {

    _updates++;
}

void Game::render() {
    SDL_RenderClear(_renderer);

    for(int i = 0, iEND = WIDTH*HEIGHT; i < iEND; i++) {
        _pixels[i] = i + _updates;
    }
    SDL_UpdateTexture(_screen, nullptr, _pixels, WIDTH*sizeof(Uint32));

    SDL_RenderCopy(_renderer, _screen, nullptr, nullptr);
    SDL_RenderPresent(_renderer);
}
