#include "instance.h"
#include <stdlib.h>
#include <time.h>

Instance::Instance(){
    this->screen_width  = 400;
    this->screen_height = 400;
    
    this->id = 1;
    this->status = INSTANCE_INIT;
    this->difficulty = INSTANCE_EASY;
    this->rounds_max = 5;
    this->r = this->g = this->b = this->a = 0x00;
}

Instance::Instance(int screen_width, int screen_height, int id, int difficulty, int rounds_max){
    this->screen_width  = screen_width;
    this->screen_height = screen_height;
    
    this->id = id;
    this->status = INSTANCE_INIT;
    this->difficulty = difficulty;
    this->rounds_max = rounds_max;
    this->r = this->g = this->b = this->a = 0x00;

}

void Instance::set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

int Instance::get_status(){
    return this->status;
}

void Instance::start(){

    // Preparando os parâmetris
    this->round_counter  = 1;
    this->gravity        = -1;
    this->air_resistance = 0;
    this->wind_force     = 0;

    // Gerando cor aleatória
    this->r = rand()%0xFF + 0x33;
    this->g = rand()%0xFF + 0x33;
    this->b = rand()%0xFF + 0x33;

    // Preparando os objetos
    this->cannon     = Cannon(20, this->screen_height-30, 50, 30);
    this->cannon.set_color(this->r, this->g, this->b, this->a);
    
    this->projectile = cannon.shot_projectile(rand()%50, rand()%50, 45);
    this->projectile.set_color(this->r, this->g, this->b, this->a);
    
    this->enemy = Enemy(this->screen_width-(rand()%700)-60, this->screen_height-60, 40, 60);
    this->enemy.set_color(this->r, this->g, this->b, this->a);

    // Atualizando o status do jogo
    this->status = INSTANCE_RUNNING;

}

void Instance::render(SDL_Renderer* renderer, bool update ){
        
        // Verificando se esse é um dos frames de atualização
        if(update && this->status == INSTANCE_RUNNING){
            int acel_x = this->air_resistance + this->wind_force;
            int acel_y = this->gravity;

            this->projectile.update_position();
            this->projectile.update_velocity(acel_x, acel_y);
        }

        // Desenhando os objetos da cena
        this->cannon.render( renderer );
        this->enemy.render( renderer );
        this->projectile.render( renderer );

        // Se o projétil atinge o chão passa para a proxima rodada ou finaliza o jogo
        if(this->projectile.pos_y >= this->screen_height || this->projectile.pos_x >= this->screen_width){
            
            this->round_counter += 1;

            if(this->round_counter > this->rounds_max){
                this->status = INSTANCE_FINISHED;
            } else {
                this->enemy = Enemy(this->screen_width-(rand()%700)-60, this->screen_height-60, 40, 60);
                this->enemy.set_color(this->r, this->g, this->b, this->a);

                this->projectile = cannon.shot_projectile(rand()%50, rand()%50, 45);
                this->projectile.set_color(this->r, this->g, this->b, this->a);
            }
        }

}