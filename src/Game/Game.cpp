#include "Game.hpp"

using namespace tv;

int Game::map[16][16] = {
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 1, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 1, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

Game::Game(SDL_Window* window, SDL_Renderer* renderer) : _renderer(renderer), _window(window), _player(5, 5, -1, 0, 0, 0.66) {
    _screen = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
    _player.setMap(map);
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
    InputManager::addAction("map", SDLK_f);

    float delta = 0.f;
    Uint32 then = SDL_GetTicks();
    Uint32 lastUpdate = SDL_GetTicks();
    const float tups = 1000.f / 60.f;

    Uint32 last = SDL_GetTicks();

    int ups = 0;
    int fps = 0;

    SDL_Event e;

    float tlf = 0.f;
    float tlu = 0.f;
    while (_running) {
        Uint32 now = SDL_GetTicks();
        tlf = static_cast<float>(now - then);
        delta += tlf / tups;
        tlf /= 1000.f;
        then = now;

        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    _running = false;
                    break;
                default:
                    break;
            }

            InputManager::update(&e);
        }

        while (delta >= 1.f) {
            Uint32 thisUpdate = SDL_GetTicks();
            if (thisUpdate - lastUpdate != 0)
                tlu = 1000 / (thisUpdate - lastUpdate);
            lastUpdate = thisUpdate;
            update();
            ups++;

            delta -= 1.f;
        }
        render();
        fps++;

        if (last + 50 <= SDL_GetTicks()) {
            std::ostringstream message;
            float tfsp = 1.0 / tlf;
            message << std::fixed << std::setprecision(5) << "ups: " << tlu << ", fps: " << (1.0 / tlf);
            SDL_SetWindowTitle(_window, message.str().c_str());
            message.clear();
            ups = 0; fps = 0;
            last += 50;
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

    fillRect(0, 0, WIDTH, HALF_HEIGHT, 0x65AEF7FF);
    fillRect(0, HALF_HEIGHT, WIDTH, HALF_HEIGHT, 0x777777FF);

    castRays(_player);
    if (InputManager::isPerformed("map")) {
        Color c = 0x00000066;
        fillRect(0, 0, 257, 257, c);

        for (int y = 0; y < 16; y++) {
            for (int x = 0; x < 16; x++) {
                Color color = 0;
                switch (map[x][y]) {
                    case 1:
                        color = 0xff000066;
                        break;
                    case 2:
                        color = 0x00ff0066;
                        break;
                    case 3:
                        color = 0x0000ff66;
                        break;
                    default:
                        color = 0x00000066;
                }
                fillRect(x * 16, y * 16, 16, 16, color);
            }

            fillCircle(_player.getX() * 16, _player.getY() * 16, 8, 0x00000066);
            drawCircle(_player.getX() * 16, _player.getY() * 16, 8, 0xffffff66);
        }
    }
    fillRect(WIDTH / 2 - 1, HALF_HEIGHT - 12, 2, 24, 0xffffffff);
    fillRect(WIDTH / 2 - 12, HALF_HEIGHT - 1, 24, 2, 0xffffffff);

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

void Game::drawCircle(int n_cx, int n_cy, int radius, Color color) {
    double error = static_cast<double>(-radius);
    double x = static_cast<double>(radius) -0.5;
    double y = static_cast<double>(0.5);
    double cx = static_cast<double>(n_cx) -0.5;
    double cy = static_cast<double>(n_cy) -0.5;

    struct Points {
        std::vector<SDL_Point> v;
        SDL_Point p;
        void add(int x, int y) { p.x = x; p.y = y; v.push_back(p); }
        SDL_Point* get() { return &v[0]; }
        int size() { return v.size(); }
    };

    Points points;

    while (x >= y) {
        points.add(cx + x, cy + y);
        points.add(cx + y, cy + x);

        if (x != 0) {
            points.add(cx - x, cy + y);
            points.add(cx + y, cy - x);
        }

        if (y != 0) {
            points.add(cx + x, cy - y);
            points.add(cx - y, cy + x);
        }

        if (x != 0 && y != 0) {
            points.add(cx - x, cy - y);
            points.add(cx - y, cy - x);
        }

        error += y;
        ++y;
        error += y;

        if (error >= 0) {
            --x;
            error -= x;
            error -= x;
        }
    }

    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoints(_renderer, points.get(), points.size());
}

void Game::fillCircle(int cx, int cy, int radius, Color color) {
    struct Points {
        std::vector<SDL_Point> v;
        SDL_Point p;
        void add(int x, int y) { p.x = x; p.y = y; v.push_back(p); }
        SDL_Point* get() { return &v[0]; }
        int size() { return v.size(); }
    };
    Points points;

    double r = static_cast<double>(radius);

    for (double dy = 1; dy < r; dy += 1.0) {
        double dx = floor(sqrt((2.0*r*dy) - (dy*dy)));
        int x = cx - dx;
        int y1 = cy + r - dy;
        int y2 = cy - r + dy;

        for (; x <= cx + dx; x++) {
            points.add(x, y1);
            points.add(x, y2);
        }
    }

    for (int x = cx - radius; x < cx + radius; x++) {
        points.add(x, cy);
    }

    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoints(_renderer, points.get(), points.size());
}

void Game::drawLine(int x1, int y1, int x2, int y2, Color color) {
    SDL_SetRenderDrawColor(_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(_renderer, x1, y1, x2, y2);
}

void Game::castRays(Player player) {
    for (int x = 0; x < WIDTH; x++) {
        double cameraX = 2 * x / double(WIDTH) - 1;
        double rayPosX = player.getX();
        double rayPosY = player.getY();
        double rayDirX = player.getDirX() + player.getPlaneX()*cameraX;
        double rayDirY = player.getDirY() + player.getPlaneY()*cameraX;

        int mapX = int(rayPosX);
        int mapY = int(rayPosY);

        double sideDistX;
        double sideDistY;

        double deltaDistX = sqrt(1 + (rayDirY*rayDirY) / (rayDirX*rayDirX));
        double deltaDistY = sqrt(1 + (rayDirX*rayDirX) / (rayDirY*rayDirY));
        double perpWallDist;

        int stepX;
        int stepY;

        int hit = 0;
        int side;

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (rayPosX - mapX)*deltaDistX;
        }
        else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - rayPosX)*deltaDistX;
        }

        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (rayPosY - mapY)*deltaDistY;
        }
        else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - rayPosY)*deltaDistY;
        }

        while (hit == 0) {
            if (sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }

            if (map[mapX][mapY] > 0) hit = 1;
        }

        if (side == 0) perpWallDist = fabs((mapX - rayPosX + (1 - stepX) / 2) / rayDirX);
        else perpWallDist = fabs((mapY - rayPosY + (1 - stepY) / 2) / rayDirY);

        int lineHeight = abs(int(HEIGHT / perpWallDist));

        int drawStart = -lineHeight / 2 + HALF_HEIGHT;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + HALF_HEIGHT;
        if (drawEnd >= HEIGHT)drawEnd = HEIGHT - 1;

        Color color = 0;
        switch (map[mapX][mapY]) {
            case 1: color = 0xff0000ff; break;
            case 2: color = 0x00ff00ff; break;
            case 3: color = 0x0000ffff; break;
        }

        int darkness = perpWallDist * 12.8;
        if (darkness > 255) darkness = 255;

        color.r -= darkness;
        color.g -= darkness;
        color.b -= darkness;

        if (side == 1) {
            color.r /= 2;
            color.g /= 2;
            color.b /= 2;
        }
        if (color.r < 0) color.r = 0;
        if (color.g < 0) color.g = 0;
        if (color.b < 0) color.b = 0;
        drawLine(x, drawStart, x, drawEnd, color);
    }
}
