#include <cpptest.h>
#include "plateau.hpp"

class PlateauTestSuite : public Test::Suite
{
public:
    PlateauTestSuite()
    {
        TEST_ADD(PlateauTestSuite::creation)
    }

private:
    void creation() {
        Plateau* plateau = new Plateau();
        TEST_ASSERT(plateau->get(0, 0) == NONE)
    }
};

int main(int argc, char* argv[])
{
    PlateauTestSuite ts;
    Test::TextOutput output(Test::TextOutput::Verbose);
    if (ts.run(output) == true) {
        return 0;
    }
    return 1;
}
