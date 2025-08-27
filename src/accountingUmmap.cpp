#include "accountingUmmap.h"

#include <iostream>

namespace BrakeParking {

bool AccountingImplUMMap::MoveIn(BarrierIdType id, VehicleNumberType vehicleNumber, std::size_t placeNumber) {
    auto now = std::chrono::system_clock::now();
    m_db.emplace(vehicleNumber, ParkingData{id, 0, placeNumber, now, now, false});

    std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    std::cout << "[BrakeParking] Emplaced vehicle #" << vehicleNumber << " occupied place #" << " at " << std::ctime(&t_c);
    return true;
}

bool AccountingImplUMMap::MoveOut(BarrierIdType id, VehicleNumberType vehicleNumber) {
    // Ищем неоплаченную запись на этот номер
    auto recordCount = m_db.count(vehicleNumber);
    std::unordered_multimap<VehicleNumberType, ParkingData>::iterator current = m_db.end();
    auto range = m_db.equal_range(vehicleNumber);
    for (auto it = range.first; it != range.second; ++it) {
        if (!it->second.isPayed)
            current = it;
            break;
    }
    if (current == m_db.end()) {    // какая то дичь, и запиcи о тачке нет
        std::cout << "[BrakeParking] Error: cant find record\n";
        return false;
    }
    
    current->second.ExitBarrier = id;

    // оплата
    current->second.EndTime = std::chrono::system_clock::now();
    // для упрощения считаем единицы времени единицами денежной валюты
    auto payment = std::chrono::duration_cast<std::chrono::seconds>(current->second.EndTime - current->second.StartTime);
    if (! m_payment->PayParking(vehicleNumber, payment.count())) {
        return false; // Оплата не прошла, надо звать охрану
    }
    current->second.isPayed = true;

    std::time_t t_c = std::chrono::system_clock::to_time_t(current->second.EndTime);
    std::cout << "[BrakeParking] Vehicle #" << vehicleNumber << " exited at " << std::ctime(&t_c) << std::endl;
    return true;
}

void AccountingImplUMMap::Print() {
    std::cout << "[BrakeParking] ----- Start print accounting -----" << std::endl;
    for (const auto& it : m_db) {
        std::time_t tStart = std::chrono::system_clock::to_time_t(it.second.StartTime);
        std::time_t tEnd = std::chrono::system_clock::to_time_t(it.second.EndTime);
        std::cout << "[BrakeParking] ----- Vehicle #" << it.first << " place #" << it.second.PlaceNumber << " Its payed: " << it.second.isPayed << " start time: " << std::ctime(&tStart) << " end time: " << std::ctime(&tEnd)<< std::endl;
    }
    std::cout << "[BrakeParking] ----- End print accounting -----" << std::endl;
}

} // namespace BrakeParking