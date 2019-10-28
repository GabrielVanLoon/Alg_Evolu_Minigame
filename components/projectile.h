#ifndef GAME_PROJECTILE_H
    #define GAME_PROJECTILE_H

    #include <SDL2/SDL.h>

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
            int vel_x, vel_y;
            int radius;
            Uint8 r, g, b, a;

            Projectile();

            Projectile(int pos_x, int pos_y, int radius, int vel_x, int vel_y);

            void set_color(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

            void update_position();

            void update_velocity(int acel_x, int acel_y);

            void render(SDL_Renderer* renderer);

    };

#endif