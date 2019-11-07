#ifndef GAME_PROJECTILE_H
    #define GAME_PROJECTILE_H

    #include <SDL2/SDL.h>
    #include "enemy.h"

    /**
     * @class Projectile
     * 
     * Representa um projétil disparado pelo Canhão. Possui atributos
     * básicos como posição, raio (é uma esfera) e velocidade.
     */
    class Projectile {
        public: 
            // Atributos de configuração
            int pos_x, pos_y;
            double vel_x, vel_y;
            int radius;
            Uint8 r, g, b, a;

            Projectile();

            Projectile(int pos_x, int pos_y, int radius, double vel_x, double vel_y);

            void set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

            void update_position();

            void update_velocity(double acel_x, double acel_y);

            bool check_colission(int pos_x, int pos_y, int width, int height);
            bool check_colission(const Enemy &e);

            void render(SDL_Renderer* renderer);

    };

#endif