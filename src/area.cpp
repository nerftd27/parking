#include "area.h"
#include <iostream>

namespace BrakeParking {

std::size_t Area::EmplaceVehicle(VehicleNumberType vehicleNumber, size_t place /*0*/) {
    // кейс с запрашиваемым местом.
    // Продуктовый вопрос -  а что делать, когда запрошенное место занято? Пока отдаем первое свободное
    if (place && CheckVacantPlace(place)) {
        
        m_storage.at(place-1).m_vehicleNumber = vehicleNumber;
        m_storage.at(place-1).m_status = IArea::StatusPlace::OCCUPIED;
        m_occupied++;
        return place;
    }

    // кейс с зарезервированным местом
    for (std::size_t i=0;i<m_capacity;i++) {
        if ((m_storage.at(i).m_status == IArea::StatusPlace::RESERVED) && m_storage.at(i).m_vehicleNumber == vehicleNumber) {
            m_storage.at(i).m_status = IArea::StatusPlace::OCCUPIED;
            return i+1;
        }
    }

    // основной кейс  добавления машины
    if (m_occupied < m_capacity) {    
        for (std::size_t i=0;i<m_capacity;i++) {
            if (m_storage.at(i).m_status == IArea::StatusPlace::VACANT) {
                m_storage.at(i).m_vehicleNumber = vehicleNumber;
                m_storage.at(i).m_status = IArea::StatusPlace::OCCUPIED;
                m_occupied++;
                return i+1; // парковочное место
            }
        }
    }
    return 0;
}

std::size_t Area::DeleteVehicle(VehicleNumberType vehicleNumber) {
    m_occupied--;
    for (std::size_t i=0;i<m_capacity;i++) {
            if (m_storage.at(i).m_vehicleNumber == vehicleNumber) {
                m_storage.at(i).m_vehicleNumber = 0;
                m_storage.at(i).m_status = IArea::StatusPlace::VACANT;
                return i+1;
            }
        }
    return 0;
}

std::size_t Area::GetOccupiedCount() const {
    std::cout << "[BrakeParking] Parking slots: " << m_capacity << " Occupied: " << m_occupied << std::endl;
    return m_occupied;
}


bool Area::CheckVacantPlace(size_t place) const {
    // ошибочный кейс, несуществующее место занято
    if ((place-1)>m_capacity) 
        return false;

    if (m_storage.at(place-1).m_status == IArea::StatusPlace::VACANT)
        return true;

    return false;
}

bool Area::ReservePlace(VehicleNumberType vehicleNumber, size_t place) {
    if (place && CheckVacantPlace(place)) {
        m_storage.at(place-1).m_vehicleNumber = vehicleNumber;
        m_storage.at(place-1).m_status = IArea::StatusPlace::RESERVED;
        m_occupied++;
        return true;
    }
    return false;
}

} // namespace BrakeParking