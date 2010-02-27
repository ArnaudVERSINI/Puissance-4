/*
 * Controler.cpp
 *
 *  Created on: 24 janv. 2010
 *      Author: Franck Arrestier
 */

#include "controler.hpp"
#include "ia.h"

int main(int argc, char **argv) {
	size_t option ;
	cout << "!!!Hello Puissance 4!!!" << endl; // prints !!!Hello World!!!

	PlateauException exception("Toto");
	cout << "Usage" << endl;
	cout << "\t1 : partie avec 2 humains" << endl ;
	cout << "\t2 : partie avec 1 humain et IA (prof. 5)" << endl ;
	cout << "\t3 : partie avec 1 humain et IA (prof. 9)" << endl ;
	cout << "\t4 : partie avec 1 humain et IA (prof. 11)" << endl ;
	cout << "\t5 : partie avec 2 IA (prof. 5)" << endl ;
	cout << "\t6 : partie avec 2 IA (prof. 3 et 9)" << endl ;

    cout << "Selectionner une option de jeu : ";
    cin >> option;

	if (option == 1 ) {

		JoueurHumain<JOUEUR_BLEU> joueur1;//("Franck");
		JoueurHumain<JOUEUR_ROUGE> joueur2;//("Franck");
		cout << joueur1.getJoueurInformations() << endl;
		cout << joueur2.getJoueurInformations() << endl;
		Controler controleur(joueur1, joueur2);
		controleur.launchGame();
	} else if (option == 2  ) {
		JoueurHumain<JOUEUR_BLEU> joueur1;//("Franck");
		IAJoueurMinMax<JOUEUR_ROUGE, 5> joueur2;//("Franck");
		cout << joueur1.getJoueurInformations() << endl;
		cout << joueur2.getJoueurInformations() << endl;
		Controler controleur(joueur1, joueur2);
		controleur.launchGame();
	}else if (option == 3  ) {
		JoueurHumain<JOUEUR_BLEU> joueur1;//("Franck");
		IAJoueurMinMax<JOUEUR_ROUGE, 9> joueur2;//("Franck");
		cout << joueur1.getJoueurInformations() << endl;
		cout << joueur2.getJoueurInformations() << endl;
		Controler controleur(joueur1, joueur2);
		controleur.launchGame();
	}else if (option == 4  ) {
		JoueurHumain<JOUEUR_BLEU> joueur1;//("Franck");
		IAJoueurMinMax<JOUEUR_ROUGE, 11> joueur2;//("Franck");
		cout << joueur1.getJoueurInformations() << endl;
		cout << joueur2.getJoueurInformations() << endl;
		Controler controleur(joueur1, joueur2);
		controleur.launchGame();
	} else if (option == 5  ) {
		IAJoueurMinMax<JOUEUR_BLEU, 5> joueur1;//("Franck");
		IAJoueurMinMax<JOUEUR_ROUGE, 5> joueur2;//("Franck");
		cout << joueur1.getJoueurInformations() << endl;
		cout << joueur2.getJoueurInformations() << endl;
		Controler controleur(joueur1, joueur2);
		controleur.launchGame();
	}else if (option == 6  ) {
		IAJoueurMinMax<JOUEUR_BLEU, 3> joueur1;//("Franck");
		IAJoueurMinMax<JOUEUR_ROUGE, 9> joueur2;//("Franck");
		cout << joueur1.getJoueurInformations() << endl;
		cout << joueur2.getJoueurInformations() << endl;
		Controler controleur(joueur1, joueur2);
		controleur.launchGame();
	}

	else {


	}

	return 0;
}
