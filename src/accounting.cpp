#include "accounting.h"

#include <iostream>

namespace BrakeParking {

bool Accounting::MoveIn(BarrierIdType id, VehicleNumberType vehicleNumber, std::size_t placeNumber) {
    auto now = std::chrono::system_clock::now();
    
    std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    std::cout << "[BrakeParking] New record parking: vehicle #" << vehicleNumber << " occupied place #" << placeNumber << " at " << std::ctime(&t_c);

    return  m_db->StartRecord(id, vehicleNumber, placeNumber, now);
}

bool Accounting::MoveOut(BarrierIdType id, VehicleNumberType vehicleNumber) {
    auto now = std::chrono::system_clock::now();
    
    auto price = m_db->CalcPrice(vehicleNumber, now);
    if (! m_payment->PayParking(vehicleNumber, price)) {
        return false; // Оплата не прошла, надо звать охрану
    }
    
    m_db->FinalizeRecord(id, vehicleNumber, now);
    std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    std::cout << "[BrakeParking] Vehicle #" << vehicleNumber << " exited at " << std::ctime(&t_c) << std::endl;
    return true;
}

} // namespace BrakeParking