#include <SDL.h>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Constants.h"
#include "Player.h"

void addPlatform(std::vector<Rect>& platforms, float x, float y, float w, float h) {
    platforms.push_back({x, y, w, h});
}

int main(int argc, char* argv[]) {
    srand(static_cast<unsigned int>(time(nullptr)));

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
            "Zadanie 12: Icy Tower - Parametry Skoku",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN
    );

    if (!window) return 1;
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    std::vector<Rect> platforms;

    float floorY = SCREEN_HEIGHT - 50;
    addPlatform(platforms, -100, floorY, SCREEN_WIDTH + 200, 100);

    float testLevelY = floorY - 150;
    addPlatform(platforms, 50, testLevelY, 200, 20);
    addPlatform(platforms, 450, testLevelY, 300, 20);

    addPlatform(platforms, -50, -10000, 50, 10000 + SCREEN_HEIGHT);
    addPlatform(platforms, SCREEN_WIDTH, -10000, 50, 10000 + SCREEN_HEIGHT);

    float currentY = testLevelY - 150;
    int platformCount = 100;
    for (int i = 0; i < platformCount; ++i) {
        float pWidth = 150 + (rand() % 150);
        float pX = 50 + (rand() % (SCREEN_WIDTH - 100 - (int)pWidth));
        addPlatform(platforms, pX, currentY, pWidth, 20);
        float gap = 120 + (rand() % 50);
        currentY -= gap;
    }

    Player player(SCREEN_WIDTH / 2.0f, floorY - 50);

    bool running = true;
    SDL_Event event;

    float accumulator = 0.0f;
    Uint32 lastTime = SDL_GetTicks();

    std::cout << "========================================" << std::endl;
    std::cout << "                ICY TOWER               " << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "STEROWANIE:" << std::endl;
    std::cout << "  [W] / [Spacja] : Skok" << std::endl;
    std::cout << "  [A] / [D]      : Ruch lewo/prawo" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "REGULACJA PARAMETROW SKOKU (w konsoli):" << std::endl;
    std::cout << "  [U] / [J] : Zwieksz / Zmniejsz WYSOKOSC skoku" << std::endl;
    std::cout << "  [I] / [K] : Zwieksz / Zmniejsz ZASIEG skoku (czas do szczytu)" << std::endl;
    std::cout << "========================================" << std::endl;

    while (running) {
        Uint32 currentTime = SDL_GetTicks();
        float frameTime = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        if (frameTime > 0.25f) frameTime = 0.25f;
        accumulator += frameTime;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
            player.handleInput(event);
        }

        const Uint8* keyState = SDL_GetKeyboardState(nullptr);

        while (accumulator >= TIME_STEP) {
            player.update(TIME_STEP, keyState);
            player.resolveCollision(platforms);
            accumulator -= TIME_STEP;
        }

        // Kamera
        int targetCamY = static_cast<int>(player.y) - SCREEN_HEIGHT / 2 + 100;
        int maxCamY = static_cast<int>(floorY) - SCREEN_HEIGHT + 50;
        if (targetCamY > maxCamY) targetCamY = maxCamY;

        int camX = 0;
        int camY = targetCamY;

        SDL_SetRenderDrawColor(renderer, 20, 20, 40, 255);
        SDL_RenderClear(renderer);

        for (const auto& p : platforms) {
            if (p.y - camY < SCREEN_HEIGHT && p.y + p.h - camY > 0) {
                SDL_Rect r = {
                        static_cast<int>(p.x - camX),
                        static_cast<int>(p.y - camY),
                        static_cast<int>(p.w),
                        static_cast<int>(p.h)
                };

                if (p.y == testLevelY) SDL_SetRenderDrawColor(renderer, 255, 200, 50, 255);
                else if (p.y == floorY) SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
                else if (p.h > 1000) SDL_SetRenderDrawColor(renderer, 50, 50, 70, 255);
                else SDL_SetRenderDrawColor(renderer, 100, 200, 255, 255);

                SDL_RenderFillRect(renderer, &r);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 100);
                SDL_RenderDrawRect(renderer, &r);
            }
        }

        player.render(renderer, camX, camY);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}