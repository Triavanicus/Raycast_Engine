#pragma once

#include <math.h>
#include <iostream>

#include "InputManager.hpp"

namespace tv {
    class Player {
    public:
        Player(double x, double y, double dirX, double dirY, double planeX, double planeY) : _x(x), _y(y), _dirX(dirX), _dirY(dirY), _planeX(planeX), _planeY(planeY) {}
        ~Player() {}

        void setX(double x);
        void setY(double y);
        void setLocation(double x, double y);

        void setDirX(double dirX);
        void setDirY(double dirY);
        void setDirection(double dirX, double dirY);

        void setPlaneX(double planeX);
        void setPlaneY(double planeY);
        void setPlane(double planeX, double planeY);

        void setMap(int map[16][16]);

        double getX();
        double getY();

        double getDirX();
        double getDirY();

        double getPlaneX();
        double getPlaneY();

        void update();

    private:
        int _map[16][16];

        double _x;
        double _y;

        double _dirX;
        double _dirY;

        double _planeX;
        double _planeY;
    };
}
