#include "impl.h"

namespace BrakeParking {

//------------------------------------------------------------------------------
// Class Portal
//------------------------------------------------------------------------------
void Portal::VehicleMoveIn(unsigned int vehicleNumber) {
    // фиксить deadlock наверно будем потом, когда дойдем до реализации с двумя площадками и порталом между ними
    if (m_areaB) {
        //std::lock_guard<std::mutex> lg(m_areaBMutex);
        m_areaB->DeleteVehicle(vehicleNumber);
    }
    if (m_areaA) {
        //std::lock_guard<std::mutex> lg(m_areaAMutex);
        m_areaA->EmplaceVehicle(vehicleNumber);
    }
}

void Portal::VehicleMoveOut(unsigned int vehicleNumber) {
    if (m_areaA) {
        //std::lock_guard<std::mutex> lg(m_areaAMutex);
        m_areaA->DeleteVehicle(vehicleNumber);
    }
    if (m_areaB) {
        //std::lock_guard<std::mutex> lg(m_areaBMutex);
        m_areaB->EmplaceVehicle(vehicleNumber);
    }
}

//------------------------------------------------------------------------------
// Class Area
//------------------------------------------------------------------------------
bool Area::EmplaceVehicle(unsigned int vehicleNumber) {
    // пока опускаем ошибочный случай, когда номер уже зарегестрирован
    m_storage.insert(vehicleNumber);
    std::cout << "[BrakeParking] Entered vehicle " << vehicleNumber << std::endl;
    return true;
}

bool Area::DeleteVehicle(unsigned int vehicleNumber) {
    // пока опускаем ошибочный случай, когда номер еще не зарегестрирован
    m_storage.erase(vehicleNumber);
    std::cout << "[BrakeParking] Exited vehicle " << vehicleNumber << std::endl;
    return true;
}

unsigned int Area::CheckOccupied() {
    std::cout << "[BrakeParking] Parking slots: " << m_capacity << " Occupied: " << m_storage.size() << std::endl;
    return m_storage.size();
}

//------------------------------------------------------------------------------
// Class Parking
//------------------------------------------------------------------------------
void Parking::Construct() {
    unsigned int portalId = 10;
    m_portals.emplace(portalId, Portal(portalId));
    
    unsigned int areaId = 2;
    unsigned int capacity = 100;
    m_areas.emplace(areaId, Area(areaId, capacity));

    m_portals[portalId].SetSideA(&m_areas[areaId]);
}

void Parking::VehicleMoveIn(unsigned int vehicleNumber, unsigned int /*portalId =0*/) {
    m_portals.begin()->second.VehicleMoveIn(vehicleNumber);
}

void Parking::VehicleMoveOut(unsigned int vehicleNumber, unsigned int /*portalId =0*/) {
    m_portals.begin()->second.VehicleMoveOut(vehicleNumber);
}

unsigned int Parking::CheckOccupied() {
    return m_areas.begin()->second.CheckOccupied();
}
} // namespace BrakeParkingcd 