#pragma once

#include <iostream>

namespace BrakeParking3rd {

class BarrierHardware {
public:
    bool OpenBarrier();
    bool CloseBarrier();
};

class PaymentSystem {
public:
    bool PayParking(unsigned int uuid, unsigned int time);
};

} // namespace BrakeParking3rd
