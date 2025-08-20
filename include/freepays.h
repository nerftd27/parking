// что то типа БД тачек с бесплатной стоянкой
#pragma once

#include "interfaces.h"
#include <unordered_set>

namespace BrakeParking {

class Freepays {
public:
    static Freepays* GetInstance() {
        static Freepays inst;
        return &inst;
    }

//private:  gtest'ам ну очень прям нужны ctor'ы, пока закоменнтил, будет инвалидный синглтон
    /*Freepays();
    ~Freepays();
    Freepays(const Freepays&);
    Freepays& operator=(const Freepays&);*/

public:
    void AddFreepayVehicle(VehicleNumberType vehicleNumber) {
        m_storage.insert(vehicleNumber);
    }

    void RemoveFreepayVehicle(VehicleNumberType vehicleNumber) {
        m_storage.erase(vehicleNumber);
    }

    bool isFreepayVehicle(VehicleNumberType vehicleNumber) {
        return m_storage.find(vehicleNumber) != m_storage.end();
    }

private:
    std::unordered_set<VehicleNumberType> m_storage;

};

} // namespace BrakeParking