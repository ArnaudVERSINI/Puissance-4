/*
 * Controler.cpp
 *
 *  Created on: 24 janv. 2010
 *      Author: Franck Arrestier
 */

#include "controler.hpp"
#include "ia.h"

int main(int argc, char **argv) {

	PlateauException exception("Toto");
	cout << "!!!Hello Puissance 4!!!" << endl; // prints !!!Hello World!!!
	JoueurHumain<JOUEUR_BLEU> joueur1;//("Arnaud");


	if (argc > 1) {
		const unsigned int profondeur = 5;

		IAJoueurMinMax<JOUEUR_ROUGE, profondeur> joueur2;//("Franck");
		cout << joueur1.getJoueurInformations() << endl;
		cout << joueur2.getJoueurInformations() << endl;
		Controler controleur(joueur1, joueur2);
		controleur.launchGame();

	} else {
		JoueurHumain<JOUEUR_ROUGE> joueur2;//("Franck");
		cout << joueur1.getJoueurInformations() << endl;
		cout << joueur2.getJoueurInformations() << endl;
		Controler controleur(joueur1, joueur2);
		controleur.launchGame();
	}



	return 0;
}
