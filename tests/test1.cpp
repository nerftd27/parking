#include <gtest/gtest.h>
#include "include/impl.h"

using namespace BrakeParking;

TEST(BrakeParkingTest, BaseImplTest) {
  Parking pk;
  pk.Construct();

  const size_t vehicleNum = 10;

  for (size_t i=1; i<=vehicleNum; i++) {
    pk.VehicleMoveIn(i*100 + i);
  }
  EXPECT_EQ(vehicleNum, pk.CheckOccupied());

  for (size_t i=1; i<=vehicleNum; i++) {
    pk.VehicleMoveOut(i*100 + i);
  }
  EXPECT_EQ(0, pk.CheckOccupied());
}
