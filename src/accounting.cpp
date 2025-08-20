#include "accounting.h"
#include "freepays.h"

#include <iostream>

namespace BrakeParking {

bool Accounting::MoveIn(BarrierIdType id, VehicleNumberType vehicleNumber, std::size_t placeNumber) {
    auto now = std::chrono::system_clock::now();
    bool isFreepay = Freepays::GetInstance()->isFreepayVehicle(vehicleNumber);
    m_accounting.emplace(vehicleNumber, ParkingData{id, 0, placeNumber, now, now, isFreepay, false});

    std::time_t t_c = std::chrono::system_clock::to_time_t(now);
    std::cout << "[BrakeParking] Emplaced vehicle #" << vehicleNumber << " Freepay state: " << isFreepay << " occupied place #" << " at " << std::ctime(&t_c);
    return true;
}

bool Accounting::MoveOut(BarrierIdType id, VehicleNumberType vehicleNumber) {
    // Ищем неоплаченную запись на этот номер
    auto recordCount = m_accounting.count(vehicleNumber);
    std::unordered_multimap<VehicleNumberType, ParkingData>::iterator current = m_accounting.end();
    auto range = m_accounting.equal_range(vehicleNumber);
    for (auto it = range.first; it != range.second; ++it) {
        if (!it->second.isPayed)
            current = it;
            break;
    }
    if (current == m_accounting.end()) {    // какая то дичь, и запиcи о тачке нет
        std::cout << "[BrakeParking] Error: cant find record\n";
        return false;
    }

    // оплата
    current->second.EndTime = std::chrono::system_clock::now();
    if (!current->second.isFreepay) {
        // для упрощения считаем единицы времени единицами денежной валюты
        auto payment = std::chrono::duration_cast<std::chrono::seconds>(current->second.EndTime - current->second.StartTime);
        if (! m_payment.PayParking(vehicleNumber, payment.count())) {
            return false; // Оплата не прошла, ничего не делаем
        }
    }
    current->second.isPayed = true;

    current->second.ExitBarrier = id;
    std::time_t t_c = std::chrono::system_clock::to_time_t(current->second.EndTime);
    std::cout << "[BrakeParking] Vehicle #" << vehicleNumber << " exited at " << std::ctime(&t_c) << std::endl;
    return true;
}

void Accounting::Print() {
    std::cout << "[BrakeParking] ----- Start print accounting -----" << std::endl;
    for (const auto& it : m_accounting) {
        std::time_t tStart = std::chrono::system_clock::to_time_t(it.second.StartTime);
        std::time_t tEnd = std::chrono::system_clock::to_time_t(it.second.EndTime);
        std::cout << "[BrakeParking] ----- Vehicle #" << it.first << " place #" << it.second.PlaceNumber << " Freepay state: " << it.second.isFreepay << " Its payed: " << it.second.isPayed << " start time: " << std::ctime(&tStart) << " end time: " << std::ctime(&tEnd)<< std::endl;
    }
    std::cout << "[BrakeParking] ----- End print accounting -----" << std::endl;
}

} // namespace BrakeParking