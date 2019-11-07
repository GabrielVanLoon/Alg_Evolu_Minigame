#ifndef GAME_TEXT_MESSAGE_H
    #define GAME_TEXT_MESSAGE_H

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_ttf.h>
    #include <string>

    /**
     * @class TextMessage
     * Função simples que exibe uma mensagem na tela do usuário.
     * 
     * Obs.: Não está funcionando por não ser prioridade.
     */
    class TextMessage {
        public: 
            TTF_Font*    font;
            SDL_Color    color;
            SDL_Surface* surface;
            SDL_Texture* texture;
            SDL_Rect Message_rect;

            std::string str;

            TextMessage(std::string str, int pos_x, int pos_y, int width, int height);

            void render(SDL_Renderer* renderer);

    };

#endif