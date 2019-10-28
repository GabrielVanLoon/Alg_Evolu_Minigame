#include "projectile.h"

Projectile::Projectile(){
    this->pos_x  = 0;
    this->pos_y  = 0;
    this->radius = 10;
    this->vel_x = this->vel_y = 0;
    this->r = this->g = this->b = this->a = 0x00;
}

Projectile::Projectile(int pos_x, int pos_y, int radius, int vel_x, int vel_y){
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->radius = radius;
    this->vel_x = vel_x;
    this->vel_y = -vel_y;
    this->r = this->g = this->b = this->a = 0x00;
}

void Projectile::set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

void Projectile::update_position(){
    this->pos_x += this->vel_x;
    this->pos_y += this-> vel_y;
}

void Projectile::update_velocity(int acel_x, int acel_y){
    this->vel_x += acel_x;
    this->vel_y -= acel_y;
}

void Projectile::render(SDL_Renderer* renderer){
    SDL_Rect fillRect = { this->pos_x-(this->radius/2), this->pos_y-(this->radius/2), this->radius, this->radius };
	SDL_SetRenderDrawColor( renderer, this->r, this->g, this->b, this->a );		
	SDL_RenderFillRect( renderer, &fillRect );
}