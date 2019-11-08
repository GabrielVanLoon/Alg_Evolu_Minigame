/**
 * Copyright 2019 - Gabriel Van Loon  
 * 
 * Algoritmos Genéticos + RN - Shooter Minigame
 * 
 */
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>
#include "components/enemy.h"
#include "components/cannon.h"
#include "components/instance.h"
#include "genetics/population.h"

/**
 * Configurações do jogo
 */
    const int  TAMANHO_POPULACAO = 300;
    const bool AUTO_UPGRADE      = true;

/**
 * CONFIGURAÇÕES GERAIS DO PROGRAMA
 */ 
    const int SCREEN_WIDTH  = 1200;
    const int SCREEN_HEIGHT = 680;


/**
 * VARIÁVEIS GLOBAIS 
 */
    SDL_Window*   gWindow   = NULL;
    SDL_Renderer* gRenderer = NULL;
    SDL_Event     gEvent;


int init();
void auto_upgrade(int gen, std::vector<Instance> &v);

int main(){

    if( init() ) 
        return 1;

    // Declarando as variáveis necessárias
    // std::vector<int> configurations{2,3,2,1}; v1.0
    std::vector<int> configurations{4,3,2};
    
    Population pop = Population(TAMANHO_POPULACAO);
    pop.genes_range       = 1;
    pop.mutation_rate     = 30;
    pop.mutation_range    = 1;
    pop.mutation_multiply = 1;
    pop.genes_precision   = 100; 
    pop.start(configurations);

    std::vector<Instance> vInstances;

    for(int i = 0; i < TAMANHO_POPULACAO; i++){
        vInstances.push_back(Instance(SCREEN_WIDTH, SCREEN_HEIGHT, INSTANCE_EASY, 10, &pop, i));
        vInstances[i].start();
    }

    // Variáveis do loop
    int framesCounter = 0;
    bool quitFlag     = false;
    bool changeRequestedFlag = false;
    char buttonPressed = ' ';

    bool onlyBestFlag    = false;
    bool randomSpamnFlag = false;
    bool randomFlySpamnFlag = false;
    bool enemiesRunFlag  = false;
    bool enemiesFlyFlag  = false;

    while(!quitFlag){
        
        if(AUTO_UPGRADE){
            auto_upgrade(pop.epoch, vInstances);
        }

        // 1ª Etapa - Lendo os eventos disparados
        while( SDL_PollEvent( &gEvent ) != 0 ){
            //User requests quit
            if( gEvent.type == SDL_QUIT ){
                quitFlag = true;
            } 
            // User Key Press
            if (gEvent.type == SDL_KEYDOWN){
                if(gEvent.key.keysym.sym == SDLK_b){
                    changeRequestedFlag = true;   
                    buttonPressed       = 'b';
                } else if(gEvent.key.keysym.sym == SDLK_r){
                    changeRequestedFlag = true;   
                    buttonPressed       = 'r';
                    randomSpamnFlag     = !randomSpamnFlag;
                } else if(gEvent.key.keysym.sym == SDLK_t){
                    changeRequestedFlag = true;   
                    buttonPressed       = 't';
                    randomFlySpamnFlag  = !randomFlySpamnFlag;
                } else if(gEvent.key.keysym.sym == SDLK_e){
                    changeRequestedFlag = true;   
                    buttonPressed  = 'e';
                    enemiesRunFlag = !enemiesRunFlag;
                } else if(gEvent.key.keysym.sym == SDLK_f){
                    changeRequestedFlag = true;   
                    buttonPressed  = 'f';
                    enemiesFlyFlag = !enemiesFlyFlag;
                } 
            }
        }

        // 2ª Etapa - Limpando a tela para o próximo frame
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( gRenderer ); 

        // 3º Etapa - Realizando as mudanças no frame
        bool allRoundsFinished = true;
        
        if(onlyBestFlag){
            vInstances[0].render(gRenderer, (framesCounter%2==0), false);
            allRoundsFinished = (vInstances[0].round_counter > vInstances[0].rounds_max);
        
            if(allRoundsFinished){
                printf("Score melhor indivíduo: %d\t\n", pop.ind[0].score);
                vInstances[0].start();
            }
        }

        if(!onlyBestFlag){
            for(int i = 0; i < vInstances.size(); i++){
                vInstances[i].render( gRenderer, (framesCounter%2==0), false);
                if(vInstances[i].status != INSTANCE_FINISHED){
                    allRoundsFinished = false;
                }
            }

            if(allRoundsFinished){
                pop.itrain();
                for(int i = 0; i < TAMANHO_POPULACAO; i++)
                    vInstances[i].start();
            }
        }

        // Realizando as mudanças estabelecidas pelo teclado
        if(allRoundsFinished && changeRequestedFlag){
            switch(buttonPressed){
                case 'b': 
                    onlyBestFlag = !onlyBestFlag; 
                    break;
                case 'r':
                    for(int i = 0; i < TAMANHO_POPULACAO; i++)
                        vInstances[i].flag_randomSpawn = randomSpamnFlag;
                    break;
                case 't':
                    for(int i = 0; i < TAMANHO_POPULACAO; i++)
                        vInstances[i].flag_randomSpawnFly = randomFlySpamnFlag;
                    break;
                case 'e':
                    for(int i = 0; i < TAMANHO_POPULACAO; i++)
                        vInstances[i].flag_enemiesRun = enemiesRunFlag;
                    break;
                case 'f':
                    for(int i = 0; i < TAMANHO_POPULACAO; i++)
                        vInstances[i].flag_flyingEnemies = enemiesFlyFlag;
                    break;
            }
            changeRequestedFlag = false; 
        }

        // 4ª Etapa - Redesenhando o frame o próximo frame
        SDL_RenderPresent( gRenderer );

        framesCounter++;
        // SDL_Delay(10);
    }

    // Desalocando as variáveis e destruindo as estruturas
    SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

    SDL_Quit();

    return 0;

}

int init(){
    /**
     * Pré-condigurações
     */
    srand(time(NULL));
    // Verificando se a SDL 2.0 foi carregada com sucesso
    if(SDL_Init( SDL_INIT_VIDEO ) < 0){
        printf("Error: a biblioteca SDL falhou ao iniciar.\n");
        return 1;
    } 

    // Gerando a janela que irá carregar o jogo
    gWindow = SDL_CreateWindow("Super Shooter AG", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == NULL){
        printf("Error: ocorreu um erro ao executar a função SDL_CreateWindow().\n");
        return 1;
    }

    // Gerando o renderizador que irá realizar o desenho dos frames
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
    if(gRenderer == NULL){
        printf("Error: ocorreu um erro ao executar a função SDL_CreateRenderer().\n");
        return 1;
    }

    return 0;
}

void auto_upgrade(int gen, std::vector<Instance> &v){

    if(gen <= 1){
        //printf("Estágio inicial...\n");
        for(int i = 0; i < v.size(); i++){
            v[i].flag_flyingEnemies = false;
            v[i].flag_randomSpawn   = false;
            v[i].flag_randomSpawnFly = false;
            v[i].flag_enemiesRun    = false;
        }
    }

    else if(gen == 7){
        //printf("Realizando upgrade...\n");
        for(int i = 0; i < v.size(); i++){
            v[i].flag_flyingEnemies = true;
            v[i].flag_randomSpawn   = false;
            v[i].flag_randomSpawnFly = false;
            v[i].flag_enemiesRun    = false;
        }
    }

    else if(gen == 25){
        //printf("Realizando upgrade...\n");
        for(int i = 0; i < v.size(); i++){
            v[i].flag_flyingEnemies = true;
            v[i].flag_randomSpawn   = true;
            v[i].flag_randomSpawnFly = false;
            v[i].flag_enemiesRun    = false;
        }
    }

    // else if(gen == 35){
    //     for(int i = 0; i < v.size(); i++){
    //         v[i].flag_flyingEnemies = true;
    //         v[i].flag_randomSpawn   = true;
    //         v[i].flag_randomSpawnFly = true;
    //         v[i].flag_enemiesRun    = false;
    //     }
    // }


}
