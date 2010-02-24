#include <cpptest.h>
#include "ia.h"

class IATestSuite : public Test::Suite
{
public:
	IATestSuite()
    {
        //TEST_ADD(IATestSuite::creation)
		TEST_ADD(IATestSuite::calculScoreFavorableJoueurAdverse)
    }




private:
	/**
	 * Creation. Le plateau est vide. Les scores attendus doivent être nul
	 */
    void creation() {
    	IAJoueurMinMax <JOUEUR_ROUGE  , 2> ia;
    	//TEST_ASSERT(ia.calculScoreJoueurActuel() == 0)
    	//TEST_ASSERT(ia.calculScoreJoueurAdverse() == 0)
    }

    /**
     * Calcule le score du joueur actuel alors qu'il a joue un premier coup
     * Le joueur adverse n'a pas joué
     */
    void calculScoreFavorableJoueurAdverse() {
        	IAJoueurMinMax <JOUEUR_ROUGE  , 6> ia;

        	ia.getPlateau().addToColumn(2,RED);
        	ia.getPlateau().addToColumn(6,BLUE);
        	ia.getPlateau().addToColumn(3,RED);
        	ia.getPlateau().addToColumn(3,BLUE);
        	ia.getPlateau().addToColumn(4,RED);
        	ia.getPlateau().addToColumn(1,BLUE);

        	/*TEST_ASSERT(ia.getPlateau().get(0,2) == RED)
        	TEST_ASSERT(ia.getPlateau().get(0,3) == RED)
        	TEST_ASSERT(ia.getPlateau().get(0,4) == RED)
        	TEST_ASSERT(ia.getPlateau().get(0,6) == BLUE)
        	TEST_ASSERT(ia.getPlateau().get(1,3) == BLUE)
        	TEST_ASSERT(ia.getPlateau().get(0,1) == BLUE)*/

        //	cout << ia.calculScoreJoueurActuel() << endl ;
        //	cout << ia.calculScoreJoueurAdverse() << endl ;

        	cout << ia.effectuerCoup() << endl ;
        	//ia.getPlateau().addToColumn(3,BLUE);
        	//TEST_ASSERT(ia.getPlateau().get(0,3) == BLUE)

        }

};
