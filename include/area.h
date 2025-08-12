#pragma once

#include "interfaces.h"
#include "thirdparty.h"

#include <chrono>
#include <unordered_map>

namespace BrakeParking {

class Area : public IArea {
public:
    struct ParkingData {
        unsigned short Place;
        std::chrono::time_point<std::chrono::system_clock> StartTime;
        std::chrono::time_point<std::chrono::system_clock> EndTime;
    };

    Area() = default;
    Area(unsigned int id, size_t capacity)
        : m_id(id)
        , m_capacity(capacity)
        , m_occupied(0)
    {
        m_storage.reserve(m_capacity);
    }

    virtual ~Area() {
        PrintAccounting();
    }

    unsigned int GetId() const override { return m_id; }
    bool EmplaceVehicle(VehicleNumberType vehicleNumber) override;
    bool DeleteVehicle(VehicleNumberType vehicleNumber) override;
    unsigned int CheckOccupied() const override;

private:
    void PrintAccounting();

private:
    AreaIdType m_id;
    
    size_t m_capacity;
    unsigned short m_occupied;  // будет так же выполнять роль номера занятого места для конкретной машины
    
    BrakeParking3rd::PaymentSystem m_payment;
    std::unordered_map<VehicleNumberType, ParkingData> m_storage;
    std::unordered_multimap<VehicleNumberType, ParkingData> m_accounting; // для бухгалтерии, хендлится когда машина уезжает с парковки
};

} // namespace BrakeParking
