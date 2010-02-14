#include <cpptest.h>
#include "ia.h"

class IATestSuite : public Test::Suite
{
public:
	IATestSuite()
    {
        TEST_ADD(IATestSuite::creation)
		TEST_ADD(IATestSuite::calculScoreFavorableJoueurAdverse)
    }




private:
	/**
	 * Creation. Le plateau est vide. Les scores attendus doivent être nul
	 */
    void creation() {
    	IAJoueurMinMax <JOUEUR_BLEU  , 2> ia;
    	TEST_ASSERT(ia.calculScoreJoueurActuel() == 0)
    	TEST_ASSERT(ia.calculScoreJoueurAdverse() == 0)
    }

    /**
     * Calcule le score du joueur actuel alors qu'il a joue un premier coup
     * Le joueur adverse n'a pas joué
     */
    void calculScoreFavorableJoueurAdverse() {
        	IAJoueurMinMax <JOUEUR_BLEU  , 6> ia;

        	ia.prendreEnCompteCoupAdversaire(1);
        	TEST_ASSERT(ia.getPlateau().get(0,1) == RED)
        	ia.prendreEnCompteCoupAdversaire(2);
        	TEST_ASSERT(ia.getPlateau().get(0,1) == RED)
        	TEST_ASSERT(ia.calculScoreJoueurActuel() == 0)
        	TEST_ASSERT(ia.calculScoreJoueurAdverse() == 0)
        }

};
