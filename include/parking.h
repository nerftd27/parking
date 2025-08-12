#pragma once

#include "interfaces.h"
#include "area.h"
#include "barrier.h"

#include <unordered_map>

namespace BrakeParking {

class Parking : public IParking {
public:
    Parking() = delete;
    Parking (std::vector<BarrierIdType> barriers);
    virtual ~Parking() {};

    void VehicleMove(VehicleNumberType vehicleNumber, BarrierIdType barrierId, IParking::MoveDirection md) override;

    unsigned int CheckOccupied() const override;

private:
    std::unordered_map<BarrierIdType, Barrier> m_barriers;
    std::unordered_map<AreaIdType, Area> m_areas;
};

} // namespace BrakeParking
