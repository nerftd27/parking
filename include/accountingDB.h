#pragma once

#include "interfaces.h"
#include <unordered_map>

namespace BrakeParking {

class AccountingDB : public IAccountingDB {
public:
    struct ParkingRecord {
        BarrierIdType EnteranceBarrier;
        BarrierIdType ExitBarrier;
        std::size_t PlaceNumber;
        std::chrono::time_point<std::chrono::system_clock> StartTime;
        std::chrono::time_point<std::chrono::system_clock> EndTime;
        bool isPayed;
    };

    using TypeDB = std::unordered_multimap<VehicleNumberType, ParkingRecord>;

public:
    bool StartRecord(BarrierIdType id, VehicleNumberType vehicleNumber, std::size_t placeNumber, std::chrono::time_point<std::chrono::system_clock> StartTime) override;
    bool FinalizeRecord(BarrierIdType id, VehicleNumberType vehicleNumber, std::chrono::time_point<std::chrono::system_clock> EndTime) override;
    size_t CalcPrice(VehicleNumberType vehicleNumber, std::chrono::time_point<std::chrono::system_clock> EndTime) override;
    void Print() override;

private:
    TypeDB::iterator FindUnpayedVehicle(VehicleNumberType vehicleNumber);

private:
     TypeDB m_storage;

};

} // namespace BrakeParking
