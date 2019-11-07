#include "instance.h"
#include <algorithm>
#include <vector>
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

    this->flag_randomSpawn = false;
}

Instance::Instance(int screen_width, int screen_height, int difficulty, int rounds_max, Population* pop, int id){
    this->screen_width  = screen_width;
    this->screen_height = screen_height;
    
    this->status = INSTANCE_INIT;
    this->difficulty = difficulty;
    this->rounds_max = rounds_max;
    this->r = this->g = this->b = this->a = 0x00;

    this->flag_randomSpawn = false;

    this->id  = id;
    this->pop = pop;
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

    //printf("Iniciando instância nº%d...\n", this->id);

    // Preparando os parâmetris
    this->round_counter  =  1;
    this->gravity        = -1.0;
    this->air_resistance =  0.0;
    this->wind_force     =  0.0;

    // Gerando cor aleatória
    this->r = rand()%0xFF + 0x22;
    this->g = rand()%0xFF + 0x22;
    this->b = rand()%0xFF + 0x22;

    // Zerando o Score da instância
    this->pop->ind[this->id].score = 0;

    // Preparando o canhão
    this->cannon = Cannon(20, this->screen_height-30, 50, 30);
    this->cannon.set_color(this->r, this->g, this->b, this->a);
    
    // Atualizando o status do jogo
    this->status = INSTANCE_WAITING;

}

void Instance::render(SDL_Renderer* renderer, bool update, bool atualizarIndividuos){
        
    // Verificando se esse é um dos frames de atualização
    if(this->status == INSTANCE_RUNNING && update){
        int acel_x = this->air_resistance + this->wind_force;
        int acel_y = this->gravity;

        this->projectile.update_position();
        this->projectile.update_velocity(acel_x, acel_y);
    }

    // Se o projétil atinge o alvo então pausa a instância
    if(this->status == INSTANCE_RUNNING && this->projectile.check_colission(this->enemy)){
        
        // Incrementa o contador de rodadas e calcula a loss
        this->round_counter += 1;
        this->pop->ind[this->id].score += 0;

        if(this->round_counter > this->rounds_max){
            this->status = INSTANCE_FINISHED;
        } else {
            this->status = INSTANCE_WAITING;
        }
    }

    // Se o projétil atinge o chão ou foge muito da largura passa para ou pausa a instância
    if(this->status == INSTANCE_RUNNING && (this->projectile.pos_y >= this->screen_height 
            || this->projectile.pos_x > 2*this->screen_width)){
        
        // Incrementa o contador de rodadas e calcula a loss
        this->round_counter += 1;

        if(this->projectile.pos_y >= this->screen_height)
            this->pop->ind[this->id].score += abs(this->projectile.pos_x - this->enemy.pos_x);
        else 
            this->pop->ind[this->id].score += 2*this->screen_width;

        if(this->round_counter > this->rounds_max){
            this->status = INSTANCE_FINISHED;
        } else {
            this->status = INSTANCE_WAITING;
        }
    }
            
    // Caso o usuário dê a permissão para iniciar uma nova rodada
    if(this->status == INSTANCE_WAITING){
        
        // Posicionando o inimigo
        if(this->flag_randomSpawn == true)
            this->enemy = Enemy(this->screen_width-(rand()%900)-60, this->screen_height-60, 40, 60);
        else
            this->enemy = Enemy(this->screen_width-(100*this->round_counter)-60, this->screen_height-60, 40, 60);
        this->enemy.set_color(this->r, this->g, this->b, this->a);

        // Utilizando a rede neurão para calcular a velocidade
        double dist_normalized = this->cannon.get_enemy_distance(this->enemy);
        dist_normalized = (dist_normalized-(this->screen_width/2.0))/((double)this->screen_width);
        
        Matrix input = Matrix(1,2);
        input.set(0,0,dist_normalized);
        input.set(0,1,1);                

        this->pop->ind[this->id].run(input);
        Matrix output = this->pop->ind[this->id].get_output();

        // Atirando o projétil
        double proj_vel = output.values[0][0]*50;
        // if(this->id == 0) printf("Velocidade %lf\n", proj_vel);
        this->projectile = cannon.shot_projectile(proj_vel, proj_vel, 45);
        this->projectile.set_color(this->r, this->g, this->b, this->a);
        
        this->status = INSTANCE_RUNNING;
    }

    // Desenhando os objetos da cena
    this->cannon.render( renderer );
    this->enemy.render( renderer );
    this->projectile.render( renderer );
}