#include "instance.h"
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <time.h>

#define PI 3.14159265

#define CANNON_DEFAULT_WIDTH  50
#define CANNON_DEFAULT_HEIGHT 30

#define ENEMY_DEFAULT_WIDTH   40
#define ENEMY_DEFAULT_HEIGHT  60

#define ENEMY_MAX_VELOCITY   3.0

#define PROJ_MAX_VELOCITY    45.0
#define PROJ_MAX_ANGLE       (PI * 4.0)/9.0  // 90º == "PI/2.0" | 80º == "PI*4.0/9.0" 
#define PROJ_MIN_ANGLE       PI/6.0  // 30º


// Função auxiliar para gerar valores double aleatorios
double random_double(int range, int precision){
    if(precision == 0) precision = 1;
    return (rand()%(range*precision))/((double)precision);
}

int get_dist_manhattan(const Projectile &p, const Enemy &e){
    return abs(p.pos_x-e.pos_x) + abs(p.pos_y-e.pos_y);
    // return abs( p.pos_x - (e.pos_x+(e.width/2)) ) + abs( p.pos_y - (e.pos_y+(e.height/2)) );
}

Instance::Instance(){
    this->screen_width  = 400;
    this->screen_height = 400;
    
    this->id = 1;
    this->status = INSTANCE_INIT;
    this->difficulty = INSTANCE_EASY;
    this->rounds_max = 5;
    this->r = this->g = this->b = this->a = 0x00;

    this->type = INST_TYPE_DEFAULT;
    this->flag_randomSpawn   = false;
    this->flag_enemiesRun    = false;
    this->flag_flyingEnemies = false;
    this->flag_randomSpawnFly = false;
}

Instance::Instance(int screen_width, int screen_height, int difficulty, int rounds_max, Population* pop, int id){
    this->screen_width  = screen_width;
    this->screen_height = screen_height;
    
    this->status = INSTANCE_INIT;
    this->difficulty = difficulty;
    this->rounds_max = rounds_max;
    this->r = this->g = this->b = this->a = 0x00;

    this->type = INST_TYPE_DEFAULT;
    this->flag_randomSpawn   = false;
    this->flag_enemiesRun    = false;
    this->flag_flyingEnemies = false;
    this->flag_randomSpawnFly = false;

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

    // Preparando os parâmetros
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
    this->cannon = Cannon(20, this->screen_height-30, CANNON_DEFAULT_WIDTH, CANNON_DEFAULT_HEIGHT);
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
        
        this->enemy.update_position();

        this->proj_min_dist = std::min(this->proj_min_dist, get_dist_manhattan(this->projectile, this->enemy));
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
    else if(this->status == INSTANCE_RUNNING && (this->projectile.pos_y >= this->screen_height 
            || this->projectile.pos_x > 2*this->screen_width)){
        
        // Incrementa o contador de rodadas e calcula a loss
        this->round_counter += 1;
        this->pop->ind[this->id].score += this->proj_min_dist;

        if(this->round_counter > this->rounds_max){
            this->status = INSTANCE_FINISHED;
        } else {
            this->status = INSTANCE_WAITING;
        }
    }

    // Se o inimigo tocou no canhão 
    if(this->status == INSTANCE_RUNNING && this->enemy.pos_x <= this->cannon.pos_x+this->cannon.width){
        // O inimigo para e aumenta penaliza o score
        this->pop->ind[this->id].score += 100;
        this->enemy.vel_x = 0.0;
    }

    // Prepara uma nova rodada do tipo FLAG CONTROL
    if(this->status == INSTANCE_WAITING && this->type == INST_TYPE_FLAG_CONTROL){
        
        // Configurando e posicionando o inimigo
        if(this->flag_randomSpawn == true)
            this->enemy = Enemy( (rand()%(this->screen_width-140))+70, this->screen_height-60, ENEMY_DEFAULT_WIDTH, ENEMY_DEFAULT_HEIGHT);
        else
            this->enemy = Enemy(this->screen_width-(100*this->round_counter)-60, this->screen_height-60, ENEMY_DEFAULT_WIDTH, ENEMY_DEFAULT_HEIGHT);
        this->enemy.set_color(this->r, this->g, this->b, this->a);

        if(this->flag_flyingEnemies == true){
            if(this->flag_randomSpawnFly){
                this->enemy.pos_y = rand()%(this->screen_height-this->enemy.height);
            } else {
                this->enemy.pos_y = this->screen_height-(this->round_counter*60);
            }
        }

        if(this->flag_enemiesRun == true)
            this->enemy.vel_x = random_double((int)ENEMY_MAX_VELOCITY,100);
        else
            this->enemy.vel_x = 0.0;

        // Configurando a loss da rodada
        this->proj_min_dist  = 99999999;
    }

    else if(this->status == INSTANCE_WAITING && this->type == INST_TYPE_ALL_POSIX){
        
        // As instâncias do tipo ALL_POSIX tem obrigatoriamente 4*8 rodadas
        this->rounds_max = 36;

        // A posicao da X e Y do inimigo são definidar pela rodada tal que
        int e_posX = (this->round_counter-1) / 4; // 8 posicoes distintas
        int e_posY = (this->round_counter-1) % 4; // 4 posicoes distintas

        int pos_x = (this->flag_randomSpawn)    ? (rand()%(this->screen_width-140))+70 : this->screen_width-(120*e_posX)-60; 
        int pos_y = (this->flag_randomSpawnFly) ? rand()%(this->screen_height-this->enemy.height) : this->screen_height-(e_posY*200)-60; 
        
        this->enemy = Enemy( pos_x, pos_y, ENEMY_DEFAULT_WIDTH, ENEMY_DEFAULT_HEIGHT);
        this->enemy.set_color(this->r, this->g, this->b, this->a);

        // Configurando a loss da rodada
        this->proj_min_dist  = 99999999;
    }

    // Após a partida ter sido preparada, entra com os dados na rede neural
    // sendo eles devidamente normalizados na entrada e na saída e em seguida
    // inicia a instância.
    if(this->status == INSTANCE_WAITING){
        
        // Calculando os parâmetros de entrada da rede e normalizando seus valores
        double dist_x_normalized = this->cannon.get_enemy_distance(this->enemy);
        dist_x_normalized        = (dist_x_normalized-(this->screen_width/2.0))/((double)this->screen_width);
        double dist_y_normalized = this->enemy.pos_y-(this->screen_height-this->enemy.height);
        dist_y_normalized        = dist_y_normalized/((double)this->screen_height-this->enemy.height);
        double velx_normalized = this->enemy.vel_x / ENEMY_MAX_VELOCITY;
        
        // Construindo a matriz de entrada
        Matrix input = Matrix(1,4);
        input.set(0,0,dist_x_normalized);
        input.set(0,1,dist_y_normalized);
        input.set(0,2,velx_normalized);
        input.set(0,3,1);                

        // Executando a rede neural
        this->pop->ind[this->id].run(input);
        Matrix output = this->pop->ind[this->id].get_output();

        // Ajustando os parâmetros de saída
        double proj_vel   = std::min( PROJ_MAX_VELOCITY, output.values[0][0] * PROJ_MAX_VELOCITY);
        double proj_angle = std::min(1.0, output.values[0][1]);
        proj_angle = (proj_angle * (PROJ_MAX_ANGLE-PROJ_MIN_ANGLE)) + PROJ_MIN_ANGLE;

        this->projectile = cannon.shot_projectile(proj_vel*cos(proj_angle), proj_vel*sin(proj_angle), 45);
        this->projectile.set_color(this->r, this->g, this->b, this->a);
        
        this->status = INSTANCE_RUNNING;
    }

    // Desenhando os objetos da cena
    this->cannon.render( renderer );
    this->enemy.render( renderer );
    this->projectile.render( renderer );
}