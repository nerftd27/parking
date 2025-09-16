#include "accountingDB.h"

#include <iostream>

namespace BrakeParking {

bool AccountingDB::StartRecord(BarrierIdType id, VehicleNumberType vehicleNumber, std::size_t placeNumber, std::chrono::time_point<std::chrono::system_clock> StartTime) {
    m_storage.emplace(vehicleNumber, ParkingRecord{id, 0, placeNumber, StartTime, StartTime, false});
    return true;
}

AccountingDB::TypeDB::iterator AccountingDB::FindUnpayedVehicle(VehicleNumberType vehicleNumber) {
    // Ищем неоплаченную запись на этот номер
    std::unordered_multimap<VehicleNumberType, ParkingRecord>::iterator current = m_storage.end();
    auto range = m_storage.equal_range(vehicleNumber);
    for (auto it = range.first; it != range.second; ++it) {
        if (!it->second.isPayed)
            current = it;
            break;
    }
    if (current == m_storage.end()) {    // какая то дичь, и запиcи о тачке нет
        std::cout << "[BrakeParking] Error: cant find record at DB\n";
    }
    return current;
}

std::chrono::time_point<std::chrono::system_clock> AccountingDB::GetStartTimeRecord(VehicleNumberType vehicleNumber) {
     auto current = FindUnpayedVehicle(vehicleNumber);
     if (current != m_storage.end()) {
        //auto payment = std::chrono::duration_cast<std::chrono::milliseconds>(EndTime - current->second.StartTime);
        return current->second.StartTime;
     }
     return std::chrono::system_clock::now();
}

bool AccountingDB::FinalizeRecord(BarrierIdType id, VehicleNumberType vehicleNumber, std::chrono::time_point<std::chrono::system_clock> EndTime) {
    auto current = FindUnpayedVehicle(vehicleNumber);
    if (current != m_storage.end()) {
        current->second.ExitBarrier = id;
        current->second.EndTime = EndTime;
        current->second.isPayed = true;
        std::time_t t_c = std::chrono::system_clock::to_time_t(current->second.EndTime);
        std::cout << "[BrakeParking] Finalize parking record: vehicle #" << vehicleNumber << " exited at " << std::ctime(&t_c) << std::endl;
        return true;
    }
    else
        return false;
}

void AccountingDB::Flush(std::ostream* st = &std::cout) {
    *st << "[BrakeParking] ----- Start print accountingDB -----" << std::endl;
    for (const auto& it : m_storage) {
        std::time_t tStart = std::chrono::system_clock::to_time_t(it.second.StartTime);
        std::time_t tEnd = std::chrono::system_clock::to_time_t(it.second.EndTime);
        *st << "[BrakeParking] ----- Vehicle #" << it.first << " place #" << it.second.PlaceNumber << " Its payed: " << it.second.isPayed << " start time: " << std::ctime(&tStart) << " end time: " << std::ctime(&tEnd)<< std::endl;
    }
    *st << "[BrakeParking] ----- End print accountingDB -----" << std::endl;
}

} // namespace BrakeParking