#include "impl.h"

namespace BrakeParking {

//------------------------------------------------------------------------------
// Class Barrier
//------------------------------------------------------------------------------
void Barrier::VehicleMoveIn(VehicleNumberType vehicleNumber) {
    if (m_areaOut) {
        m_areaOut->DeleteVehicle(vehicleNumber);
    }
    if (m_areaIn) {
        m_areaIn->EmplaceVehicle(vehicleNumber);
    }
}

void Barrier::VehicleMoveOut(VehicleNumberType vehicleNumber) {
    if (m_areaIn) {
        m_areaIn->DeleteVehicle(vehicleNumber);
    }
    if (m_areaOut) {
        m_areaOut->EmplaceVehicle(vehicleNumber);
    }
}

//------------------------------------------------------------------------------
// Class Area
//------------------------------------------------------------------------------
bool Area::EmplaceVehicle(VehicleNumberType vehicleNumber) {
    // пока опускаем ошибочный случай, когда номер уже зарегестрирован
    m_occupied++;
    auto now = std::chrono::system_clock::now();
    m_storage.emplace(vehicleNumber, ParkingData{m_occupied, now, now});
    
    std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    std::cout << "[BrakeParking] Vehicle #" << vehicleNumber << " occupied place #" << m_occupied << " at " << std::ctime(&t_c) << std::endl;
    return true;
}

bool Area::DeleteVehicle(VehicleNumberType vehicleNumber) {
    // пока опускаем ошибочный случай, когда номер еще не зарегистрирован
    m_occupied--;
    auto now = std::chrono::system_clock::now();
    m_storage[vehicleNumber].EndOccupie = now;
    m_accounting.emplace(vehicleNumber, ParkingData(m_storage[vehicleNumber]));
    
    m_storage.erase(vehicleNumber);

    std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    std::cout << "[BrakeParking] Vehicle #" << vehicleNumber << " exited at " << std::ctime(&t_c) << std::endl;
    return true;
}

unsigned int Area::CheckOccupied() {
    std::cout << "[BrakeParking] Parking slots: " << m_capacity << " Occupied: " << m_storage.size() << std::endl;
    return m_storage.size();
}

//------------------------------------------------------------------------------
// Class Parking
//------------------------------------------------------------------------------
void Parking::Construct(std::vector<BarrierIdType> barriers) {
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

unsigned int Parking::CheckOccupied() {
    return m_areas.begin()->second.CheckOccupied();
}
} // namespace BrakeParkingcd 