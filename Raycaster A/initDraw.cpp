#include "Draw.h"

Draw::Draw() {
    // sdl
    SDL_Init(SDL_INIT_EVERYTHING);
    // window
    win = SDL_CreateWindow(
        "Raycaster",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_RESIZABLE
    );
    srf = SDL_GetWindowSurface(win);
    render = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(render, 0, 0, 0, 0);

    if (!loadBitmaps()) printf("Failed to load bitmaps");
}
void Draw::quit() {
    // window
    SDL_FreeSurface(srf);
    srf = NULL;
    SDL_DestroyWindow(win);
    win = NULL;

    // loaded content
    SDL_DestroyTexture(wallsBMP);
    wallsBMP = NULL;

    SDL_DestroyTexture(spritesBMP);
    spritesBMP = NULL;

    SDL_Quit();
}

bool Draw::loadBitmaps() {
    SDL_Surface* loadSrf = NULL; // surface for loading bitmaps

    // load bitmaps
    loadSrf = SDL_LoadBMP("bitmaps/walls.bmp");
    wallsBMP = SDL_CreateTextureFromSurface(render, loadSrf);

    loadSrf = SDL_LoadBMP("bitmaps/sprites.bmp");
    spritesBMP = SDL_CreateTextureFromSurface(render, loadSrf);

    // close surface
    SDL_FreeSurface(loadSrf);
    loadSrf = NULL;

    // return status
    return wallsBMP != NULL;
}