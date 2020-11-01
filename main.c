#include <stdio.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include <SDL/SDL_image.h>

///Initialisation des éléments du jeu:
//Constante pour la taille de l'image
const int WIDTH=1024;
const int HEIGHT=512;

//Definition d'un type pour savoir quelle image afficher
enum VariationImage {
	        Normal=0,
		Fausse,
		Fausse_surbrillance
};

///Fonctions gérant les éléments du jeu :
//Code utilisé pour détruire une image
//if(img != NULL){
//	                SDL_FreeSurface(img), img = NULL;
//}

//Action avec le clique
void clic(int x,int y){
};

//Affichage
void aff(SDL_Surface *screen){
};

int main ( int argc, char** argv )
{
    /// [1] Démarrage
    // [1.1] Démarrages SDL
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0)
    {
        printf("Impossible d'initialiser la SDL: %s ",SDL_GetError());
        return 1;
    }

    // [1.2] Préparation de fermeture
    atexit(SDL_Quit);

    // [1.3] Para-fenêtre
    SDL_WM_SetCaption("Affiche evil-eye", 0);

    /// [2] Préparation des composants
    // [2.1] Préparation de la fenêtre
    SDL_Surface* screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s ",SDL_GetError());
        return 1;
    }

    // [2.2] Préparation
    SDL_Surface* img = IMG_Load("./Textures/evil-eye.png");

    SDL_Surface* evileye = IMG_Load("./Textures/evil-eye.png");
    SDL_Surface* evileyeFake = IMG_Load("./Textures/evil-eye.png");
    SDL_Surface* evileyeFakeShiny = IMG_Load("./Textures/evil-eye.png");

    // [2.3] Préparation du jeu  

    // [2.4] Séparation de l'écran en deux :
    SDL_Rect left = { 0 };
    SDL_Rect right = { 0 };
    left.x = 0;
    left.y = 0;
    right.x = WIDTH/2;
    right.y = 0; 

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

	SDL_BlitSurface(img, NULL, screen, &left);
	SDL_BlitSurface(img, NULL, screen, &right);
	 
	SDL_Delay(16);

        SDL_Flip(screen);
    } //fin bcl principale

    ///[4] Destruction des composants
    //[4.1] Les images initialisées
    if(img != NULL){
	    SDL_FreeSurface(img), img = NULL;
    }
    if(evileye != NULL){
            SDL_FreeSurface(evileye), evileye = NULL;
    }
    if(evileyeFake != NULL){
            SDL_FreeSurface(evileyeFake), evileyeFake = NULL;
    }
    if(evileyeFakeShiny != NULL){
            SDL_FreeSurface(evileyeFakeShiny), evileyeFakeShiny = NULL;
    }

    //[4.2] L'écran
    SDL_FreeSurface(screen);


    printf("Aucune erreur détectée.");
    return 0;
}
