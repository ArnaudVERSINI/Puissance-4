#include <cpptest.h>
#include "plateau.hpp"

class PlateauTestSuite : public Test::Suite
{
public:
    PlateauTestSuite()
    {
        TEST_ADD(PlateauTestSuite::creation)
		TEST_ADD(PlateauTestSuite::addJeton)
    }

private:
    void creation() {
        Plateau* plateau = new Plateau();
        TEST_ASSERT(plateau->get(0, 0) == NONE)
    }
    void addJeton() {
            Plateau* plateau = new Plateau();
            plateau->addToColumn(1,BLUE);
            // Test de la presence du jeton au bon endroit
            TEST_ASSERT(plateau->get(0, 1) == BLUE)

            //Est-il a cote ?
            TEST_ASSERT(plateau->get(0, 0) == RED)
            TEST_ASSERT(plateau->get(1, 1) == NONE)
            TEST_ASSERT(plateau->get(0, 2) == NONE)
        }
};


