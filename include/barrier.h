// Основная реализация барьера
#pragma once

#include "accountingUmmap.h"
#include "interfaces.h"
#include "thirdpartyAdapters.h"

#include <memory>

namespace BrakeParking {

class Barrier : public IBarrier {

public:
    Barrier()
        : m_hardware(new BarrierHardwareAdapter()) 
    {
    }

    Barrier(BarrierIdType id, INotifier* notifier, IArea* areaIn = nullptr, IArea* areaOut = nullptr)
        : m_id(id)
        , m_notifier(notifier)
        , m_areaIn {areaIn}
        , m_areaOut {areaOut}
        , m_hardware(new BarrierHardwareAdapter())
    {
    }

    BarrierIdType GetId() const override { return m_id; }
    void SetSideIn(IArea* area) override { m_areaIn = area; }
    void SetSideOut(IArea* area) override { m_areaOut = area; }
    void VehicleMove(VehicleNumberType vehicleNumber, IParking::MoveDirection md) override;
    void ManualControl(bool open = true) override;

private:
    unsigned int m_id;
    IArea* m_areaIn;
    IArea* m_areaOut;

    std::shared_ptr<IBarrierHardware> m_hardware;   // shared_ptr for move-semantics

    INotifier* m_notifier;
    
};
    
} // namespace BrakeParking
