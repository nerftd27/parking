#pragma once

#include "interfaces.h"
#include "area.h"
#include "accounting.h"
#include "accountingListener.h"
#include "barrier.h"

#include <unordered_map>

namespace BrakeParking {

class Parking : public IParking {
public:
    Parking() = delete;
    Parking (std::vector<BarrierIdType> barriers, std::vector<AreaIdType> areas);
    virtual ~Parking();

public:
    void VehicleMove(IParking::CustomerData& data) override;
    unsigned int GetOccupiedCount(AreaIdType areaId) const override;
    bool GetBarrierStatus(BarrierIdType barrierId) const override;
    void ManualControlBarrier(BarrierIdType barrierId, bool open) override;
    bool CheckVacantPlace(AreaIdType areaId, size_t place) const override;
    bool ReservePlace(AreaIdType areaId, VehicleNumberType vehicleNumber, size_t place) override;

private:
    std::unordered_map<BarrierIdType, Barrier> m_barriers;
    std::unordered_map<AreaIdType, Area> m_areas;

    std::shared_ptr<IListener> m_listener;
    std::shared_ptr<INotifier> m_notifier;
    std::unique_ptr<IAccounting> m_accounting;
};

} // namespace BrakeParking
