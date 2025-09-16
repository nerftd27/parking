#pragma once

#include "interfaces.h"

namespace BrakeParking {

class AccountingListener : public IListener {
public:
    AccountingListener(IAccounting& acc)
        : m_accounting(acc)
    {
    }

public:
    void OnNotify(BarrierIdType id,  MoveDirection md, VehicleNumberType vehicleNumber,std::size_t placeNumber) override {
        if (MoveDirection::In == md) {
            m_accounting.MoveIn(id, vehicleNumber, placeNumber);
        }
        else {
            m_accounting.MoveOut(id, vehicleNumber);
        }
    }

private:
    IAccounting& m_accounting;
};

} // namespace BrakeParking