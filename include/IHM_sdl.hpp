#ifndef IHM_SDL_HPP_INCLUDED
#define IHM_SDL_HPP_INCLUDED

#include <SDL/SDL.h>
#include <iostream>

#include "plateau.hpp"
#include "jeu_puissance_4.hpp"
#include "joueur.hpp"
#include "ia.h"

//Classe du jeu
class Jeu {

private:
	//Le plateau jeu
	TCase plateau[Plateau::HAUTEUR][Plateau::LARGEUR];

	//Surfaces d'un rond, d'une croix et d'un fond
	SDL_Surface *rouge, *jaune, *background, *gagnantJaune, *gagnantRouge;

	//Variable pour un tour
	TCase tour;

	Joueur<JOUEUR_BLEU>& joueurBleu;
	Joueur<JOUEUR_ROUGE>& joueurRouge;

	JeuxPuissanceQuatre jeux;

public:
	static const size_t WIDTH = 392;
	static const size_t HEIGHT = 336;

	Jeu(Joueur<JOUEUR_BLEU>& joueurBleu_, Joueur<JOUEUR_ROUGE>& joueurRouge_) :
		joueurBleu(joueurBleu_), joueurRouge(joueurRouge_) {
		int i, j;

		//On met toutes les cases � Vide
		for (i = 0; i < Plateau::HAUTEUR; i++)
			for (j = 0; j < Plateau::LARGEUR; j++)
				plateau[i][j] = NONE;

		//Valeur par d�faut pour les surfaces
		rouge = NULL;
		jaune = NULL;
		background = NULL;
		gagnantJaune = NULL;
		gagnantRouge = NULL;
	}

	~Jeu() {
		//On lib�re les surfaces
		SDL_FreeSurface(rouge);
		SDL_FreeSurface(background);
		SDL_FreeSurface(jaune);
		SDL_FreeSurface(gagnantJaune);
		SDL_FreeSurface(gagnantRouge);
	}

	bool init() {
		//V�rification de l'allocation des surfaces
		if (rouge != NULL) {
			SDL_FreeSurface(rouge), rouge = NULL;
		}
		if (jaune != NULL) {
			SDL_FreeSurface(jaune), jaune = NULL;
		}
		if (background != NULL) {
			SDL_FreeSurface(background), background = NULL;
		}
		if (gagnantJaune != NULL) {
			SDL_FreeSurface(gagnantJaune), gagnantJaune = NULL;
		}
		if (gagnantRouge != NULL) {
			SDL_FreeSurface(gagnantRouge), gagnantRouge = NULL;
		}
		//On charge toutes les images dans les surfaces associ�es
		rouge = SDL_LoadBMP("ressources/rouge.bmp");
		jaune = SDL_LoadBMP("ressources/jaune.bmp");
		background = SDL_LoadBMP("ressources/fond.bmp");
		gagnantJaune = SDL_LoadBMP("ressources/gagnantJaune.bmp");
		gagnantRouge = SDL_LoadBMP("ressources/gagnantRouge.bmp");

		//On teste le retour du chargement
		if ((rouge == NULL) || (jaune == NULL) || (background == NULL)
				|| (gagnantJaune == NULL) || (gagnantRouge == NULL)) {
			cout
					<< "Probleme de chargement de l'image rouge, jaune ou background"
					<< endl;
			return false;
		}

		//On initialise le premier tour: ce sera Rond qui commencera
		tour = RED;

		//Mis en place de la transparence
		if (SDL_SetColorKey(rouge, SDL_SRCCOLORKEY, 0) == -1)
			cout << "Erreur avec la transparence du rond" << endl;

		if (SDL_SetColorKey(jaune, SDL_SRCCOLORKEY, 0) == -1)
			cout << "Erreur avec la transparence de la croix" << endl;

		if (SDL_SetColorKey(gagnantJaune, SDL_SRCCOLORKEY, 0) == -1)
			cout << "Erreur avec la transparence du gagnant bleu" << endl;

		if (SDL_SetColorKey(gagnantRouge, SDL_SRCCOLORKEY, 0) == -1)
			cout << "Erreur avec la transparence du gagnant rouge" << endl;
		return true;
	}

	void clic(int x, int y) {
		size_t i, j;
		size_t colonne, ligne;
		bool joue = false;

		//On recupere la largeur et l'hauteur d'une case
		colonne = WIDTH / Plateau::LARGEUR;
		ligne = HEIGHT / Plateau::HAUTEUR;

		//Calcul de la case associée
		i = y / ligne;
		j = x / colonne;

		TJoueur joueurActuel = jeux.getJoueurActuel();

		if (j >= Plateau::LARGEUR) {
			return;
		}
		if (!jeux.estColonneJouable(j)) {
			return;
		}

		i = Plateau::HAUTEUR - jeux.jouer(j) - 1;
		joueurBleu.prendreEnCompteCoupAdversaire(i);

		//cout << "Ligne  : " << i << endl;
		//Si la case est vide, on met à jour son type et la variable tour
		if (plateau[i][j] == NONE) {
			plateau[i][j] = tour;
			tour = (tour == RED) ? BLUE : RED;
			joue = true;
		}

	}

	void aff(SDL_Surface *screen) {
		//Le couple (w,h) représentera les dimensions d'une case du plateau
		int w = WIDTH / Plateau::LARGEUR, h = HEIGHT / Plateau::HAUTEUR, i, j,
				k, l;
		SDL_Rect r = { 0, 0, 0, 0 };

		//Dessiner le fond d'ecran
		SDL_BlitSurface(background, NULL, screen, &r);

		//On parcourt les cases du tableau, r sera le SDL_Rect qui représentera la position de la case courante
		for (k = 0, i = 0; i < HEIGHT; i += h, k++) {
			r.y = i;
			for (j = 0, l = 0; j < WIDTH; j += w, l++) {
				r.x = j;

				//On dessine en fonction du type de la case
				if (plateau[k][l] == BLUE) {
					SDL_BlitSurface(jaune, NULL, screen, &r);
				} else if (plateau[k][l] == RED) {
					SDL_BlitSurface(rouge, NULL, screen, &r);
				}
			}
		}

		// Test si la partie est finie
		if (jeux.isEnded()) {
			SDL_Rect r2 = { 100, 100, 0, 0 };
			TJoueur joueurGagnant = jeux.getJoueurActuelGagnant();
			if (joueurGagnant == JOUEUR_BLEU) {
				// le gagnant est le jaune

				//Dessiner le fond d'ecran
				SDL_BlitSurface(gagnantRouge, NULL, screen, &r2);
			} else if (joueurGagnant == JOUEUR_ROUGE) {
				// le gagnant est le rouge

				//Dessiner le fond d'ecran
				SDL_BlitSurface(gagnantJaune, NULL, screen, &r2);
			} else {

			}
		}
	}

	void verif(IAJoueurMinMax<JOUEUR_ROUGE, 9> ia) {
		TJoueur joueurActuel = jeux.getJoueurActuel();
		if (joueurActuel == JOUEUR_ROUGE && !jeux.isEnded()) {
			size_t ligne, colonne;

			bool joue = false;

			colonne = ia.effectuerCoup();

			if (colonne > Plateau::LARGEUR) {
				return;
			}
			if (!jeux.estColonneJouable(colonne)) {
				return;
			}
			ligne = Plateau::HAUTEUR - jeux.jouer(colonne) - 1;


			joueurRouge.prendreEnCompteCoupAdversaire(colonne);

			cout << "Ligne  : " << ligne << endl;
			cout << "Colonne  : " << colonne << endl;
			//Si la case est vide, on met à jour son type et la variable tour
			if (plateau[ligne][colonne] == NONE) {
				plateau[ligne][colonne] = tour;
				tour = (tour == RED) ? BLUE : RED;
				joue = true;
			}

		}
	}
};
#endif

