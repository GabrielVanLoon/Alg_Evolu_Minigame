#ifndef GAME_INSTANCE_H
    #define GAME_INSTANCE_H

    #include <SDL2/SDL.h>

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
            // Atributos de configuração
            int id;
            int difficulty;
            int round_counter;
            int rounds_max;

            // Atributos da instância
            int gravity;
            int air_resistance;
            int wind_force;

            Instance();
    };

#endif