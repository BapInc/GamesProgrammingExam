#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include <memory>
#include "GameObject.hpp"
class GameState
{
public:
    GameState();

    virtual void update() = 0;
    virtual void render() = 0;
    virtual void start() = 0;

private:

};

#endif