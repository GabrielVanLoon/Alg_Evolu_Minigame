#ifndef GAME_CANNON_H
    #define GAME_CANNON_H

    #include <SDL2/SDL.h>
    #include "projectile.h"

    /**
     * @class Cannon
     * 
     * Representa um objeto Canhão do AG Shooter. O canhão tem
     * como principal objetivo atirar os projéteis para acertar os
     * inimigos que aparecem em campo.
     * 
     * É esse objeto que terá associado a si a referencia de uma rede
     * neural que será utilizada para calcular os parâmetros do disparo.
     */
    class Cannon {
        public: 
            // Atributos de configuração
            int pos_x, pos_y;
            int width, height;
            Uint8 r, g, b, a;

            Cannon();

            Cannon(int pos_x, int pos_y, int width, int height);

            void set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

            // Calcula a distancia horizontal do inimigo baseado
            // na posição atual do canhão e atira.
            int get_enemy_distance();

            // Atira um projétil
            Projectile shot_projectile(int vel_x, int vel_y, int degrees);

            // SDL - Render()
            void render(SDL_Renderer* renderer);


    };

#endif