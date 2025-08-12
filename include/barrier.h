#pragma once

#include "interfaces.h"
#include "thirdparty.h"

namespace BrakeParking {

class Barrier : public IBarrier {
public:
    Barrier() = default;    // TODO Remove

    Barrier(BarrierIdType id, IArea* areaIn = nullptr, IArea* areaOut = nullptr)
        : m_areaIn {areaIn}
        , m_areaOut {areaOut}
        , m_id(id)
    {
    }

    virtual ~Barrier() {};

    unsigned int GetId() const override { return m_id; }
    void SetSideIn(IArea* area) override { m_areaIn = area; }
    void SetSideOut(IArea* area) override { m_areaOut = area; }
    void VehicleMoveIn(unsigned int vehicleNumber) override;
    void VehicleMoveOut(unsigned int vehicleNumber) override;

private:
    unsigned int m_id;
    IArea* m_areaIn;
    IArea* m_areaOut;
    BrakeParking3rd::BarrierHardware m_hardware;
};
    
} // namespace BrakeParking
