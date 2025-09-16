#include <gtest/gtest.h>
#include "include/area.h"

using namespace BrakeParking;

TEST(UnitTests, AreaId) {
    AreaIdType id {111};
    Area area(id, 100);
    
    EXPECT_EQ(area.GetId(), id);
}

TEST(UnitTests, AreaOccupied) {
    AreaIdType id {111};
    Area area(id, 100);
    const size_t count = 10;

    for (size_t i=1; i<=count; i++) {
        EXPECT_TRUE(area.CheckVacantPlace(i));
        area.EmplaceVehicle(1000+i, i);
        EXPECT_FALSE(area.CheckVacantPlace(i));
    }

    EXPECT_EQ(area.GetOccupiedCount(), count);
}

TEST(UnitTests, AreaVacant) {
    AreaIdType id {111};
    Area area(id, 100);
    const size_t count = 10;

    for (size_t i=1; i<=count; i++) {
        area.EmplaceVehicle(1000+i, i);
    }

    for (size_t i=1; i<=count; i++) {
        EXPECT_FALSE(area.CheckVacantPlace(i));
        area.DeleteVehicle(1000+i);
        EXPECT_TRUE(area.CheckVacantPlace(i));
    }

    EXPECT_EQ(area.GetOccupiedCount(), 0);

}

TEST(UnitTests, AreaReserve) {
    AreaIdType id {111};
    Area area(id, 100);
    const size_t count = 10;

    for (size_t i=1; i<=count; i++) {
        EXPECT_TRUE(area.CheckVacantPlace(i));
        area.ReservePlace(1000+i, i);
        EXPECT_FALSE(area.CheckVacantPlace(i));
    }

    EXPECT_EQ(area.GetOccupiedCount(), count);

    for (size_t i=1; i<=count; i++) {
        EXPECT_FALSE(area.CheckVacantPlace(i));
        area.EmplaceVehicle(1000+i, i);
        EXPECT_FALSE(area.CheckVacantPlace(i));
    }

    for (size_t i=1; i<=count; i++) {
        EXPECT_FALSE(area.CheckVacantPlace(i));
        area.DeleteVehicle(1000+i);
        EXPECT_TRUE(area.CheckVacantPlace(i));
    }

    EXPECT_EQ(area.GetOccupiedCount(), 0);
}
