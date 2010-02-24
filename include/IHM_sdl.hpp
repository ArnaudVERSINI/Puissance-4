#ifndef IHM_SDL_HPP_INCLUDED
#define IHM_SDL_HPP_INCLUDED

#include <SDL/SDL.h>
#include <iostream>

#include "plateau.hpp"
#include "jeu_puissance_4.hpp"
#include "joueur.hpp"

//Classe du jeu
class Jeu {

private:
	//Le plateau jeu
	TCase plateau[Plateau::HAUTEUR][Plateau::LARGEUR];

	//Surfaces d'un rond, d'une croix et d'un fond
	SDL_Surface *o, *x, *bg;

	//Variable pour un tour
	TCase tour;

	JeuxPuissanceQuatre jeux;

public:
	static const size_t WIDTH = 392;
	static const size_t HEIGHT = 336;
	Jeu() {
		int i, j;

		//On met toutes les cases � Vide
		for (i = 0; i < Plateau::HAUTEUR; i++)
			for (j = 0; j < Plateau::LARGEUR; j++)
				plateau[i][j] = NONE;

		//Valeur par d�faut pour les surfaces
		o = NULL;
		x = NULL;
		bg = NULL;
	}

	~Jeu() {
		//On lib�re les surfaces
		SDL_FreeSurface(o);
		SDL_FreeSurface(bg);
		SDL_FreeSurface(x);
	}

	bool init() {
		//V�rification de l'allocation des surfaces
		if (o != NULL) {
			SDL_FreeSurface(o), o = NULL;
		}
		if (x != NULL) {
			SDL_FreeSurface(x), x = NULL;
		}
		if (bg != NULL) {
			SDL_FreeSurface(bg), bg = NULL;
		}

		//On charge toutes les images dans les surfaces associ�es
		o = SDL_LoadBMP("ressources/rouge.bmp");
		x = SDL_LoadBMP("ressources/jaune.bmp");
		bg = SDL_LoadBMP("ressources/fond.bmp");

		//On teste le retour du chargement
		if ((o == NULL) || (x == NULL) || (bg == NULL)) {
			cout << "Probleme de chargement du O, du X ou de l'image de fond"
					<< endl;
			return false;
		}

		//On initialise le premier tour: ce sera Rond qui commencera
		tour = RED;

		//Mis en place de la transparence
		if (SDL_SetColorKey(o, SDL_SRCCOLORKEY, 0) == -1)
			cout << "Erreur avec la transparence du rond" << endl;

		if (SDL_SetColorKey(x, SDL_SRCCOLORKEY, 0) == -1)
			cout << "Erreur avec la transparence de la croix" << endl;

		return true;
	}

	void clic(int x, int y) {
		size_t i, j;
		size_t colonne, ligne;

		//On recupere la largeur et l'hauteur d'une case
		colonne = WIDTH / Plateau::LARGEUR;
		ligne = HEIGHT / Plateau::HAUTEUR;

		//Calcul de la case associée
		i = y / ligne;
		j = x / colonne;

		cout << "Colonne  : " << j << endl;

		//Si la case est vide, on met � jour son type et la variable tour


		TJoueur joueurActuel = jeux.getJoueurActuel();

		if (j >= Plateau::LARGEUR) {
			return;
		}
		if (!jeux.estColonneJouable(j)) {
			return;
		}

		i = Plateau::HAUTEUR - jeux.jouer(j) - 1;
		cout << "Ligne  : " << i << endl;
		//Si la case est vide, on met à jour son type et la variable tour
		if (plateau[i][j] == NONE) {
			plateau[i][j] = tour;
			tour = (tour == RED) ? BLUE : RED;
		}

	}

	void aff(SDL_Surface *screen) {
		//Le couple (w,h) représentera les dimensions d'une case du plateau
		int w = WIDTH / Plateau::LARGEUR, h = HEIGHT / Plateau::HAUTEUR, i, j,
				k, l;
		SDL_Rect r = { 0, 0, 0, 0 };

		//Dessiner le fond d'ecran
		SDL_BlitSurface(bg, NULL, screen, &r);

		//On parcourt les cases du tableau, r sera le SDL_Rect qui représentera la position de la case courante
		for (k = 0, i = 0; i < HEIGHT; i += h, k++) {
			r.y = i;
			for (j = 0, l = 0; j < WIDTH; j += w, l++) {
				r.x = j;

				//On dessine en fonction du type de la case
				if (plateau[k][l] == BLUE) {
					SDL_BlitSurface(x, NULL, screen, &r);
				} else if (plateau[k][l] == RED) {
					SDL_BlitSurface(o, NULL, screen, &r);
				}
			}
		}

	}
};
#endif

