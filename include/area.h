#pragma once

#include "interfaces.h"
#include "thirdparty.h"

#include <vector>

namespace BrakeParking {

class Area : public IArea {
public:
    Area() = default;
    Area(unsigned int id, std::size_t capacity)
        : m_id(id)
        , m_occupied(0)
        , m_capacity(capacity)
        , m_storage(capacity, 0)
    {
    }

    AreaIdType GetId() const override { return m_id; }
    std::size_t EmplaceVehicle(VehicleNumberType vehicleNumber) override;
    std::size_t DeleteVehicle(VehicleNumberType vehicleNumber) override;
    std::size_t CheckOccupied() const override;

private:
    AreaIdType m_id;
    std::size_t m_capacity;
    std::size_t m_occupied;
    std::vector<VehicleNumberType> m_storage;
};

} // namespace BrakeParking
