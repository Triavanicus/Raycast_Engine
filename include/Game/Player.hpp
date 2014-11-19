#ifndef GAME_PLAYER_HPP
#define GAME_PLAYER_HPP



namespace tv {
    class Player {
    public:
        Player(float x, float y): _x(x), _y(y) {}
        ~Player() {}

        const float FOV = 60.f;

        void setX(float x);
        void setY(float y);
        void setZ(float z);
        float getX();
        float getY();
        float getZ();

    private:
        float _x;
        float _y;
    };
}



#endif // GAME_PLAYER_HPP
