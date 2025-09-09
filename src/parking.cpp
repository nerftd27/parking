#include "barrierNotifier.h"
#include "parking.h"

namespace BrakeParking {

Parking::Parking(std::vector<BarrierIdType> barriers, std::vector<AreaIdType> areas)
{
    m_accounting = std::make_unique<Accounting>();
    m_listener = std::make_shared<AccountingListener>(*m_accounting);
    m_notifier = std::make_shared<BarrierNotifier>();

    m_notifier->AddListener(m_listener);

     
    for (const auto& barrierId : barriers)
    {
        m_barriers.emplace(std::make_pair(barrierId, Barrier(barrierId, m_notifier)));

    }

    unsigned int capacity = 100;
    for (const auto& areaId : areas)
    {
        m_areas.emplace(areaId, Area(areaId, capacity));
    }

}

void Parking::VehicleMove(IParking::CustomerData& data) {
    IArea* areaA = nullptr; 
    IArea* areaB = nullptr; 

    if (data.m_direction == IParking::MoveDirection::In) {
        areaA = data.m_areaIn ? &m_areas[data.m_areaIn] : nullptr;
        areaB = data.m_areaOut ? &m_areas[data.m_areaOut] : nullptr;
    }
    else
    {
        areaA = data.m_areaOut ? &m_areas[data.m_areaOut] : nullptr;
        areaB = data.m_areaIn ? &m_areas[data.m_areaIn] : nullptr;
    }

    // С той стороны, откуда тачка заезжает - удаляем ее
    if (areaB) {
        m_barriers[data.m_barrierId].VehicleMove(data.m_vehicleNumber, IParking::MoveDirection::Out, 0);
        areaB->DeleteVehicle(data.m_vehicleNumber);
    }
    // В ту сторону, куда заезжает - добавляем
    if (areaA) {
        auto placeNumber = areaA->EmplaceVehicle(data.m_vehicleNumber, data.m_place);
        if (placeNumber) {
            m_barriers[data.m_barrierId].VehicleMove(data.m_vehicleNumber, IParking::MoveDirection::In, placeNumber);
        }
        else
        {
            std::cout << "[BrakeParking] Sorry, no place for vehicle #" << data.m_vehicleNumber << std::endl;
            return;
        }
    }
}

unsigned int Parking::GetOccupiedCount(AreaIdType areaId) const {
    return m_areas.at(areaId).GetOccupiedCount();
}

void Parking::ManualControlBarrier(BarrierIdType id, bool open) {
    m_barriers.at(id).ManualControl(open);
}

bool Parking::GetBarrierStatus(BarrierIdType id) const {
    return m_barriers.at(id).IsOpen();
}

bool Parking::CheckVacantPlace(AreaIdType areaId, size_t place) const {
    return m_areas.at(areaId).CheckVacantPlace(place);
}

bool Parking::ReservePlace(AreaIdType areaId, VehicleNumberType vehicleNumber, size_t place) {
    return m_areas.at(areaId).ReservePlace(vehicleNumber, place);
}

Parking::~Parking() {
    m_notifier->RemoveListener(m_listener);
}

} // namespace BrakeParking