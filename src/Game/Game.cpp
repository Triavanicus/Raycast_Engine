#include <Game/Game.hpp>

using namespace tv;

Game::Game(SDL_Window* window, SDL_Renderer* renderer): _renderer(renderer), _window(window), _player(50.f, 100.f, 45.f) {
    _screen = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
    run();
}

Game::~Game() {
    SDL_DestroyTexture(_screen);
    _screen = nullptr;
}

void Game::run() {
    //add actions
    InputManager::addAction("forward", SDLK_w);
    InputManager::addAction("back", SDLK_s);
    InputManager::addAction("left", SDLK_a);
    InputManager::addAction("right", SDLK_d);
    InputManager::addAction("turnLeft", SDLK_q);
    InputManager::addAction("turnRight", SDLK_e);

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

            InputManager::update(&e);
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
    _player.update();
    _updates++;
}

void Game::render() {
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderClear(_renderer);
    castRays(_player.getX(), _player.getY(), _player.getAngle(), _player.FOV, WIDTH);

    Color c(0x000000ff);
    fillRect(0, 0, 257, 257, c);

    for(int y = 0; y < 16; y++) {
        for(int x = 0; x < 16; x++) {
            Color* color = nullptr;
            switch(map[y][x]) {
                case 1:
                    color = new Color(0xff0000ff);
                    break;
                case 2:
                    color = new Color(0x00ff00ff);
                    break;
                case 3:
                    color = new Color(0x0000ffff);
                    break;
                default:
                    color =  new Color(0x000000ff);
            }
            drawRect(x << 4, y << 4, 16, 16, *color);
            delete color;
            color = nullptr;
        }

        Color color(0xff00ffff);
        drawRect(_player.getX(), _player.getY(), 8, 8, color);
    }
    int px, py;
    px = _player.getX() + 4;
    py = _player.getY() + 4;
    float r1 = (_player.getAngle() - 30.f) * RADIAN;
    float r2 = (_player.getAngle() + 30.f) * RADIAN;
    drawLine(px, py, px + 200 * cos(r1), py + 200 * sin(r1), 0xa000a0);
    drawLine(px, py, px + 200 * cos(r2), py + 200 * sin(r2), 0xa000a0);

    SDL_RenderPresent(_renderer);
}

void Game::drawPoint(int x, int y, Color color) {
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(_renderer, x, y);
}

void Game::drawRect(int x, int y, int width, int height, Color color) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(_renderer, &rect);
}

void Game::fillRect(int x, int y, int width, int height, Color color) {
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(_renderer, &rect);
}

void Game::drawLine(int x1, int y1, int x2, int y2, Color color) {
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
}

void Game::castRays(int x, int y, float angle, float fov, int numRays) {
    float astep = fov / numRays;
    float start = angle - fov / 2.f;
    for(int i = 0; i < numRays; i++) {
        castRay(x, y, i * astep + start, i);
    }
}

void Game::castRay(int x, int y, float angle, int rayNum) {
    float px = _player.getX() + 4;
    float py = _player.getY() + 4;
    float length = 0;
    float r = angle * RADIAN;
    int nx, ny, i, c;
    i = 0;
    c = 0;
    for(;;c++) {
        nx = px + c * cos(r);
        ny = py + c * sin(r);
            i = getTile(nx, ny);
        if (i != 0) {
            float ax, ay;
            ax = px + c * cos(r);
            ay = py + c * sin(r);
            length = sqrt(((px - ax) * (px - ax)) + ((py - ay) * (py - ay)));
            break;
        }
    };
    Color* color = 0;
    switch(i) {
        case 1:
            color = new Color(0xff0000ff);
            break;
        case 2:
            color = new Color(0x00ff00ff);
            break;
        case 3:
            color = new Color(0x0000ffff);
            break;
        default:
            color = new Color(0x000000ff);
            break;
    }
    float distance = length * cos((360 - (_player.getAngle() - angle)) * RADIAN);
    int size = 64 / distance * 200;
    int startLoc = (HALF_HEIGHT - (size / 2));
    drawRect(rayNum, startLoc, 1, size, *color);
    color = new Color(distance - 10);
    drawRect(rayNum, startLoc, 1, size + 1, *color);
    delete color;
    color = nullptr;
}

int Game::getTile(int x, int y) {
    return map[y >> 4][x >> 4];
}
