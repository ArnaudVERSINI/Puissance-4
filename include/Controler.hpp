#ifndef CONTROLER_H_INCLUDED
#define CONTROLER_H_INCLUDED

#include "IHM_console.hpp"

// include C++
#include <iostream>
#include <cstdlib>

using namespace std;

class Controler {

	JeuxPuissanceQuatre jeux;
	IHMConsole console ;
    Joueur<JOUEUR_BLEU>& joueurBleu;
    Joueur<JOUEUR_ROUGE>& joueurRouge;

    inline void traitementTour() {
        size_t colonne;
        TJoueur joueurActuel = jeux.getJoueurActuel();
        if (joueurActuel == JOUEUR_BLEU) {
            colonne = joueurBleu.effectuerCoup();
        } else {
            colonne = joueurRouge.effectuerCoup();
        }
        if (colonne >= Plateau::LARGEUR) {
            return;
        }
        if (!jeux.estColonneJouable(colonne)) {
            return;
        }

        jeux.jouer(colonne);

        if (joueurActuel == JOUEUR_BLEU) {
            joueurRouge.prendreEnCompteCoupAdversaire(colonne);
        } else {
            joueurBleu.prendreEnCompteCoupAdversaire(colonne);
        }
    }

public :

    inline Controler(Joueur<JOUEUR_BLEU>& joueurBleu_, Joueur<JOUEUR_ROUGE>& joueurRouge_) :
            joueurBleu(joueurBleu_),
            joueurRouge(joueurRouge_){}

    inline void launchGame() {

    	while (not jeux.isEnded()) {

    		 //do {
					    //cout << jeux.getJoueurActuelStr() << " : ";
    		            //cout << "veuillez saisir le numero de colonne où jouer ( de 0 à " << Plateau::LARGEUR << "): ";
    		            //cin >> colonne;
    		            //cout << endl;
    		            //cout << colonne << endl;
    		            //if ( colonne >= Plateau::LARGEUR) {
    		            //    cout << "Merci de saisir un numero entre 0 et " << Plateau::LARGEUR << endl;
    		            //}
    		            //else if (jeux.estColonneJouable(colonne) == false) {
    		            //	cout << "Cette colonne " << colonne << " est pleine. Veuillez en choisir une autre"<< endl;
    		            //}
    		            //else {
    		            //	jouable = true ;
    		            //}

    		        //} while (colonne != true);



    		//jeux.jouer(colonne);
    		//jeux.switchCurrentPlayer();
    		traitementTour();
    		console.print(jeux);
    	}
    	cout << "Le gagnant est :" << jeux.getJoueurActuelGagnantStr() << endl;
    }
};



#endif // IHM_CONSOLE_H_INCLUDED
