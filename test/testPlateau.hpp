#include <cpptest.h>
#include "plateau.hpp"

class PlateauTestSuite: public Test::Suite {
public:
	PlateauTestSuite() {
		TEST_ADD(PlateauTestSuite::creation)
		TEST_ADD(PlateauTestSuite::setGet)
		TEST_ADD(PlateauTestSuite::colonneJouable)
		TEST_ADD(PlateauTestSuite::addToColumn)
		TEST_ADD(PlateauTestSuite::aGagnerHorizontal)
		TEST_ADD(PlateauTestSuite::aGagnerVertical)
		TEST_ADD(PlateauTestSuite::aGagnerDiagGaucheDroite)
		TEST_ADD(PlateauTestSuite::aGagnerDiagDroiteGauche)
		TEST_ADD(PlateauTestSuite::isPartieFinitPlateauVide)
		TEST_ADD(PlateauTestSuite::isPartieFinitPlateauPlein)
		TEST_ADD(PlateauTestSuite::isPartieFinitDerniereCaseVide)
		TEST_ADD(PlateauTestSuite::isPartieFinitUneCaseVide)
		TEST_ADD(PlateauTestSuite::supprimerCoupException)
		TEST_ADD(PlateauTestSuite::supprimerCoup)
		TEST_ADD(PlateauTestSuite::aGagnerTriangle)
	}

private:
	void creation() {
		Plateau plateau;
		for (size_t colonne = 0; colonne < Plateau::LARGEUR; colonne++) {
			for (size_t ligne = 0; ligne < Plateau::HAUTEUR; ligne++) {
				TEST_ASSERT(plateau.get(ligne, colonne) == NONE)
			}
		}
	}

	void setGet() {
		Plateau plateau;
		plateau.get(0, 0);
		// Test de la presence du jeton au bon endroit
		TEST_ASSERT(plateau.get(0, 0) == NONE)

		// Jeton BLUE en 0,0
		plateau.set(0, 0, BLUE);
		TEST_ASSERT(plateau.get(0, 0) == BLUE)

		// Jeton BLUE en 0,0
		plateau.set(3, 3, RED);
		TEST_ASSERT(plateau.get(3, 3) == RED)

	}

	void colonneJouable() {
		Plateau plateau;
		TEST_ASSERT(plateau.colonneJouable(0) == true)

		for (int ligne = 0; ligne <= Plateau::HAUTEUR + 3; ligne++) {
			plateau.set(ligne, 3, RED);
		}
		TEST_ASSERT(plateau.colonneJouable(3) == false)
	}

	void addToColumn() {
		Plateau plateau;
		// Ajout d'un pion dans colonne 2
		TEST_ASSERT(plateau.addToColumn(2,RED) == 0)

		// Ajout d'un pion dans colonne 2
		TEST_ASSERT(plateau.addToColumn(2,BLUE) == 1)

		// Ajout d'un pion dans colonne 5
		TEST_ASSERT(plateau.addToColumn(5,BLUE) == 0)
	}

	void aGagnerVertical() {
		{
			Plateau plateau;
			// Ajout d'un pion dans colonne 2
			plateau.addToColumn(0, RED);
			plateau.addToColumn(0, RED);
			plateau.addToColumn(0, RED);
			// Test attendu a faux
			TEST_ASSERT(plateau.aGagner(2,0,RED) == false)

			// Test attendu a faux
			plateau.addToColumn(0, RED);
			TEST_ASSERT(plateau.aGagner(3,0,RED) == true)
		};
		{
			// Initialisation du plateau
			Plateau plateau;

			plateau.addToColumn(0, RED);
			plateau.addToColumn(0, BLUE);
			plateau.addToColumn(0, RED);

			// Test attendu a faux
			plateau.addToColumn(0, RED);
			TEST_ASSERT(plateau.aGagner(3,0,RED) == false)

		}
	}

	void aGagnerHorizontal() {
		{
			Plateau plateau;
			// Ajout d'un pion dans colonne 2
			plateau.addToColumn(0, RED);
			plateau.addToColumn(1, RED);
			plateau.addToColumn(2, RED);
			// Test attendu a faux
			TEST_ASSERT(plateau.aGagner(0,2,RED) == false)

			// Test attendu a faux
			plateau.addToColumn(0, RED);
			TEST_ASSERT(plateau.aGagner(0,3,RED) == true)
		};
		{
			// Initialisation du plateau
			Plateau plateau;

			plateau.addToColumn(0, RED);
			plateau.addToColumn(1, BLUE);
			plateau.addToColumn(2, RED);

			// Test attendu a faux
			plateau.addToColumn(3, RED);
			TEST_ASSERT(plateau.aGagner(0,3,RED) == false)
		}
	}

	void aGagnerDiagGaucheDroite() {
		Plateau plateau;
		// Ajout d'un pion dans colonne 2
		plateau.addToColumn(0, RED);
		plateau.addToColumn(1, BLUE);
		plateau.addToColumn(1, RED);
		plateau.addToColumn(2, BLUE);
		plateau.addToColumn(2, BLUE);
		plateau.addToColumn(2, RED);
		// Test attendu a faux
		TEST_ASSERT(plateau.aGagner(2,2,RED) == false)

		// Test attendu a faux
		plateau.addToColumn(3, BLUE);
		plateau.addToColumn(3, BLUE);
		plateau.addToColumn(3, BLUE);
		plateau.addToColumn(3, RED);
		TEST_ASSERT(plateau.aGagner(3,3,RED) == true)

	}
	void aGagnerDiagDroiteGauche() {
		Plateau plateau;
		// Ajout d'un pion dans colonne 2
		plateau.addToColumn(6, RED);
		plateau.addToColumn(5, BLUE);
		plateau.addToColumn(5, RED);
		plateau.addToColumn(4, BLUE);
		plateau.addToColumn(4, BLUE);
		plateau.addToColumn(4, RED);
		// Test attendu a faux
		TEST_ASSERT(plateau.aGagner(2,4,RED) == false)

		// Test attendu a faux
		plateau.addToColumn(3, BLUE);
		plateau.addToColumn(3, BLUE);
		plateau.addToColumn(3, BLUE);
		plateau.addToColumn(3, RED);
		TEST_ASSERT(plateau.aGagner(3,3,RED) == true)
	}

	/*
	 *   X
	 *  XOX
	 * XOOXX
	 */


	void aGagnerTriangle() {
			Plateau plateau;
			// Ajout d'un pion dans colonne 2
			plateau.addToColumn(1, RED);
			plateau.addToColumn(2, BLUE);
			plateau.addToColumn(3, BLUE);
			plateau.addToColumn(4, RED);
			plateau.addToColumn(5, RED);

			plateau.addToColumn(2, RED);
			plateau.addToColumn(3, BLUE);
			plateau.addToColumn(4, RED);
			plateau.addToColumn(3, RED);


			// Test attendu a faux
			TEST_ASSERT(plateau.aGagner(2,4,RED) == false)
		}

	void isPartieFinitPlateauVide() {
		Plateau plateau;
		for (size_t colonne = 0; colonne < Plateau::LARGEUR; colonne++) {
			for (size_t ligne = 0; ligne < Plateau::HAUTEUR; ligne++) {
				plateau.set(ligne, colonne, NONE);
			}
		}
		TEST_ASSERT(plateau.isPartieFinit() == false)
	}
	void isPartieFinitPlateauPlein() {
		Plateau plateau;
		// PLateau plein
		for (size_t colonne = 0; colonne < Plateau::LARGEUR; colonne++) {
			for (size_t ligne = 0; ligne < Plateau::HAUTEUR; ligne++) {
				plateau.set(ligne, colonne, RED);
			}
		}
		TEST_ASSERT(plateau.isPartieFinit() == true)
	}
	void isPartieFinitDerniereCaseVide() {
		Plateau plateau;
		// PLateau plein sauf dernier case
		for (size_t colonne = 0; colonne < Plateau::LARGEUR; colonne++) {
			for (size_t ligne = 0; ligne < Plateau::HAUTEUR; ligne++) {
				plateau.set(ligne, colonne, RED);
			}
		}
		plateau.set(Plateau::HAUTEUR -1 , Plateau::LARGEUR - 1 , NONE);
		TEST_ASSERT(plateau.isPartieFinit() == false)
	}
	void isPartieFinitUneCaseVide() {
		Plateau plateau;
		// PLateau plein sauf un case
		for (size_t colonne = 0; colonne < Plateau::LARGEUR; colonne++) {
			for (size_t ligne = 0; ligne < Plateau::HAUTEUR; ligne++) {
				plateau.set(ligne, colonne, RED);
			}
		}
		plateau.set(Plateau::HAUTEUR - 1, 0, NONE);
		TEST_ASSERT(plateau.isPartieFinit() == false)
	}
	void supprimerCoupException() {
		Plateau plateau;
		TEST_THROWS(plateau.supprimerCoup(0),PlateauException)
	}
	void supprimerCoup() {
		Plateau plateau;


		plateau.addToColumn(1,RED);
		TEST_ASSERT( plateau.get(0,1)  == RED)

/*		plateau.supprimerCoup(1);
		TEST_ASSERT( plateau.get(0,0)  == NONE)*/

	}
};

