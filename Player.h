#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <vector>
#include "Constants.h"

class Player {
public:
    float x, y;
    float old_x, old_y;

    float width, height;

    bool onGround;
    int jumpCount;
    const int MAX_JUMPS = 2;

    float gravity;
    float jumpV0;
    float runSpeed;
    float friction;

    float targetJumpHeight;
    float targetJumpDist;

    Player(float startX, float startY);

    void update(float dt, const Uint8* keyState);

    void handleInput(const SDL_Event& e);

    void resolveCollision(const std::vector<Rect>& platforms);

    void render(SDL_Renderer* renderer, int camX, int camY);

private:
    void recalculatePhysics();
    void jump();
};

#endif