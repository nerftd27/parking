#include "thirdparty.h"

#include <iostream>

namespace BrakeParking3rd {

bool BarrierHardware::OpenBarrier() {
    std::cout << "[ThirdParty] Barrier opened\n";
    return true;
}

bool BarrierHardware::CloseBarrier() {
    std::cout << "[ThirdParty] Barrier closed\n";
    return true;
}

bool PaymentSystem::PayParking(unsigned int number, unsigned int time) {
    // Execute payment
    // ...
    std::cout << "[ThirdParty] Vehicle #" << number << " payed units: " << time << std::endl;
    return true;
}

} // namespace BrakeParking3rd
