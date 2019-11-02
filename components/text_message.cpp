#include "text_message.h"

TextMessage::TextMessage(std::string str, int pos_x, int pos_y, int width, int height){
    this->font = TTF_OpenFont("Sans.ttf", 24);
    this->color = {51, 51, 51};
    this->str = str;
    this->surface = TTF_RenderText_Solid(this->font, this->str.c_str(), this->color);
    
    this->Message_rect.x = pos_x;
    this->Message_rect.y = pos_y;
    this->Message_rect.w = width;
    this->Message_rect.h = height;
}

void TextMessage::render(SDL_Renderer* renderer){
    this->texture = SDL_CreateTextureFromSurface(renderer, this->surface);
    SDL_RenderCopy(renderer, this->texture, NULL, &(this->Message_rect));
}