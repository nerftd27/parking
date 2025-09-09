// Основная реализация барьера
#pragma once

#include "accounting.h"
#include "interfaces.h"
#include "thirdpartyAdapters.h"

namespace BrakeParking {

class Barrier : public IBarrier {

public:
    Barrier()
        : m_hardware(std::make_unique<BarrierHardwareAdapter>()) {
    }

    Barrier(BarrierIdType id, std::shared_ptr<INotifier> notifier)
        : m_id(id)
        , m_hardware(std::make_unique<BarrierHardwareAdapter> ()) {
        m_notifier = std::move(notifier);
    }

    // move-semantics due Barriers storages at Parking::m_barriers;
    Barrier(const Barrier& other) {
        m_id = other.m_id;
        m_notifier = other.m_notifier;
        m_hardware = std::make_unique<BarrierHardwareAdapter>();
    }

    Barrier& operator=(const Barrier& other) {
        m_id = other.m_id;
        m_notifier = other.m_notifier;
        m_hardware.reset();
        m_hardware = std::make_unique<BarrierHardwareAdapter> ();
        return *this;
    }

    Barrier(Barrier&& other) {
        m_id = other.m_id;
        m_notifier = std::move(other.m_notifier);
        m_hardware = std::move(other.m_hardware);
    }

    Barrier& operator=(Barrier&& other) {
        m_id = other.m_id;
        m_notifier = std::move(other.m_notifier);
        m_hardware.reset();
        m_hardware = std::move(other.m_hardware);
        return *this;
    }

    BarrierIdType GetId() const override { return m_id; }
    void VehicleMove(VehicleNumberType vehicleNumber, IParking::MoveDirection md, std::size_t placeNumber) override;
    bool IsOpen() const override { return m_hardware->IsOpen(); }
    void ManualControl(bool open) override;


private:
    unsigned int m_id;
    std::unique_ptr<IBarrierHardware> m_hardware;
    std::shared_ptr<INotifier> m_notifier;
};
    
} // namespace BrakeParking
