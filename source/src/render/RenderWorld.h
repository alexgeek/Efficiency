#ifndef GAME_RENDERWORLD_H
#define GAME_RENDERWORLD_H

#include "../Game.h"

class RenderWorld
{
public:
    RenderWorld(Game* game);
    ~RenderWorld();

    void Render();
};

#endif //GAME_RENDERWORLD_H
