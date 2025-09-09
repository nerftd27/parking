#include "thirdparty.h"

#include <iostream>

namespace BrakeParking3rd {

bool BarrierHardware::OpenBarrier() {
    m_isOpen = true;
    std::cout << "[ThirdParty] Barrier opened\n";
    return true;
}

bool BarrierHardware::CloseBarrier() {
    m_isOpen = false;
    std::cout << "[ThirdParty] Barrier closed\n";
    return true;
}

bool BarrierHardware::IsOpen() const {
    return m_isOpen;
}

bool PaymentSystem::PayParking(unsigned int number, unsigned int time) {
    // Execute payment
    // ...
    std::cout << "[ThirdParty] Vehicle #" << number << " payed units: " << time << std::endl;
    return true;
}

} // namespace BrakeParking3rd
