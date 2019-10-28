#ifndef GAME_ENEMY_H
    #define GAME_ENEMY_H

    #include <SDL2/SDL.h>

    /**
     * @class Enemy
     * 
     * Representa um objeto Inimigo do jogo AG Shooter. Ele possui
     * propriedades básicas como posição, dimensões e velocidade. Além de
     * conter o sistema de detecção de colisões.
     * 
     * Caso haja tempo hábil, também serão criados poderes especiais com
     * disparo aleatório como escudo, speed boost, etc... afim de deixar o
     * jogo mais desafiados para o AG ser treinado.
     */
    class Enemy {
        public: 
            // Atributos de configuração
            int pos_x, pos_y;
            int vel_x;
            int width, height;
            Uint8 r, g, b, a;

            Enemy();

            Enemy(int pos_x, int pos_y, int width, int height);

            Enemy(int pos_x, int pos_y, int width, int height, int vel_x);

            void set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

            // Verifica se houve colisão de um objeto com outro.
            bool check_colission();

            void update_position();

            void update_velocity(int acel_x);

            void render(SDL_Renderer* renderer);

    };

#endif