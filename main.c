#include <stdio.h>
#include <SDL/SDL.h>
#include <stdbool.h>

int main ( int argc, char** argv )
{
    /// [1] Démarrage
    // [1.1] Démarrages SDL
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0)
    {
        printf("Impossible d'initialiser la SDL: ",SDL_GetError());
        return 1;
    }

    // [1.2] Préparation de fermeture
    atexit(SDL_Quit);

    // [1.3] Para-fenêtre
    SDL_WM_SetCaption("Application SDL", 0);

    /// [2] Préparation des composants
    // [2.1] Préparation de la fenêtre
    SDL_Surface* screen = SDL_SetVideoMode(640, 480, 32,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: ",SDL_GetError());
        return 1;
    }

    // [2.2] Préparation


    // [2.3] Préparation des ...


    /// [3] Boucle principale
    bool done = false;
    while (!done)
    {
        // [3.1] Gestion évènements
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                done = true;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    done = true;
                break;
            } // end switch event type
        } // end of message processing

        // [3.2] Calculs

        // [3.3] Dessin des composants
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 255, 255));


	SDL_Delay(16);

        SDL_Flip(screen);
    } //fin bcl principale

    ///[4] Destruction des composants
    SDL_FreeSurface(screen);


    printf("Aucune erreur détectée.");
    return 0;
}
