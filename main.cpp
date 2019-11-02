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
#include "components/text_message.h"
#include "components/enemy.h"
#include "components/cannon.h"
#include "components/instance.h"
#include "genetics/population.h"

/**
 * Configurações do jogo
 */
    const int TAMANHO_POPULACAO = 100;


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

int main(){

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

    /**
     * Variáveis do jogo
     */

    // Declarando as variáveis necessárias
    std::vector<int> configurations{2,2,1};
    Population pop = Population(TAMANHO_POPULACAO);
    pop.genes_range       = 1;
    pop.mutation_rate     = 50;
    pop.mutation_range    = 1;
    pop.mutation_multiply = 1;
    pop.genes_precision   = 1000000; 
    pop.start();

    std::vector<Instance> vInstances;

    for(int i = 0; i < TAMANHO_POPULACAO; i++){
        vInstances.push_back(Instance(SCREEN_WIDTH, SCREEN_HEIGHT, INSTANCE_EASY, 10, &pop, i));
        vInstances[i].start();
    }

    TextMessage messageTeste = TextMessage("olá mundo!", 20, 20, 100, 20);

    // Variáveis do loop
    int framesCounter = 0;
    bool quitFlag = false;
    bool onlyBestFlag = false;
    bool changeRequestedFlag = false;

    while(!quitFlag){

        // 1ª Etapa - Lendo os eventos disparados
        while( SDL_PollEvent( &gEvent ) != 0 ){
            //User requests quit
            if( gEvent.type == SDL_QUIT ){
                quitFlag = true;
            } 
            // User Key Press
            if (gEvent.type == SDL_KEYDOWN){
                if(gEvent.key.keysym.sym == SDLK_b) 
                    changeRequestedFlag = true;   
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
        
            if(allRoundsFinished)
                vInstances[0].start();
            
            if(allRoundsFinished && changeRequestedFlag){
                changeRequestedFlag = false;
                onlyBestFlag        = false;
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

            if(allRoundsFinished && changeRequestedFlag){
                changeRequestedFlag = false;
                onlyBestFlag = true;
            }
        }

        messageTeste.render(gRenderer);

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

