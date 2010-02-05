/*
 * Controler.cpp
 *
 *  Created on: 24 janv. 2010
 *      Author: Franck Arrestier
 */

#include "Controler.hpp"

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	JoueurHumain<JOUEUR_BLEU> joueur1("Arnaud");
	JoueurHumain<JOUEUR_ROUGE> joueur2("Franck");
	cout << joueur1.getJoueurInformations() <<endl ;
	cout << joueur2.getJoueurInformations() <<endl ;
	Controler <JOUEUR_BLEU , JOUEUR_ROUGE> controleur(joueur1,joueur2) ;

	return 0;
}
