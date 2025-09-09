#pragma once

#include "interfaces.h"
#include "thirdpartyInterfaces.h"

#include "thirdparty.h"

namespace BrakeParking {

class BarrierHardwareAdapter : public IBarrierHardware {
public:
    bool OpenBarrier() override {
        return m_hardware.OpenBarrier();
    }

    bool CloseBarrier() override {
        return m_hardware.CloseBarrier();
    }

    bool IsOpen() const override {
        return m_hardware.IsOpen();
    }

private:
    BrakeParking3rd::BarrierHardware m_hardware;
};

class PaymentSystemAdapter : public IPaymentSystem {
public:
    bool PayParking(VehicleNumberType number, unsigned int time) override {
        return m_payementSystem.PayParking(static_cast<unsigned int>(number), time);
    }

private:
    BrakeParking3rd::PaymentSystem m_payementSystem;
};

} // namespace BrakeParking