#include <stdio.h>
#include <SDL/SDL.h>
#include <stdbool.h>
#include <SDL/SDL_image.h>
#include <stdlib.h>
#include <time.h>

///Création pour générer de l'aléatoire 
//Seed 
static bool rand_is_init = false;

//Fonction donnant un chiffre aléatoire x, min<=x<max
int rand_int (int min, int max){
	        if(!rand_is_init){
	                srand(time(NULL));
	                rand_is_init = true;
	        }
	        return(rand()%(max - min) + min);
}


///Initialisation des éléments du jeu:
//Constante pour la taille de l'image
const int WIDTH=1024;
const int HEIGHT=512;
const int DIM=6; // Peut augmenté/diminué la difficulté (sous réserves de modifications du reste du programme)
const int D= 2*(DIM+1)+1;//Pour diviser l'écran en deux + des marges sur les côtés + 1 au milieu
const int SIZE_IMG=32; //Les images affichées de chaque côté sont des carrés de 32x32
const int W=WIDTH/D;//Pas d'une case à l'autre en largeur
const int H=HEIGHT/(DIM+1);//Pas d'une case à l'autre en hauteur
const int NB_CREAT=7; //Peut être considéré comme le niveau de difficulté (2 -> Trop facile, 4 -> Moyen, 7 -> Difficile)

///Debut du main
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
    SDL_WM_SetCaption("Clique sur l'intru dans le groupe de droite !", 0);

    // [1.4] Préparation de la sauvegarde
    FILE* data = NULL;
    data = fopen("sauvegarde.txt","r+");    

    /// [2] Préparation des composants
    // [2.1] Préparation de la fenêtre
    SDL_Surface* screen = SDL_SetVideoMode(WIDTH, HEIGHT, 32,
                                           SDL_HWSURFACE|SDL_DOUBLEBUF);
    if ( !screen )
    {
        printf("Unable to set 640x480 video: %s ",SDL_GetError());
        return 1;
    }

    // [2.2] Préparation des autres images
    SDL_Surface* leftImg = IMG_Load("./Textures/evil-eye.png");
    SDL_Surface* rightImg = IMG_Load("./Textures/evil-eye.png");
    SDL_Surface* creat1 = IMG_Load("./Textures/creat1.png");
    SDL_Surface* creat2 = IMG_Load("./Textures/creat2.png");
    SDL_Surface* creat3 = IMG_Load("./Textures/creat3.png");
    SDL_Surface* creat4 = IMG_Load("./Textures/creat4.png");
    SDL_Surface* creat5 = IMG_Load("./Textures/creat5.png");
    SDL_Surface* creat6 = IMG_Load("./Textures/creat6.png");
    SDL_Surface* creat7 = IMG_Load("./Textures/creat7.png");
    SDL_Surface* fin = IMG_Load("./Textures/fin.png");
    
    // [2.3] Préparation des pointeurs de postion pour afficher d=les images
    SDL_Rect p = { 0 }; //Pour le tableau normal
    SDL_Rect pf = { 0 }; //Pour le fake

    // [2.4] Préparation du jeu  
    // Création des deux plateaux identiques
    int plateau[DIM][DIM];
    int plateauFake[DIM][DIM];
    int i;
    int j;
    for(i=0; i<DIM; i++){
	    for(j=0; j<DIM; j++){
		    plateau[i][j]=rand_int(0,NB_CREAT);;
		    plateauFake[i][j]=plateau[i][j];
	    }
    }

    // Ajout d'une différence :
    int i_erreur = rand_int(0,DIM);
    int j_erreur = rand_int(0,DIM);

    int x_min_erreur = (2+DIM+i_erreur)*W;
    int x_max_erreur = x_min_erreur + SIZE_IMG;
    int y_min_erreur = (1+j_erreur)*H;
    int y_max_erreur = y_min_erreur + SIZE_IMG;
    
    int diff = rand_int(0,NB_CREAT);
    
    if (plateau[i_erreur][j_erreur]==diff){
    	if (plateau[i_erreur][j_erreur]==0){
	    diff = 1;	    
	}
	else{
	    diff = plateau[i_erreur][j_erreur] - 1;
	}
    }

    plateauFake[i_erreur][j_erreur]=diff;

    // Variable qui dit quand on a trouvé la différence :
    bool b = false; 

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
	//Evenement lié à l'utilisation de la touche échap
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    done = true;
                break;
	//Evenement lié au clic de souris (gauche)	
	    case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT){
			if(event.button.x > x_min_erreur && event.button.x < x_max_erreur && event.button.y > y_min_erreur && event.button.y < y_max_erreur){
				SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
				SDL_BlitSurface(fin, NULL, screen, NULL);
				SDL_Flip(screen);
				SDL_Delay(1600);
				fseek(data, 0, SEEK_END);
				fputs("Partie terminée en ",data);
				int time = SDL_GetTicks();
				time = time/1000;
				fprintf(data, "%d", time);
				fputs(" secondes\n",data);
				done=true;
			}
		}
		break;
            } // end switch event type
        } // end of message processing
	
	//Si le jeu est en cours :
	if(!done){

        // [3.2] Dessin des composants
        SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 255, 255, 255));

       	for(i=0; i<DIM; i++){
		p.x = (i+1)*W;//Avec i la i-ème case de la ligne
		pf.x = (DIM+i+2)*W;
		
		for(j=0; j<DIM; j++){
			p.y = (j+1)*H;//Avec j la j-ème case de la colonne
			pf.y = (j+1)*H;
			//Affichage pour le plateau normal (gauche)
			switch (plateau[i][j]){
			case 0 :
			   	SDL_BlitSurface(creat1, NULL, screen, &p);
				break;	
			case 1 :
				SDL_BlitSurface(creat2, NULL, screen, &p);
				break;
			case 2 :
				SDL_BlitSurface(creat3, NULL, screen, &p);
		  	break;
			case 3 :
		                SDL_BlitSurface(creat4, NULL, screen, &p);
		        break;
 			case 4 :
			        SDL_BlitSurface(creat5, NULL, screen, &p);
			break;
		        case 5 :
		                SDL_BlitSurface(creat6, NULL, screen, &p);
			break;
			case 6 :
			        SDL_BlitSurface(creat7, NULL, screen, &p);
			break;
			}
			//Affichage pour le plateau fake (droite)
			switch (plateauFake[i][j]){
	                case 0 :
				SDL_BlitSurface(creat1, NULL, screen, &pf); 
      				break;
                        case 1 :
                                SDL_BlitSurface(creat2, NULL, screen, &pf);
                                break;
			case 2 :
                                SDL_BlitSurface(creat3, NULL, screen, &pf);
                        break;
                        case 3 :
                                SDL_BlitSurface(creat4, NULL, screen, &pf);
                        break;
                        case 4 :
                                SDL_BlitSurface(creat5, NULL, screen, &pf);
                        break;
                        case 5 :
                                SDL_BlitSurface(creat6, NULL, screen, &pf);
                        break;
                        case 6 :
                                SDL_BlitSurface(creat7, NULL, screen, &pf);
                        break;
			}
		}
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
    
    //[4.3] Fermeture du fichier de sauvegarde
    fclose(data);


    printf("Aucune erreur détectée.");
    return 0;
}
