#include "area.h"
#include <iostream>

namespace BrakeParking {

bool Area::EmplaceVehicle(VehicleNumberType vehicleNumber) {
    m_occupied++;
    auto now = std::chrono::system_clock::now();
    m_storage.emplace(vehicleNumber, ParkingData{m_occupied, now, now});
    
    std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    std::cout << "[BrakeParking] Vehicle #" << vehicleNumber << " occupied place #" << m_occupied << " at " << std::ctime(&t_c) << std::endl;
    return true;
}

bool Area::DeleteVehicle(VehicleNumberType vehicleNumber) {
    auto now = std::chrono::system_clock::now();
    m_storage[vehicleNumber].EndTime = now;
    
    // для упрощения считаем единицы времени единицами денежной валюты
    auto needPay = std::chrono::duration_cast<std::chrono::seconds>(m_storage[vehicleNumber].EndTime - m_storage[vehicleNumber].StartTime);
    if (! m_payment.PayParking(vehicleNumber, needPay.count())) {
        return false;
    }
    
    m_accounting.emplace(vehicleNumber, ParkingData(m_storage[vehicleNumber]));
    m_occupied--;
    m_storage.erase(vehicleNumber);

    std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    std::cout << "[BrakeParking] Vehicle #" << vehicleNumber << " exited at " << std::ctime(&t_c) << std::endl;
    return true;
}

unsigned int Area::CheckOccupied() const {
    std::cout << "[BrakeParking] Parking slots: " << m_capacity << " Occupied: " << m_storage.size() << std::endl;
    return m_storage.size();
}

void Area::PrintAccounting() {
    std::cout << "[BrakeParking] ----- Start print accounting -----" << std::endl;
    for (const auto& it : m_accounting) {
        std::time_t tStart = std::chrono::system_clock::to_time_t(it.second.StartTime);
        std::time_t tEnd = std::chrono::system_clock::to_time_t(it.second.EndTime);
        std::cout << "[BrakeParking] ----- Vehicle #" << it.first << " place #" << it.second.Place << " start time: " << std::ctime(&tStart) << " end time: " << std::ctime(&tEnd)<< std::endl;
    }
    std::cout << "[BrakeParking] ----- End print accounting -----" << std::endl;
}

} // namespace BrakeParking