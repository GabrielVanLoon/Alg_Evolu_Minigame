#ifndef GAME_INSTANCE_H
    #define GAME_INSTANCE_H

    #include <SDL2/SDL.h>
    #include "enemy.h"
    #include "cannon.h"

    #define INSTANCE_EASY   1
    #define INSTANCE_NORMAL 2
    #define INSTANCE_HARD   3

    #define INSTANCE_INIT      1
    #define INSTANCE_RUNNING   2
    #define INSTANCE_FINISHED  3


    /**
     * @class Instance
     * Representa uma instância em execução do AG Shooter. Cada
     * indivíduo irá executar em uma instância independente das outras
     * a qual será representada por um ID e uma COR.
     * 
     * Ela também terá configurações como dificuldade do jogo e outros
     * atributos.
     */
    class Instance {
        public:
            // Atributos do pai
            int screen_width;
            int screen_height;

            // Atributos de configuração
            int id;
            int status;
            int difficulty;
            int rounds_max;
            Uint8 r, g, b, a;

            // Atributos da instância
            int round_counter;
            int gravity;
            int air_resistance;
            int wind_force;

            // Objetos da Instância
            Cannon cannon;
            Enemy  enemy;
            Projectile projectile;

            Instance();

            Instance(int screen_width, int screen_height, int id, int difficulty, int rounds_max);

            void set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

            int get_status();

            void start();

            void render(SDL_Renderer* renderer, bool update);
    };

#endif