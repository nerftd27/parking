#pragma once

#include "interfaces.h"

#include <mutex>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <iostream>

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
    void SetSideA(IArea* area) override { m_areaA = area; }
    void SetSideB(IArea* area) override { m_areaB = area; }
    void VehicleMoveIn(unsigned int vehicleNumber) override;
    void VehicleMoveOut(unsigned int vehicleNumber) override;

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
    Area(unsigned int id, size_t capacity)
        : m_id(id)
        , m_capacity(capacity)
    {
        m_storage.reserve(m_capacity);
    }

    unsigned int GetId() const override { return m_id; }
    bool EmplaceVehicle(unsigned int vehicleNumber) override;
    bool DeleteVehicle(unsigned int vehicleNumber) override;
    unsigned int CheckOccupied() override;

private:
    unsigned int m_id;
    const size_t m_capacity;
    std::unordered_set<unsigned int> m_storage; // вместо сета может сделать мапу с пользовательской инфой типа время заезда, имя водителя и тд.
};

class Parking : public IParking {
public:
    void Construct() override;
    
    // Пока проксируем вызовы портала, но в сложном конфиге надо будет еще указывать сам портал
    void VehicleMoveIn(unsigned int vehicleNumber, unsigned int portalId = 0) override;
    void VehicleMoveOut(unsigned int vehicleNumber, unsigned int portalId = 0) override;

private:
    std::unordered_map<unsigned int, Portal> m_portals;
    std::unordered_map<unsigned int, Area> m_areas;
};

} // namespace BrakeParking
