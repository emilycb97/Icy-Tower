#include "Player.h"
#include <iostream>
#include <cmath>
#include <algorithm>

Player::Player(float startX, float startY) {
    x = startX;
    y = startY;
    old_x = startX;
    old_y = startY;

    width = 30;
    height = 30;

    onGround = false;
    jumpCount = 0;

    targetJumpHeight = 180.0f;
    targetJumpDist = 250.0f;
    runSpeed = 450.0f;
    friction = 0.92f;

    recalculatePhysics();
}

void Player::recalculatePhysics() {
    float speed = (runSpeed > 0) ? runSpeed : 1.0f;

    float timeToApex = targetJumpDist / speed;

    gravity = (2 * targetJumpHeight) / (timeToApex * timeToApex);
    jumpV0 = gravity * timeToApex;

    std::cout << "--- ZMIANA PARAMETROW SKOKU ---" << std::endl;
    std::cout << "Zadana Wysokosc (h): " << targetJumpHeight << std::endl;
    std::cout << "Zadana Odleglosc do szczytu (d): " << targetJumpDist << std::endl;
    std::cout << "Wynikowe Grawitacja (g): " << gravity << std::endl;
    std::cout << "Wynikowe Predkosc poczatkowa (v0): " << jumpV0 << std::endl;
    std::cout << "-----------------------------------" << std::endl;
}

void Player::jump() {
    old_y = y - (-jumpV0 * TIME_STEP);
    onGround = false;
    jumpCount++;
}

void Player::handleInput(const SDL_Event& e) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.keysym.sym == SDLK_SPACE || e.key.keysym.sym == SDLK_w || e.key.keysym.sym == SDLK_UP) {
            if (onGround) {
                jump();
            } else if (jumpCount < MAX_JUMPS) {
                jump();
            }
        }

        bool changed = false;
        if (e.key.keysym.sym == SDLK_u) { targetJumpHeight += 10; changed = true; }
        if (e.key.keysym.sym == SDLK_j) { targetJumpHeight = std::max(50.0f, targetJumpHeight - 10); changed = true; }

        if (e.key.keysym.sym == SDLK_i) { targetJumpDist += 10; changed = true; }
        if (e.key.keysym.sym == SDLK_k) { targetJumpDist = std::max(50.0f, targetJumpDist - 10); changed = true; }

        if (changed) recalculatePhysics();
    }
}

void Player::update(float dt, const Uint8* keyState) {
    float accelX = 0.0f;
    float accelY = gravity;

    if (keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT]) {
        accelX = -1.0f;
    }
    if (keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT]) {
        accelX = 1.0f;
    }

    if (!onGround && (keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_DOWN])) {
        accelY *= 3.0f;
    }

    bool holdingJump = keyState[SDL_SCANCODE_SPACE] || keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_UP];
    if ((y < old_y) && !holdingJump) {
        accelY *= 2.5f;
    }

    float tempX = x;
    float tempY = y;

    float vx = (x - old_x) / dt;
    vx *= friction;

    if (accelX != 0) {
        vx += accelX * (runSpeed * 10.0f) * dt;
        if (vx > runSpeed) vx = runSpeed;
        if (vx < -runSpeed) vx = -runSpeed;
    } else {
        if (std::abs(vx) < 10.0f) vx = 0;
    }

    x = x + vx * dt;
    y = 2 * y - old_y + accelY * dt * dt;

    old_x = tempX;
    old_y = tempY;
}

void Player::resolveCollision(const std::vector<Rect>& platforms) {
    onGround = false;

    for (const auto& p : platforms) {
        if (x < p.x + p.w && x + width > p.x &&
            y < p.y + p.h && y + height > p.y) {

            float overlapLeft = (x + width) - p.x;
            float overlapRight = (p.x + p.w) - x;
            float overlapTop = (y + height) - p.y;
            float overlapBottom = (p.y + p.h) - y;

            float minOverlap = std::min({overlapLeft, overlapRight, overlapTop, overlapBottom});

            if (minOverlap == overlapTop) {
                if ((y - old_y) > 0) {
                    y = p.y - height;
                    old_y = y;
                    onGround = true;
                    jumpCount = 0;
                }
            }
            else if (minOverlap == overlapBottom) {
                y = p.y + p.h;
                old_y = y;
            }
            else if (minOverlap == overlapLeft) {
                x = p.x - width;
                old_x = x;
            }
            else if (minOverlap == overlapRight) {
                x = p.x + p.w;
                old_x = x;
            }
        }
    }

    if (y > SCREEN_HEIGHT + 200) {
        x = SCREEN_WIDTH / 2.0f;
        y = SCREEN_HEIGHT - 100.0f;
        old_x = x;
        old_y = y;
        jumpCount = 0;
        std::cout << "Reset pozycji!" << std::endl;
    }
}

void Player::render(SDL_Renderer* renderer, int camX, int camY) {
    SDL_Rect r = {
            static_cast<int>(x - camX),
            static_cast<int>(y - camY),
            static_cast<int>(width),
            static_cast<int>(height)
    };

    SDL_SetRenderDrawColor(renderer, 255, 50, 50, 255);
    SDL_RenderFillRect(renderer, &r);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &r);
}