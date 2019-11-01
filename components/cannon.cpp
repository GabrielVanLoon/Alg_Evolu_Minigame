#include "cannon.h"

Cannon::Cannon(){
    this->pos_x = this->pos_y = 0;
    this->width = this->height = 60;
    this->r = this->g = this->b = this->a = 0x00;
}

Cannon::Cannon(int pos_x, int pos_y, int width, int height){
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->width = width;
    this->height = height;
    this->r = this->g = this->b = this->a = 0x00;
}

void Cannon::set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

int Cannon::get_enemy_distance(const Enemy &e){
    return e.pos_x - this->pos_x;
}

Projectile Cannon::shot_projectile(int vel_x, int vel_y, int degrees){
    int pos_x = this->pos_x + (this->width/2);
    int pos_y = this->pos_y + (this->height/2);
    int radius = 10;
    
    return Projectile(pos_x, pos_y, radius, vel_x, vel_y);
}

void Cannon::render(SDL_Renderer* renderer){
    SDL_Rect fillRect = { this->pos_x, this->pos_y, this->width, this->height };
	SDL_SetRenderDrawColor( renderer, this->r, this->g, this->b, this->a );		
	SDL_RenderFillRect( renderer, &fillRect );
}