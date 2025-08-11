#pragma once

#include "interfaces.h"


#include <chrono>
#include <unordered_map>
#include <iostream>

namespace BrakeParking {

class Barrier : public IBarrier {
public:
    Barrier() = default;

    Barrier(BarrierIdType id, IArea* areaIn = nullptr, IArea* areaOut = nullptr)
        : m_areaIn {areaIn}
        , m_areaOut {areaOut}
        , m_id(id)
    {
    }

    virtual ~Barrier() {};

    unsigned int GetId() const override { return m_id; }
    void SetSideIn(IArea* area) override { m_areaIn = area; }
    void SetSideOut(IArea* area) override { m_areaOut = area; }
    void VehicleMoveIn(unsigned int vehicleNumber) override;
    void VehicleMoveOut(unsigned int vehicleNumber) override;

private:
    unsigned int m_id;
    IArea* m_areaIn;
    IArea* m_areaOut;
};

class Area : public IArea {
public:
    struct ParkingData {
        unsigned short Place;
        std::chrono::time_point<std::chrono::system_clock> StartOccupie;
        std::chrono::time_point<std::chrono::system_clock> EndOccupie;
    };

    Area() = default;
    Area(unsigned int id, size_t capacity)
        : m_id(id)
        , m_capacity(capacity)
        , m_occupied(0)
    {
        m_storage.reserve(m_capacity);
    }

    virtual ~Area() {};

    unsigned int GetId() const override { return m_id; }
    bool EmplaceVehicle(VehicleNumberType vehicleNumber) override;
    bool DeleteVehicle(VehicleNumberType vehicleNumber) override;
    unsigned int CheckOccupied() override;

private:
    AreaIdType m_id;
    size_t m_capacity;
    unsigned short m_occupied;  // будет так же выполнять роль номера занятого места для конкретной машины
    std::unordered_map<VehicleNumberType, ParkingData> m_storage;
    std::unordered_multimap<VehicleNumberType, ParkingData> m_accounting; // для бухгалтерии, хендлится когда машина уезжает с парковки
};

class Parking : public IParking {
public:
    void Construct(std::vector<BarrierIdType> barriers) override;
    virtual ~Parking() {};

    void VehicleMove(VehicleNumberType vehicleNumber, BarrierIdType barrierId, IParking::MoveDirection md) override;

    unsigned int CheckOccupied() override;

private:
    std::unordered_map<BarrierIdType, Barrier> m_barriers;
    std::unordered_map<AreaIdType, Area> m_areas;
};

} // namespace BrakeParking
