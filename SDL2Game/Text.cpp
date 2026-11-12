#include "Text.h"


Text::Text() {
    value = "";
    x = 0;
    y = 0;
}

Text::Text(std::string val, int startX, int startY) {
    value = val;
    x = startX;
    y = startY;
}


void Text::Update(TTF_Font* font, SDL_Color color, SDL_Renderer* renderer) {

    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }


    SDL_Surface* surface = TTF_RenderText_Solid(font, value.c_str(), color);
    if (surface) {

        texture = SDL_CreateTextureFromSurface(renderer, surface);


        width = surface->w;
        height = surface->h;

        SDL_FreeSurface(surface);
    }
}


void Text::Render(SDL_Renderer* renderer) {
    if (!texture) return; 


    SDL_Rect destRect = { x, y, width, height };


    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
}