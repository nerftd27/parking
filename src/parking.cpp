#include "parking.h"

namespace BrakeParking {

Parking::Parking(std::vector<BarrierIdType> barriers) {
    AreaIdType areaId = 111;
    unsigned int capacity = 100;
    m_areas.emplace(areaId, Area(areaId, capacity));

    for (const auto& barrierId : barriers)
    {
        m_barriers.emplace(barrierId, Barrier(barrierId, &m_areas[areaId]));
    }
}

void Parking::VehicleMove(VehicleNumberType vehicleNumber, BarrierIdType id, IParking::MoveDirection md) {
    if (IParking::MoveDirection::In == md) {
        m_barriers[id].VehicleMoveIn(vehicleNumber);
    }
    else
    {
        m_barriers[id].VehicleMoveOut(vehicleNumber);
    }
    
}

unsigned int Parking::CheckOccupied() const {
    return m_areas.begin()->second.CheckOccupied();
}

} // namespace BrakeParking