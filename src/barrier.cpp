#include "barrier.h"

#include <iostream>

namespace BrakeParking {

void Barrier::VehicleMove(VehicleNumberType vehicleNumber, MoveDirection md, std::size_t placeNumber) {
    m_notifier->Notify(m_id, md, vehicleNumber, placeNumber);
    m_hardware->OpenBarrier();
    std::cout << "[BrakeParking] Vehicle #" << vehicleNumber << " crossed barrier #" << m_id << " \n";
    m_hardware->CloseBarrier();
    std::cout << std::endl;
}


void Barrier::ManualControl(bool open) {
    if (open) {
        m_hardware->OpenBarrier();
        std::cout << "[BrakeParking] Barrier #" << m_id << " manually opened\n";
    }
    else {
        m_hardware->CloseBarrier();
        std::cout << "[BrakeParking] Barrier #" << m_id << " manually closed\n";
    }
}

} // namespace BrakeParking
