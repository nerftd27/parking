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
    auto endTime = std::chrono::system_clock::now();    
    auto startTime = m_db->GetStartTimeRecord(vehicleNumber);

    auto duratrion = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    if (! m_payment->PayParking(vehicleNumber, duratrion.count())) {
        return false; // Оплата не прошла, надо звать охрану
    }
    
    m_db->FinalizeRecord(id, vehicleNumber, endTime);
    std::time_t t_c = std::chrono::system_clock::to_time_t(endTime);
    std::cout << "[BrakeParking] Vehicle #" << vehicleNumber << " exited at " << std::ctime(&t_c) << std::endl;
    return true;
}

} // namespace BrakeParking