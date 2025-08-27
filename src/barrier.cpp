#include "barrier.h"

#include <iostream>

namespace BrakeParking {

void Barrier::VehicleMove(VehicleNumberType vehicleNumber, IParking::MoveDirection md) {
    IArea* areaA;
    IArea* areaB;

    if (md == IParking::MoveDirection::In) {
        areaA = m_areaIn;
        areaB = m_areaOut;
    }
    else
    {
        areaA = m_areaOut;
        areaB = m_areaIn;
    }

    // С той стороны, откуда тачка заезжает - удаляем ее
    if (areaB) {
        m_notifier->Notify(m_id,IParking::MoveDirection::Out, vehicleNumber, 0);
        areaB->DeleteVehicle(vehicleNumber);
        m_hardware->OpenBarrier();
        std::cout << "[BrakeParking] Vehicle #" << vehicleNumber << " crossed barrier #" << m_id << " to OUT\n";
    }

    // В ту сторону, куда заезжает - добавляем
    if (areaA) {
        auto placeNumber = areaA->EmplaceVehicle(vehicleNumber);
        if (placeNumber) {
            m_notifier->Notify(m_id,IParking::MoveDirection::In, vehicleNumber, placeNumber);
            std::cout << "[BrakeParking] Vehicle #" << vehicleNumber << " crossed barrier #" << m_id << " to IN\n";
            m_hardware->OpenBarrier();
        }
        else
        {
            std::cout << "[BrakeParking] Sorry, no free place for vehicle #" << vehicleNumber << std::endl;
            return;
        }
    }   

    m_hardware->CloseBarrier();
    std::cout << std::endl;
}


void Barrier::ManualControl(bool open /*=true*/) {
    if (open) {
        m_hardware->OpenBarrier();
    }
    else
    {
        m_hardware->CloseBarrier();
    }
}

} // namespace BrakeParking
