#include <Game/Player.hpp>

using namespace tv;

void Player::setX(float x) {
    _x = x;
}

void Player::setY(float y) {
    _y = y;
}

void Player::setAngle(float angle) {
    _angle = angle;
}

float Player::getX() {
    return _x;
}

float Player::getY() {
    return _y;
}

float Player::getAngle() {
    return _angle;
}

void Player::update() {
    float speed = 0.5f;

    float xD = sin(360 - _angle * RADIAN) * speed;
    float yD = cos(360 - _angle * RADIAN) * speed;
    float xsD = sin(360 - (_angle + 90.f) * RADIAN) * speed;
    float ysD = cos(360 - (_angle + 90.f) * RADIAN) * speed;
    if (InputManager::isPerformed("forward")) {
        _x += xD;
        _y += yD;
    }

    if (InputManager::isPerformed("back")) {
        _x -= xD;
        _y -= yD;
    }

    if (InputManager::isPerformed("left")) {
        _x -= xsD;
        _y -= ysD;
    }

    if (InputManager::isPerformed("right")) {
        _x += xsD;
        _y += ysD;
    }

    if (InputManager::isPerformed("turnLeft")) {
        _angle -= 1.f;
    }

    if (InputManager::isPerformed("turnRight")) {
        _angle += 1.f;
    }
}
