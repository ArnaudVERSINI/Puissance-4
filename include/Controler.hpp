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


public :





    inline Controler(Joueur<JOUEUR_BLEU>& joueurBleu_, Joueur<JOUEUR_ROUGE>& joueurRouge_) :
            joueurBleu(joueurBleu_),
            joueurRouge(joueurRouge_){

    }

    void launchGame() {
        size_t colonne ;
        bool jouable = false ;
    	while (not jeux.isEnded()) {

    		 do {
					    cout << cout << jeux.getJoueurActuelStr() << " : ";
    		            cout << "veuillez saisir le numero de colonne où jouer ( de 0 à " << Plateau::LARGEUR << "): ";
    		            cin >> colonne;
    		            cout << endl;
    		            cout << colonne << endl;
    		            if ( colonne >= Plateau::LARGEUR) {
    		                cout << "Merci de saisir un numero entre 0 et " << Plateau::LARGEUR << endl;
    		            }
    		            else if (jeux.estColonneJouable(colonne) == false) {
    		            	cout << "Cette colonne " << colonne << " est pleine. Veuillez en choisir une autre"<< endl;
    		            }
    		            else {
    		            	jouable = true ;
    		            }

    		        } while (colonne != true);



    		jeux.jouer(colonne);
    		//jeux.switchCurrentPlayer();
    		console.print(jeux);
    	}
    	cout << "Le gagnant est :" << jeux.getJoueurActuelGagnantStr() << endl;

    }
};



#endif // IHM_CONSOLE_H_INCLUDED
