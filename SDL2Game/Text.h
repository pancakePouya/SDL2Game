#pragma once
#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

class Text {
private:
    SDL_Texture* texture = nullptr; 
    int width = 0;                 
    int height = 0;                 

public:
    std::string value;             
    int x, y;                      


    Text();
    Text(std::string val, int startX, int startY);


    void Update(TTF_Font* font, SDL_Color color, SDL_Renderer* renderer);
    void Render(SDL_Renderer* renderer);
};