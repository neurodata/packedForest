// This tests whether the seed works in single/parallel execution

#include "../../src/packedForest.h"

using namespace fp;

TEST(multiSeed, testSeedSet)
{
    int seed = 0;
    EXPECT_EQ(0, seed);

    // fp::fpForest<double> forest;

    fpSingleton::getSingleton().setParameter("seed", 123);
}
