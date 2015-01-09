#ifndef GAME_INPUTMANAGER_HPP
#define GAME_INPUTMANAGER_HPP

#include <vector>
#include <string>
#include <SDL2/SDL.h>

namespace tv {
    class Action {
        public:
            Action(std::string action, Uint32 keycode) : _name(action), _keycode(keycode), _isActive(false) {}
            void setKeyCode(Uint32 keycode);
            Uint32 getKeyCode();
            std::string getName();
            bool getIsActive();
            void setIsActive(bool status);
        private:
            std::string _name;
            Uint32 _keycode;
            bool _isActive;
    };

    class InputManager {
        public:
            static void update(SDL_Event* event);
            static void addAction(std::string actionName, Uint32 keycode);
            static void setAction(std::string actionName, Uint32 keycode);
            static void removeAction(std::string actionName);
            static bool isPerformed(std::string actionName);

        private:
            static std::vector<Action> _actions;
    };
}

#endif // GAME_INPUTMANAGER_HPP
