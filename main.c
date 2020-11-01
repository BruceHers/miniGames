#include <stdio.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>

///Initialisation des éléments du jeu:
//Constante pour la taille de l'image
const int WIDTH=1024;
const int HEIGHT=512;
const int DIM=6;
const int D= 2*(DIM+1)+1;//Pour diviser l'écran en deux + des marges sur les côtés + 1 au milieu
const int SIZE_IMG=32; //Les images affichées de chaque côté sont des carrés de 32x32
const int W = WIDTH/D;//Pas d'une case à l'autre en largeur
const int H = HEIGHT/(DIM+1);//Pas d'une case à l'autre en hauteur

//Banque de créature (recensé avec un type enum)
enum Creat{
	creat1 = 1,
	creat2
};

///Fonctions gérant les éléments du jeu :
//Code utilisé pour détruire une image
//if(img != NULL){
//	                SDL_FreeSurface(img), img = NULL;
//}

//Action avec le clique
void clic(int x,int y){
};
//Action de création d'un tableau de créature
//Creat* tabcreat(int DIM){
//	Creat plateau[DIM][DIM];
//	return plateau;
//}

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
    SDL_WM_SetCaption("Cliquer sur l'intru dans le groupe de droite !", 0);

    // [1.4] Préparation de la génération aléatoire
    

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
    SDL_Surface* leftImg = IMG_Load("./Textures/evil-eye.png");
    SDL_Surface* rightImg = IMG_Load("./Textures/evil-eye.png");
    SDL_Surface* creat1 = IMG_Load("./Textures/creat1.png");
    SDL_Surface* creat2 = IMG_Load("./Textures/creat2.png");
    SDL_Rect p = { 0 }; //Pointeur utiliser pour donner des positions aux images dans le tableau normal
    SDL_Rect pf = { 0 }; //Pour le fake

    // [2.3] Préparation du jeu  
    // Création des deux plateaux identiques
    int plateau[DIM][DIM];
    int plateauFake[DIM][DIM];
    int i;
    int j;
    for(i=0; i<DIM; i++){
	    for(j=0; j<DIM; j++){
		    if(i==j){
			    plateau[i][j]=1;
			    plateauFake[i][j]=1;
		    }
		    else{
			    plateau[i][j]=0;
			    plateauFake[i][j]=0;
		    }
	    }
    }
    // Ajout d'une différence :
    int i_erreur = 2;
    int j_erreur = 2;

    int x_min_erreur = (2+DIM+i_erreur)*W;
    int x_max_erreur = x_min_erreur + SIZE_IMG;
    int y_min_erreur = (1+j_erreur)*H;
    int y_max_erreur = y_min_erreur + SIZE_IMG;
    
    plateauFake[i_erreur][j_erreur]=0;

    // Variable qui dit quand on a trouvé la différence :
    bool b = false;

    // [2.4] Séparation de l'écran en deux côté de DIMxDIM (avec marges): 
    SDL_Rect left = { 0 };
    SDL_Rect right = { 0 };
    left.x = W;
    left.y = H;
    right.x = W +  WIDTH/2;
    right.y = H; 

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
	    case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT){
			if(event.button.x > x_min_erreur && event.button.x < x_max_erreur && event.button.y > y_min_erreur && event.button.y < y_max_erreur){
				done = true;
			}
		}
		break;
            } // end switch event type
        } // end of message processing

        // [3.2] Calculs

        // [3.3] Dessin des composants
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255, 255, 255));

	//	SDL_BlitSurface(leftImg, NULL, screen, &left);
	//	SDL_BlitSurface(rightImg, NULL, screen, &right);
	
       	for(i=0; i<DIM; i++){
		p.x = (i+1)*W;//Avec i la i-ème case de la ligne
		pf.x = (DIM+i+2)*W;
		for(j=0; j<DIM; j++){
			p.y = (j+1)*H;//Avec j la j-ème case de la colonne
			pf.y = (j+1)*H;
			switch (plateau[i][j]){
			case 0 :
			   	SDL_BlitSurface(creat1, NULL, screen, &p);
				break;	
			case 1 :
				SDL_BlitSurface(creat2, NULL, screen, &p);
				break;
			}
			switch (plateauFake[i][j]){
	                case 0 :
				SDL_BlitSurface(creat1, NULL, screen, &pf); 
      				break;
                        case 1 :
                                SDL_BlitSurface(creat2, NULL, screen, &pf);
                                break;																					                        }
		}
        }
    

	SDL_Delay(16);

    	SDL_Flip(screen);

    }//fin bcl principale

    ///[4] Destruction des composants
    //[4.1] Les images initialisées
    //if(leftImg != NULL){
    if(leftImg != NULL){
	    SDL_FreeSurface(leftImg), leftImg = NULL;
    }
    if(rightImg != NULL){
            SDL_FreeSurface(rightImg), rightImg = NULL;
    }
    if(creat1 != NULL){
            SDL_FreeSurface(creat1), creat1 = NULL;
    }
    if(creat2 != NULL){
            SDL_FreeSurface(creat2), creat2 = NULL;
    }

    //[4.2] L'écran
    SDL_FreeSurface(screen);


    printf("Aucune erreur détectée.");
    return 0;
}
