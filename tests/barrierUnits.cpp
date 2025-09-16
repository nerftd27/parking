#include <gtest/gtest.h>
#include "include/barrier.h"

using namespace BrakeParking;

TEST(UnitTests, BarrierId) {
    BarrierIdType id {111};
    Barrier barrier(id);
    
    EXPECT_EQ(barrier.GetId(), id);
}
