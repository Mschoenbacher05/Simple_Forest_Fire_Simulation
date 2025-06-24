#include "Forest.h"
#include "gtest/gtest.h"
/*
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
*/
// Test adding a single station
TEST(assignStation, addStation)
{
    forest testForest(1, 1);
    testForest.assignStation();
    EXPECT_EQ(testForest.regions[{0, 0}].getHasStation(), true);
}
// Test adding a third station
TEST(assignStation, addStation3)
{
    forest testForest(1, 3);
    testForest.assignStation();
    testForest.assignStation();
    testForest.assignStation();
    bool test = true;
    if (!testForest.regions[{0, 0}].getHasStation())
    {
        test = false;
    }
    if (!testForest.regions[{0, 1}].getHasStation())
    {
        test = false;
    }
    if (!testForest.regions[{0, 2}].getHasStation())
    {
        test = false;
    }
    EXPECT_EQ(test, true);
}
// Test striking lightning
TEST(lightningStrike, lightning)
{
    forest testForest(1, 1);
    testForest.lightning_strike();
    EXPECT_EQ(testForest.regions[{0, 0}].getBurning(), true);
}
// Test simulation starting fires
TEST(runSimulation, startFire)
{
    forest testForest(1, 1);
    testForest.runSimulation(1,0,50,1);
    EXPECT_EQ(testForest.regions[{0, 0}].getBurning(), true);
}
// Test simulation assigning stations
TEST(runSimulation, addStationSimulation)
{
    forest testForest(1, 1);
    testForest.runSimulation(1,1,50,1);
    EXPECT_EQ(testForest.regions[{0, 0}].getHasStation(), true);
}