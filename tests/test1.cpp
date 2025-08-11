#include <gtest/gtest.h>
#include "include/impl.h"

using namespace BrakeParking;

TEST(BrakeParkingTest, BaseImplTest) {
  Parking pk;
  unsigned int barrier0 = 10;  // Enterance
  unsigned int barrier1 = 20;  // Exit
  pk.Construct(std::vector<unsigned int> {barrier0, barrier1});
  
  const size_t vehicleNum = 10;

  for (size_t i=1; i<=vehicleNum; i++) {
    sleep(1);
    pk.VehicleMove(i*100 + i, barrier0, IParking::MoveDirection::In);
  }
  EXPECT_EQ(vehicleNum, pk.CheckOccupied());

  for (size_t i=1; i<=vehicleNum; i++) {
    sleep(1);
    pk.VehicleMove(i*100 + i, barrier1, IParking::MoveDirection::Out);
  }
  EXPECT_EQ(0, pk.CheckOccupied());
}
