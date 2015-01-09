#include <Game/InputManager.hpp>

using namespace tv;

std::vector<Action> InputManager::_actions;

void Action::setKeyCode(Uint32 keycode) {
    _keycode = keycode;
}

Uint32 Action::getKeyCode() {
    return _keycode;
}

std::string Action::getName() {
    return _name;
}

bool Action::getIsActive() {
    return _isActive;
}

void Action::setIsActive(bool status) {
    _isActive = status;
}

void InputManager::update(SDL_Event* event) {
    // Check every keycode to see if it is currently being pressed
    bool u = false, d = false;
    u = event->type == SDL_KEYUP;
    d = event->type == SDL_KEYDOWN;

    if (u || d) {
        for (std::vector<Action>::iterator it = _actions.begin(); it != _actions.end(); ++it) {
            if ((*it).getKeyCode() == event->key.keysym.sym) {
                (*it).setIsActive(d);
            }
        }
    }
}

void InputManager::addAction(std::string actionName, Uint32 keycode) {
    Action act(actionName, keycode);
    _actions.push_back(act);
}

void InputManager::setAction(std::string actionName, Uint32 keycode) {
    for (std::vector<Action>::iterator it = _actions.begin(); it != _actions.end(); ++it) {
        if ((*it).getName() == actionName) {
            (*it).setKeyCode(keycode);
            return;
        }
    }

    addAction(actionName, keycode);
}

void InputManager::removeAction(std::string actionName) {
    for (std::vector<Action>::iterator it = _actions.begin(); it != _actions.end(); ++it) {
        if ((*it).getName() == actionName) {
            _actions.erase(it);
        }
    }
}

bool InputManager::isPerformed(std::string actionName) {
    for (std::vector<Action>::iterator it = _actions.begin(); it != _actions.end(); ++it) {
        if ((*it).getName() == actionName) {
            return (*it).getIsActive();
        }
    }

    return false;
}
