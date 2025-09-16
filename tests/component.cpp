#include <gtest/gtest.h>
#include "include/parking.h"

using namespace BrakeParking;

TEST(BrakeParkingTest, BaseImplTest) {
  BarrierIdType barrier0 = 10;  // Enterance
  BarrierIdType barrier1 = 20;  // Exit
  AreaIdType area0 = 1000;

  Parking pk(std::vector<BarrierIdType> {barrier0, barrier1}, std::vector<AreaIdType> {area0});
  
  const size_t vehicleNum = 10;

  for (size_t i=1; i<=vehicleNum; i++) {
    VehicleNumberType number = i*100 + i;
    IParking::CustomerData data {number, barrier0, area0, 0, MoveDirection::In, 0};
    pk.VehicleMove(data);
  }
  EXPECT_EQ(vehicleNum, pk.GetOccupiedCount(area0));
  sleep(1);
  for (size_t i=1; i<=vehicleNum; i++) {
    VehicleNumberType number = i*100 + i;
    IParking::CustomerData data {number, barrier0, area0, 0, MoveDirection::Out, 0};
    pk.VehicleMove(data);
  }
  EXPECT_EQ(0, pk.GetOccupiedCount(area0));
}

TEST(BrakeParkingTest, ManualControl) {
  BarrierIdType barrier0 = 10;  // Enterance
  BarrierIdType barrier1 = 20;  // Exit
  AreaIdType area0 = 1000;

  Parking pk(std::vector<BarrierIdType> {barrier0, barrier1}, std::vector<AreaIdType> {area0});
  
  pk.ManualControlBarrier(barrier0, true);
  pk.ManualControlBarrier(barrier1, true);
  EXPECT_TRUE(IBarrier::BarrierStatus::Open == pk.GetBarrierStatus(barrier0));
  EXPECT_TRUE(IBarrier::BarrierStatus::Open == pk.GetBarrierStatus(barrier1));

  pk.ManualControlBarrier(barrier0, false);
  pk.ManualControlBarrier(barrier1, false);
  EXPECT_FALSE(IBarrier::BarrierStatus::Open == pk.GetBarrierStatus(barrier0));
  EXPECT_FALSE(IBarrier::BarrierStatus::Open == pk.GetBarrierStatus(barrier1));
}

TEST(BrakeParkingTest, RequestedPlace) {
  BarrierIdType barrier0 = 10;  // Enterance
  BarrierIdType barrier1 = 20;  // Exit
  AreaIdType area0 = 1000;

  Parking pk(std::vector<BarrierIdType> {barrier0, barrier1}, std::vector<AreaIdType> {area0});
  const size_t vehicleCount = 10;
  
  // Enterging vehicle to requested place:
  VehicleNumberType vehicleNum = 3333;
  size_t requestedPlace = 44;

  EXPECT_TRUE(pk.CheckVacantPlace(area0, requestedPlace));
  IParking::CustomerData data1 {vehicleNum, barrier0, area0, 0, MoveDirection::In, requestedPlace};
  pk.VehicleMove(data1);
  EXPECT_FALSE(pk.CheckVacantPlace(area0, requestedPlace));

  // some flow of different vehicle
  for (size_t i=1; i<=vehicleCount; i++) {
    VehicleNumberType number = i*100 + i;
    IParking::CustomerData data2 {number, barrier0, area0, 0, MoveDirection::In, 0};
    pk.VehicleMove(data2);
  }
  for (size_t i=1; i<=vehicleCount; i++) {
    VehicleNumberType number = i*100 + i;
    IParking::CustomerData data3 {number, barrier0, area0, 0, MoveDirection::Out, 0};
    pk.VehicleMove(data3);
  }

  EXPECT_FALSE(pk.CheckVacantPlace(area0, requestedPlace));

  // leaving vehicle at requested place
  IParking::CustomerData data4 {vehicleNum, barrier0, area0, 0, MoveDirection::Out, requestedPlace};
  pk.VehicleMove(data4);
  EXPECT_TRUE(pk.CheckVacantPlace(area0, requestedPlace));
}

TEST(BrakeParkingTest, ReserveTest) {
  BarrierIdType barrier0 = 10;  // Enterance
  BarrierIdType barrier1 = 20;  // Exit
  AreaIdType area0 = 1000;

  Parking pk(std::vector<BarrierIdType> {barrier0, barrier1}, std::vector<AreaIdType> {area0});

  VehicleNumberType vehicleNum = 3333;
  size_t reservedPlace = 44;

  EXPECT_TRUE(pk.CheckVacantPlace(area0, reservedPlace));
  pk.ReservePlace(area0, vehicleNum, reservedPlace);
  EXPECT_FALSE(pk.CheckVacantPlace(area0, reservedPlace));
  
  EXPECT_EQ(1, pk.GetOccupiedCount(area0));
  IParking::CustomerData data {vehicleNum, barrier0, area0, 0, MoveDirection::In, 0};
  pk.VehicleMove(data);
  EXPECT_EQ(1, pk.GetOccupiedCount(area0));

  IParking::CustomerData data1 {vehicleNum, barrier1, area0, 0, MoveDirection::Out, 0};
  pk.VehicleMove(data1);
  EXPECT_EQ(0, pk.GetOccupiedCount(area0));
  EXPECT_TRUE(pk.CheckVacantPlace(area0, reservedPlace));
}