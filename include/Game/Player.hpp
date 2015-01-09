#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP

#include <math.h>
#include <iostream>

#include <Game/InputManager.hpp>

namespace tv {
    class Player {
      public:
        Player(float x, float y, float angle): _x(x), _y(y), _angle(angle) {}
        ~Player() {}

        const float FOV { 60.f };
        const int height { 32 };

        void setX(float x);
        void setY(float y);
        void setAngle(float angle);
        float getX();
        float getY();
        float getAngle();

        void update();

      private:
        float _x;
        float _y;
        float _angle;
    };
}

#endif // GAME_PLAYER_HPP
