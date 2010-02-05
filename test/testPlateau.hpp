#include <cpptest.h>
#include "plateau.hpp"

class PlateauTestSuite : public Test::Suite
{
public:
    PlateauTestSuite()
    {
        TEST_ADD(PlateauTestSuite::creation)
		TEST_ADD(PlateauTestSuite::setGet)
		TEST_ADD(PlateauTestSuite::colonnePleine)
		TEST_ADD(PlateauTestSuite::addToColumn)
		TEST_ADD(PlateauTestSuite::aGagnerHorizontal)
		TEST_ADD(PlateauTestSuite::aGagnerVertical)
		TEST_ADD(PlateauTestSuite::aGagnerDiagGaucheDroite)
    }




private:
    void creation() {
    	Plateau plateau;
        TEST_ASSERT(plateau.get(0, 0) == NONE)
    }
    void setGet() {
    	Plateau plateau;
            plateau.get(0,0);
            // Test de la presence du jeton au bon endroit
            TEST_ASSERT(plateau.get(0, 0) == NONE)

            // Jeton BLUE en 0,0
            plateau.set(0,0,BLUE);
            TEST_ASSERT(plateau.get(0, 0) == BLUE)

            // Jeton BLUE en 0,0
            plateau.set(3,3,RED);
            TEST_ASSERT(plateau.get(3, 3) == RED)

        }

    void colonnePleine() {
    	Plateau plateau;
    	TEST_ASSERT(plateau.colonnePleine(0) == false)

    	for(int ligne = 0 ; ligne <= Plateau::HAUTEUR + 3; ligne++) {
    		plateau.set(ligne,3,RED);
    	}
    	TEST_ASSERT(plateau.colonnePleine(3) == true)
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
        	Plateau plateau ;
        	// Ajout d'un pion dans colonne 2
        	plateau.addToColumn(0,RED);
        	plateau.addToColumn(0,RED);
        	plateau.addToColumn(0,RED);
        	// Test attendu a faux
        	TEST_ASSERT(plateau.aGagner(2,0,RED) == false)

        	// Test attendu a faux
        	plateau.addToColumn(0,RED);
        	TEST_ASSERT(plateau.aGagner(3,0,RED) == true)
        };
        {
        	// Initialisation du plateau
        	Plateau plateau;

        	plateau.addToColumn(0,RED);
        	plateau.addToColumn(0,BLUE);
        	plateau.addToColumn(0,RED);

        	// Test attendu a faux
        	plateau.addToColumn(0,RED);
        	TEST_ASSERT(plateau.aGagner(3,0,RED) == false)

        }
    }

    void aGagnerHorizontal() {
        {
           	Plateau plateau;
           	// Ajout d'un pion dans colonne 2
           	plateau.addToColumn(0,RED);
           	plateau.addToColumn(1,RED);
           	plateau.addToColumn(2,RED);
           	// Test attendu a faux
           	TEST_ASSERT(plateau.aGagner(0,2,RED) == false)

           	// Test attendu a faux
           	plateau.addToColumn(0,RED);
           	TEST_ASSERT(plateau.aGagner(0,3,RED) == true)
        };
        {
           	// Initialisation du plateau
           	Plateau plateau;

           	plateau.addToColumn(0,RED);
           	plateau.addToColumn(1,BLUE);
           	plateau.addToColumn(2,RED);

           	// Test attendu a faux
           	plateau.addToColumn(3,RED);
           	TEST_ASSERT(plateau.aGagner(0,3,RED) == false)
        }
    }

    void aGagnerDiagGaucheDroite() {
           	Plateau plateau;
           	// Ajout d'un pion dans colonne 2
           	plateau.addToColumn(0,RED);
        	plateau.addToColumn(1,BLUE);
           	plateau.addToColumn(1,RED);
           	plateau.addToColumn(2,BLUE);
           	plateau.addToColumn(2,BLUE);
           	plateau.addToColumn(2,RED);
           	// Test attendu a faux
           	TEST_ASSERT(plateau.aGagner(2,2,RED) == false)

           	// Test attendu a faux
           	plateau.addToColumn(3,BLUE);
           	plateau.addToColumn(3,BLUE);
           	plateau.addToColumn(3,BLUE);
           	plateau.addToColumn(3,RED);
           	TEST_ASSERT(plateau.aGagner(3,3,RED) == true)


        }

};


