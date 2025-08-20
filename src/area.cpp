#include "area.h"
#include <iostream>

namespace BrakeParking {

std::size_t Area::EmplaceVehicle(VehicleNumberType vehicleNumber) {
    m_occupied++;
    if (m_occupied <= m_capacity) {
        for (std::size_t i=0;i<m_capacity;i++) {
            if (m_storage.at(i) == 0) {
                m_storage.at(i) = vehicleNumber;
                return i+1; // парковочное место
            }
        }

    }
    return 0;
}

std::size_t Area::DeleteVehicle(VehicleNumberType vehicleNumber) {
    m_occupied--;
    for (std::size_t i=0;i<m_capacity;i++) {
            if (m_storage.at(i) == vehicleNumber) {
                m_storage.at(i) = 0;
                return i+1;
            }
        }
    return 0;
}

std::size_t Area::CheckOccupied() const {
    std::cout << "[BrakeParking] Parking slots: " << m_capacity << " Occupied: " << m_occupied << std::endl;
    return m_occupied;
}

} // namespace BrakeParking