#include "barrierNotifier.h"
#include "parking.h"

namespace BrakeParking {

Parking::Parking(std::vector<BarrierIdType> barriers)
    : m_accounting(new AccountingImplUMMap())
    , m_listener(new AccountingListener(m_accounting))
    , m_notifier(new BarrierNotifier())
{
    m_notifier->AddListener(m_listener);

    AreaIdType areaId = 111;
    unsigned int capacity = 100;
    m_areas.emplace(areaId, Area(areaId, capacity));

    for (const auto& barrierId : barriers)
    {
        m_barriers.emplace(barrierId, Barrier(barrierId, m_notifier, &m_areas[areaId]));
    }
}

void Parking::VehicleMove(VehicleNumberType vehicleNumber, BarrierIdType id, IParking::MoveDirection md) {
    m_barriers[id].VehicleMove(vehicleNumber, md);
}

unsigned int Parking::CheckOccupied() const {
    return m_areas.begin()->second.CheckOccupied();
}

Parking::~Parking() {
    m_notifier->RemoveListener(m_listener);
    delete m_notifier;
    delete m_listener;
    delete m_accounting;
}

} // namespace BrakeParking