#include "barrier.h"
#include <iostream>

namespace BrakeParking {

void Barrier::VehicleMoveIn(VehicleNumberType vehicleNumber) {
    if (m_hardware.OpenBarrier())
    {
        if (m_areaOut) {
            m_areaOut->DeleteVehicle(vehicleNumber);
        }
        if (m_areaIn) {
            m_areaIn->EmplaceVehicle(vehicleNumber);
        }
        m_hardware.CloseBarrier(); // неисправность при закрытии пока опустим
    }
    else
    {
        std::cout << "[BrakeParking] Barrier #" << m_id << "malfunction\n";
        std::exit(111);
    }
}

void Barrier::VehicleMoveOut(VehicleNumberType vehicleNumber) {
    if (m_hardware.OpenBarrier())
    {
        if (m_areaIn) {
            m_areaIn->DeleteVehicle(vehicleNumber);
        }
        if (m_areaOut) {
            m_areaOut->EmplaceVehicle(vehicleNumber);
        }
        m_hardware.CloseBarrier();  // неисправность при закрытии пока опустим
    }
    else
    {
        std::cout << "[BrakeParking] Barrier #" << m_id << "malfunction\n";
        std::exit(111);
    }
}

} // namespace BrakeParking