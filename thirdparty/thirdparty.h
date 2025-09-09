#pragma once

#include <iostream>

namespace BrakeParking3rd {

class BarrierHardware {
public:
    BarrierHardware()
        : m_isOpen(false) {
    }

public:
    bool OpenBarrier();
    bool CloseBarrier();
    bool IsOpen() const;

private:
    bool m_isOpen;
};

class PaymentSystem {
public:
    bool PayParking(unsigned int uuid, unsigned int time);
};

} // namespace BrakeParking3rd
