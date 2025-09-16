#pragma once

#include "interfaces.h"
#include "thirdparty.h"

#include <vector>

namespace BrakeParking {

class Area : public IArea {
public:
    struct AreaRecord{
        VehicleNumberType m_vehicleNumber;
        IArea::StatusPlace m_status;
    };
public:
    Area() = default;
    Area(AreaIdType id, std::size_t capacity)
        : m_id(id)
        , m_occupied(0)
        , m_capacity(capacity)
        , m_storage(capacity, {0, IArea::StatusPlace::VACANT})
    {
    }

    AreaIdType GetId() const override { return m_id; }
    std::size_t EmplaceVehicle(VehicleNumberType vehicleNumber, size_t place = 0) override;
    std::size_t DeleteVehicle(VehicleNumberType vehicleNumber) override;
    std::size_t GetOccupiedCount() const override;
    bool CheckVacantPlace(size_t place) const override;
    bool ReservePlace(VehicleNumberType vehicleNumber, size_t place) override;

private:
    AreaIdType m_id;
    std::size_t m_capacity;
    std::size_t m_occupied;
    std::vector<AreaRecord> m_storage;
};

} // namespace BrakeParking
