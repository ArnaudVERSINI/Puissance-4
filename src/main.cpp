#include <SDL/SDL.h>
#include <iostream>
#include "IHM_sdl.hpp"
#include "jeu_puissance_4.hpp"
#include "joueur.hpp"

Jeu jeu;

int jeuDeuxJoueursHumain() {

	JoueurHumain<JOUEUR_BLEU> joueur1;//("Arnaud");
	JoueurHumain<JOUEUR_ROUGE> joueur2;//("Franck");

	SDL_Event event;
	SDL_Surface *screen;
	int done = 0;

	//Initialisation
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cout << "Probleme pour initialiser SDL: " << SDL_GetError() << endl;
		return 1;
	}

	//Mettre un titre � la fen�tre
	SDL_WM_SetCaption("Morpion Version 1.0", NULL);

	//Ouvrir une fenetre
	screen = SDL_SetVideoMode(Jeu::WIDTH, Jeu::HEIGHT, 16, SDL_DOUBLEBUF
			| SDL_HWSURFACE);
	if (screen == NULL)
		done = 1;

	//Initialiser le jeu
	if (!jeu.init())
		return 1;

	//Boucle generale
	while (!done) {
		//Traiter les evenements
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				done = 1;
				break;
			case SDL_KEYUP:
				if (event.key.keysym.sym == SDLK_q)
					done = 1;
				break;
			case SDL_MOUSEBUTTONUP:
				jeu.clic(event.button.x, event.button.y);
				break;
			default:
				break;
			}
		}

		jeu.aff(screen);
		SDL_Flip(screen);
	}

	SDL_Quit();

}

int main(int argc, char **argv) {

	jeuDeuxJoueursHumain();
	(void) argc;
	(void) argv;

	return 0;
}
