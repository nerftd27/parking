#pragma once

#include <iostream>

namespace BrakeParking3rd {

class BarrierHardware {
public:
    inline bool OpenBarrier() {
        std::cout << "[BrakeParking ThirdParty] Barrier opened\n";
        return true;
    }

    inline bool CloseBarrier() {
        std::cout << "[BrakeParking ThirdParty] Barrier closed\n";
        return true;
    }
};

class PaymentSystem {
public:
    inline bool PayParking(BrakeParking::VehicleNumberType number, unsigned int time) {
        // Execute payment
        // ...
        std::cout << "[BrakeParking ThirdParty] Vehicle #" << number << " payed units: " << time << std::endl;
        return true;
    }
};

} // namespace BrakeParking3rd
