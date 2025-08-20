#pragma once

#include <iostream>

namespace BrakeParking3rd {

class BarrierHardware {
public:
    inline bool OpenBarrier() {
        std::cout << "[ThirdParty] Barrier opened\n";
        return true;
    }

    inline bool CloseBarrier() {
        std::cout << "[ThirdParty] Barrier closed\n";
        return true;
    }
};

class PaymentSystem {
public:
    inline bool PayParking(BrakeParking::VehicleNumberType number, unsigned int time) {
        // Execute payment
        // ...
        std::cout << "[ThirdParty] Vehicle #" << number << " payed units: " << time << std::endl;
        return true;
    }
};

} // namespace BrakeParking3rd
