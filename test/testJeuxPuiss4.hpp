#include <cpptest.h>
#include "jeu_puissance_4.hpp"

class JeuxPuiss4TestSuite : public Test::Suite
{
public:
	JeuxPuiss4TestSuite()
    {
        TEST_ADD(JeuxPuiss4TestSuite::creation)

    }




private:
    void creation() {
    	JeuxPuissanceQuatre jeux;
    	TEST_ASSERT(jeux.getJoueurActuel() == JOUEUR_BLEU)
    	TEST_ASSERT(jeux.playerToString(JOUEUR_BLEU) == "Joueur bleu")
    }


};
