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
    	while (not jeux.isEnded()) {
    		cout << jeux.getJoueurActuelStr() ;
    		cin >> colonne ;
    		jeux.jouer(colonne);
    		//jeux.switchCurrentPlayer();
    		console.print(jeux);
    	}
    	cout << "Le gagnant est :" << jeux.getJoueurActuelGagnantStr() << endl;

    }
};



#endif // IHM_CONSOLE_H_INCLUDED
