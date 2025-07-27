#pragma once

#include "interfaces.h"

#include <mutex>
#include <vector>
#include <unordered_set>

namespace BrakeParking {

class Portal : public IPortal {
public:
    Portal() = delete;

    Portal(unsigned int id)
        : m_areaA {nullptr}
        , m_areaB {nullptr}
        , m_id(id)
    {
    }

    unsigned int GetId() const override { return m_id; }
    void SetSideA(IArea* area) override { m_areaA = area; m_areaA->connectPortal(this); }
    void SetSideB(IArea* area) override { m_areaB = area; m_areaB->connectPortal(this); }
    void VehicleGoForward(unsigned int vehicleNumber) override;
    void VehicleGoBack(unsigned int vehicleNumber) override ;

private:
    unsigned int m_id;
    IArea* m_areaA;
    IArea* m_areaB;
    std::mutex m_areaAMutex;
    std::mutex m_areaBMutex;
};

class Area : public IArea {
public:
    Area() = delete;
    Area(size_t capacity)
        : m_capacity(capacity)
    {
        m_storage.reserve(m_capacity);
    }

    void connectPortal(IPortal* portal) override {
        m_portals.push_back(portal);
    }

    bool EmplaceVehicle(unsigned int vehicleNumber) override;
    bool DeleteVehicle(unsigned int vehicleNumber) override;
    void CheckFill() override {};

private:
    const size_t m_capacity;
    std::vector<IPortal*> m_portals;
    std::unordered_set<unsigned int> m_storage; // вместо сета может сделать мапу с пользовательской инфой типа время заезда, имя водителя и тд.
};


} // namespace BrakeParking
