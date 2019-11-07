#ifndef GAME_INSTANCE_H
    #define GAME_INSTANCE_H

    #include <SDL2/SDL.h>
    #include "enemy.h"
    #include "cannon.h"
    #include "../network/matrix.h"
    #include "../genetics/population.h"

    #define INSTANCE_EASY   1
    #define INSTANCE_NORMAL 2
    #define INSTANCE_HARD   3

    #define INSTANCE_INIT      1
    #define INSTANCE_RUNNING   2
    #define INSTANCE_WAITING   3
    #define INSTANCE_FINISHED  4


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
            int status;
            int difficulty;
            int rounds_max;
            Uint8 r, g, b, a;

            // Atributos da instância
            double round_counter;
            double gravity;
            double air_resistance;
            double wind_force;

            // Objetos da Instância
            Cannon cannon;
            Enemy  enemy;
            Projectile projectile;

            // Objetos utilizados para o AG
            int id;
            Population* pop;

            /**
             * Instance(int screen_width, int screen_height, int id, int difficulty, int rounds_max);
             * Cria a nova instância de um jogo. Configurando os seguintes parâmetros:
             * @param screen_width
             * @param screen_height Quais são as dimensões da tela que o jogo está sendo executado
             * @param id Qual é o id da instância
             * @param difficulty INSTANCE_EASY, INSTANCE_NORMAL, INSTANCE_HARD
             * @param rounds_max Quantidade máxima de rounds para cada rodada.
             */
            Instance();
            Instance(int screen_width, int screen_height, int difficulty, int rounds_max, Population* pop, int id);

            /**
             * void set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
             * Define os a cor RGBA que irá designar a instância
             */
            void set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

            /**
             * int get_status();
             * Retorna o código de status da instcia
             */
            int get_status();

            /**
             * void start();
             * Inicia a instância preparando todos os componentes
             * necessários para que o jogo ocorra.
             */
            void start();

            /**
             * void render(SDL_Renderer* renderer, bool update);
             * Renderiza os componentes da instância na tela
             * @param renderer renderizador utilizado pela tela
             * @param update caso positivo, dispara as funções que atualiza 
             * as posições e velocidades dos componentes.
             */
            void render(SDL_Renderer* renderer, bool update, bool iniciarRodada);
    };

#endif