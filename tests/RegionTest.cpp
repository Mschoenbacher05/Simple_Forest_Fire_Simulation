#include "Region.h"
#include "gtest/gtest.h"
/*
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
*/
// Test fortify with a reasonable density
TEST(fortify, goodDensity)
{
    region testRegion(50, 90);
    testRegion.fortify();
    EXPECT_EQ(testRegion.getDensity(), 40);
}
// Test fortify with a low density
TEST(fortify, badDensity)
{
    region testRegion(50, 40);
    testRegion.fortify();
    EXPECT_EQ(testRegion.getDensity(), 0);
}
// Test fortify with a reasonable wetness
TEST(fortify, goodWetness)
{
    region testRegion(90, 50);
    testRegion.fortify();
    EXPECT_EQ(testRegion.getWetness(), 40);
}
// Test fortify with a low wetness
TEST(fortify, badWetness)
{
    region testRegion(40, 50);
    testRegion.fortify();
    EXPECT_EQ(testRegion.getWetness(), 0);
}
// Test extinguish on a lit region
TEST(extinguish, lit)
{
    region testRegion(50,50);
    testRegion.setFire(true);
    testRegion.extinguish();
    EXPECT_EQ(testRegion.getFire(), false);
}
// Test extinguish on a region that is not on fire
TEST(extinguish, unlit)
{
    region testRegion;
    testRegion.extinguish();
    EXPECT_EQ(testRegion.getFire(), false);
}
// Test update burning lit regions
TEST(update, decrease_burningLeft)
{
    region testRegion;
    testRegion.setFire(true);
    testRegion.update(50);
    EXPECT_EQ((testRegion.getBurningLeft() < 100), true);
}
// Test update burning lit regions
TEST(update, burnout)
{
    region testRegion;
    testRegion.setFire(true);
    testRegion.setBurningLeft(1);
    testRegion.update(50);
    EXPECT_EQ(testRegion.getFire(), false);
}
// Test update_Check_Burn respects NULL inpus
TEST(check_burn, NullInput)
{
    region testRegion;
    testRegion.update_Check_Burn(99999, NULL);
    EXPECT_EQ(testRegion.getFire(), false);
}
// Test update_Check_Burn does nothing when region not on fire
TEST(check_burn, NotOnFire)
{
    region testRegion;
    region* nonBurning;
    testRegion.update_Check_Burn(99999, nonBurning);
    EXPECT_EQ(testRegion.getFire(), false);
}
// Test update_Check_Burn catches fire when neighbor on fire
TEST(check_burn, onFire)
{
    region testRegion;
    region* burning;
    burning->setFire(true);
    testRegion.update_Check_Burn(99999, burning);
    EXPECT_EQ(testRegion.getFire(), true);
}
// Test update_Check_Burn decreases wetness when neighbor on fire
TEST(check_burn, decreaseWetness)
{
    region testRegion(100, 100);
    region* burning;
    burning->setFire(true);
    testRegion.update_Check_Burn(0, burning);
    EXPECT_EQ((testRegion.getWetness() < 100), true);
}