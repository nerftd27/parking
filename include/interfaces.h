#pragma once

#include <cstdio>
#include <chrono>
#include <memory>

namespace BrakeParking {

typedef unsigned int VehicleNumberType;
typedef unsigned int BarrierIdType;
typedef unsigned int AreaIdType;

class IArea {
public:
    virtual ~IArea() {}
public:
    enum class StatusPlace { VACANT, OCCUPIED, RESERVED };
public:
    virtual AreaIdType GetId() const = 0;
    virtual std::size_t EmplaceVehicle(VehicleNumberType vehicleNumber, size_t place = 0) = 0;
    virtual std::size_t DeleteVehicle(VehicleNumberType vehicleNumber) = 0;
    virtual std::size_t GetOccupiedCount() const = 0;
    virtual bool CheckVacantPlace(size_t place) const = 0;
    virtual bool ReservePlace(VehicleNumberType vehicleNumber, size_t place) = 0;
};

class IParking {
public:
    virtual ~IParking() {}
public:
    enum class MoveDirection { In, Out };

    struct CustomerData {
        VehicleNumberType m_vehicleNumber;
        BarrierIdType m_barrierId;
        AreaIdType m_areaIn;
        AreaIdType  m_areaOut;
        MoveDirection m_direction;
        size_t m_place;
    };

public:
    virtual void VehicleMove(IParking::CustomerData& data) = 0;
    
    // Дилема: напрямую в интерфейсе паркинга делать методы, которые будут проксировать методы барьера, зоны тд.
    // Или же делать геттеры на константую ссылку барьера/зоны, и через них дергать нужные методы
    virtual void ManualControlBarrier(BarrierIdType barrierId, bool open) = 0;
    virtual bool GetBarrierStatus(BarrierIdType barrierId) const = 0;
    
    virtual unsigned int GetOccupiedCount(AreaIdType areaId) const = 0;
    virtual bool CheckVacantPlace(AreaIdType areaId, size_t place) const = 0;
    virtual bool ReservePlace(AreaIdType areaId, VehicleNumberType vehicleNumber, size_t place) = 0;

};

class IBarrier {
public:
    virtual ~IBarrier() {}
public:
    virtual unsigned int GetId() const = 0;
    virtual void VehicleMove(VehicleNumberType vehicleNumber, IParking::MoveDirection md, std::size_t placeNumber) = 0;
    virtual bool IsOpen() const = 0;
    virtual void ManualControl(bool open) = 0;
};

class IAccounting {
public:
    virtual ~IAccounting() {}
public:
    virtual bool MoveIn(BarrierIdType id, VehicleNumberType vehicleNumber, std::size_t placeNumber) =0;
    virtual bool MoveOut(BarrierIdType id, VehicleNumberType vehicleNumber) = 0;
};

class IAccountingDB {
public:
    virtual ~IAccountingDB() {}
public:
    virtual bool StartRecord(BarrierIdType id, VehicleNumberType vehicleNumber, std::size_t placeNumber, std::chrono::time_point<std::chrono::system_clock> StartTime) =0;
    virtual bool FinalizeRecord(BarrierIdType id, VehicleNumberType vehicleNumber, std::chrono::time_point<std::chrono::system_clock> EndTime) = 0;
    virtual size_t CalcPrice(VehicleNumberType vehicleNumber, std::chrono::time_point<std::chrono::system_clock> EndTime) = 0;
    virtual void Print() = 0;
};


class IListener {
public:
    virtual ~IListener() = default;
public:
    virtual void OnNotify(BarrierIdType id,  IParking::MoveDirection md, VehicleNumberType vehicleNumber,std::size_t placeNumber) = 0;
};

class INotifier {
public:
    virtual ~INotifier() = default;
public:
    virtual void AddListener(std::shared_ptr<IListener>) = 0;
    virtual void RemoveListener(std::shared_ptr<IListener>) = 0;
    virtual void Notify(BarrierIdType id,  IParking::MoveDirection md, VehicleNumberType vehicleNumber,std::size_t placeNumber) = 0;
};

} // namespace BrakeParking
