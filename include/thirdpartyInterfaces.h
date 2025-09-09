#pragma once

#include "interfaces.h"

namespace BrakeParking {
    
class IBarrierHardware {
public:
    virtual ~IBarrierHardware() {}
public:
    virtual bool OpenBarrier() = 0;
    virtual bool CloseBarrier() = 0;
    virtual bool IsOpen() const = 0;
};

class IPaymentSystem {
public:
    virtual ~IPaymentSystem() {}
public:
    virtual bool PayParking(VehicleNumberType number, unsigned int time) = 0;
};

} // namespace BrakeParking
