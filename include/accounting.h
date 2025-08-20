#pragma once

#include "interfaces.h"
#include "thirdparty.h"

#include <chrono>
#include <unordered_map>

namespace BrakeParking {

class Accounting {
public:
    struct ParkingData {
        BarrierIdType EnteranceBarrier;
        BarrierIdType ExitBarrier;
        std::size_t PlaceNumber;
        std::chrono::time_point<std::chrono::system_clock> StartTime;
        std::chrono::time_point<std::chrono::system_clock> EndTime;
        bool isFreepay;
        bool isPayed;
    };

public:
    bool MoveIn(BarrierIdType id, VehicleNumberType vehicleNumber, std::size_t placeNumber);
    bool MoveOut(BarrierIdType id, VehicleNumberType vehicleNumber);
    void Print();

private:
    std::unordered_multimap<VehicleNumberType, ParkingData> m_accounting;

    BrakeParking3rd::PaymentSystem m_payment;
};

} // namespace BrakeParking