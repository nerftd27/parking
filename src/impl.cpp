#include "impl.h"

#include <iostream>

namespace BrakeParking {

void Portal::VehicleGoForward(unsigned int vehicleNumber) {
    if (m_areaB) {
        std::lock_guard<std::mutex> lg(m_areaBMutex);
        m_areaB->DeleteVehicle(vehicleNumber);
    }
    if (m_areaA) {
        std::lock_guard<std::mutex> lg(m_areaAMutex);
        m_areaA->EmplaceVehicle(vehicleNumber);
    }
    
}

void Portal::VehicleGoBack(unsigned int vehicleNumber) {
    if (m_areaA) {
        std::lock_guard<std::mutex> lg(m_areaAMutex);
        m_areaA->DeleteVehicle(vehicleNumber);
    }
    if (m_areaB) {
        std::lock_guard<std::mutex> lg(m_areaBMutex);
        m_areaB->EmplaceVehicle(vehicleNumber);
    }
}


bool Area::EmplaceVehicle(unsigned int vehicleNumber) {
    // пока опускаем ошибочный случай, когда номер уже зарегестрирована
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

} // namespace BrakeParking