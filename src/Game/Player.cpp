#include "Player.hpp"

using namespace tv;
void Player::setX(double x) { _x = x; }
void Player::setY(double y) { _y = y; }
void Player::setLocation(double x, double y) { _x = x; _y = y; }

void Player::setDirX(double dirX) { _dirX = dirX; }
void Player::setDirY(double dirY) { _dirY = dirY; }
void Player::setDirection(double dirX, double dirY) { _dirX = dirX; _dirY = dirY; }

void Player::setPlaneX(double planeX) { _planeX = planeX; }
void Player::setPlaneY(double planeY) { _planeY = planeY; }
void Player::setPlane(double planeX, double planeY) { _planeX = planeX; _planeY = planeY; }

void Player::setMap(int map[16][16]) {
    for (int x = 0; x < 16; x++) {
        for (int y = 0; y < 16; y++) {
            _map[x][y] = map[x][y];
        }
    }
}

double Player::getX() { return _x; }
double Player::getY() { return _y; }

double Player::getDirX() { return _dirX; }
double Player::getDirY() { return _dirY; }

double Player::getPlaneX() { return _planeX; }
double Player::getPlaneY() { return _planeY; }

void Player::update() {
    double moveSpeed = 0.04;
    double rotSpeed = 0.02;

    if ((InputManager::isPerformed("forward") ^ InputManager::isPerformed("back")) && (InputManager::isPerformed("left") ^ InputManager::isPerformed("right"))) {
        moveSpeed /= 1.5;
    }

    if (InputManager::isPerformed("forward")) {
        double nx = _x + _dirX*moveSpeed;
        double ny = _y + _dirY*moveSpeed;
        if (_map[int(nx)][int(_y)] == false) _x = nx;
        if (_map[int(_x)][int(ny)] == false) _y = ny;
    }
    if (InputManager::isPerformed("back")) {
        double nx = _x - _dirX*moveSpeed;
        double ny = _y - _dirY*moveSpeed;
        if (_map[int(nx)][int(_y)] == false) _x = nx;
        if (_map[int(_x)][int(ny)] == false) _y = ny;
    }
    if (InputManager::isPerformed("left")) {
        double nx = _x - _planeX*moveSpeed;
        double ny = _y - _planeY*moveSpeed;
        if (_map[int(nx)][int(_y)] == false) _x = nx;
        if (_map[int(_x)][int(ny)] == false) _y = ny;
    }
    if (InputManager::isPerformed("right")) {
        double nx = _x + _planeX*moveSpeed;
        double ny = _y + _planeY*moveSpeed;
        if (_map[int(nx)][int(_y)] == false) _x = nx;
        if (_map[int(_x)][int(ny)] == false) _y = ny;
    }
    if (InputManager::isPerformed("turnLeft")) {
        double oldDirX = _dirX;
        _dirX = _dirX*cos(rotSpeed) - _dirY*sin(rotSpeed);
        _dirY = oldDirX * sin(rotSpeed) + _dirY*cos(rotSpeed);

        double oldPlaneX = _planeX;
        _planeX = _planeX * cos(rotSpeed) - _planeY*sin(rotSpeed);
        _planeY = oldPlaneX * sin(rotSpeed) + _planeY*cos(rotSpeed);
    }
    if (InputManager::isPerformed("turnRight")) {
        double oldDirX = _dirX;
        _dirX = _dirX*cos(-rotSpeed) - _dirY*sin(-rotSpeed);
        _dirY = oldDirX * sin(-rotSpeed) + _dirY*cos(-rotSpeed);

        double oldPlaneX = _planeX;
        _planeX = _planeX * cos(-rotSpeed) - _planeY*sin(-rotSpeed);
        _planeY = oldPlaneX * sin(-rotSpeed) + _planeY*cos(-rotSpeed);
    }
}
