#pragma once

#include "interfaces.h"
#include "thirdpartyAdapters.h"

#include <chrono>
#include <memory>
#include <unordered_map>

namespace BrakeParking {

class AccountingImplUMMap : public IAccounting{
public:
    AccountingImplUMMap()
        : m_payment(new PaymentSystemAdapter()) {
    }

    struct ParkingData {
        BarrierIdType EnteranceBarrier;
        BarrierIdType ExitBarrier;
        std::size_t PlaceNumber;
        std::chrono::time_point<std::chrono::system_clock> StartTime;
        std::chrono::time_point<std::chrono::system_clock> EndTime;
        bool isPayed;
    };

public:
    bool MoveIn(BarrierIdType id, VehicleNumberType vehicleNumber, std::size_t placeNumber);
    bool MoveOut(BarrierIdType id, VehicleNumberType vehicleNumber);
    void Print();

private:
    std::unordered_multimap<VehicleNumberType, ParkingData> m_db;
    std::unique_ptr<IPaymentSystem> m_payment;
};

} // namespace BrakeParking