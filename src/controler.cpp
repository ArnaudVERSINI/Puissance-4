/*
 * Controler.cpp
 *
 *  Created on: 24 janv. 2010
 *      Author: Franck Arrestier
 */

#include "Controler.hpp"

int main() {
    PlateauException exception("Toto");
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	JoueurHumain<JOUEUR_BLEU> joueur1;//("Arnaud");
	JoueurHumain<JOUEUR_ROUGE> joueur2;//("Franck");
	cout << joueur1.getJoueurInformations() <<endl ;
	cout << joueur2.getJoueurInformations() <<endl ;
	Controler controleur(joueur1,joueur2) ;
	controleur.launchGame();

	return 0;
}
