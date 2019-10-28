#include "enemy.h"

Enemy::Enemy(){
    this->pos_x = 0;
    this->pos_y = 0;
    this->width = 40;
    this->height = 60;
    this->vel_x  = 0;
    this->g = this->b = this->a = 0x00;
    this->r = 0xFF;
}

Enemy::Enemy(int pos_x, int pos_y, int width, int height){
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->width = width;
    this->height = height;
    this->vel_x  = 0;
    this->g = this->b = this->a = 0x00;
    this->r = 0xFF;
}

Enemy::Enemy(int pos_x, int pos_y, int width, int height, int vel_x){
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    this->width = width;
    this->height = height;
    this->vel_x  = vel_x;
    this->g = this->b = this->a = 0x00;
    this->r = 0xFF;
}

void Enemy::set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

// Verifica se houve colisão de um objeto com outro.
bool Enemy::check_colission(){
    return false;
}

void Enemy::update_position(){
    this->pos_x -= this->vel_x;
}

void Enemy::update_velocity(int acel_x){
    this->vel_x -= acel_x;
}

void Enemy::render(SDL_Renderer* renderer){
    SDL_Rect fillRect = { this->pos_x, this->pos_y, this->width, this->height };
	SDL_SetRenderDrawColor( renderer, this->r, this->g, this->b, this->a );		
	SDL_RenderFillRect( renderer, &fillRect );
}