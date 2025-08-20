// Основная реализация барьера
#pragma once

#include "accounting.h"
#include "interfaces.h"
#include "thirdparty.h"

namespace BrakeParking {

class Barrier : public IBarrier {

public:
    Barrier() = default;

    Barrier(BarrierIdType id, Accounting* acc, IArea* areaIn = nullptr, IArea* areaOut = nullptr)
        : m_id(id)
        , m_accounting(acc)
        , m_areaIn {areaIn}
        , m_areaOut {areaOut}
    {
    }

    BarrierIdType GetId() const override { return m_id; }
    void SetSideIn(IArea* area) override { m_areaIn = area; }
    void SetSideOut(IArea* area) override { m_areaOut = area; }
    void VehicleMove(VehicleNumberType vehicleNumber, IParking::MoveDirection md) override;

private:
    unsigned int m_id;
    IArea* m_areaIn;
    IArea* m_areaOut;

    BrakeParking3rd::BarrierHardware m_hardware;

    Accounting* m_accounting;
    
};
    
} // namespace BrakeParking
