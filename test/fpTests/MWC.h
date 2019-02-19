// This tests whether the seed works in single/parallel execution

#include "../../src/baseFunctions/MWC.h"

TEST(setSeed, seed_low)
{
    int seed = 123;
    int curRandNum;
    int prevRandNum;
    randomNumberRerFMWC randNum;
    for (int i = 0; i < 1000; ++i)
    {
        randNum.initialize(seed);
        if (i > 0)
        {
            EXPECT_EQ(curRandNum, prevRandNum);
        }
        curRandNum = randNum.gen(1000);
        prevRandNum = curRandNum;
    }
}

TEST(setSeed, seed_high)
{
    long seed = 2351351351351351;
    int curRandNum;
    int prevRandNum;
    randomNumberRerFMWC randNum;
    for (int i = 0; i < 1000; ++i)
    {
        randNum.initialize(seed);
        if (i > 0)
        {
            EXPECT_EQ(curRandNum, prevRandNum);
        }
        curRandNum = randNum.gen(1000);
        prevRandNum = curRandNum;
    }
}

TEST(setSeed, seed_neg)
{
    long seed = -1001;
    int curRandNum;
    int prevRandNum;
    randomNumberRerFMWC randNum;
    for (int i = 0; i < 1000; ++i)
    {
        randNum.initialize(seed);
        if (i > 0)
        {
            EXPECT_EQ(curRandNum, prevRandNum);
        }
        curRandNum = randNum.gen(1000);
        prevRandNum = curRandNum;
    }
}

//expect two seq values random generated from large range to be NE
TEST(setSeed, randomGenNE)
{
    int range = 10000;
    long seed = -1001;
    int prevRandNum;
    randomNumberRerFMWC randNum;
    randNum.initialize(seed);
    prevRandNum = randNum.gen(range);
    for (int i = 0; i < 1000; ++i)
    {
        EXPECT_NE(randNum.gen(range), prevRandNum);
    }
}