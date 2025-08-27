#pragma once

#include <cstdio>

namespace BrakeParking {

typedef unsigned int VehicleNumberType;
typedef unsigned int BarrierIdType;
typedef unsigned int AreaIdType;

class IParking {
public:
    virtual ~IParking() {}
public:
    enum class MoveDirection { In, Out };
public:
    virtual unsigned int CheckOccupied() const = 0;
    virtual void VehicleMove(VehicleNumberType vehicleNumber, BarrierIdType barrierId, MoveDirection ) = 0;
};

class IArea {
public:
    virtual ~IArea() {}
public:
    virtual AreaIdType GetId() const = 0;
    virtual std::size_t EmplaceVehicle(VehicleNumberType vehicleNumber) = 0;
    virtual std::size_t DeleteVehicle(VehicleNumberType vehicleNumber) = 0;
    virtual std::size_t CheckOccupied() const = 0;
};

class IBarrier {
public:
    virtual ~IBarrier() {}
public:
    virtual unsigned int GetId() const = 0;
    virtual void SetSideIn(IArea*) = 0;
    virtual void SetSideOut(IArea*) = 0;
    virtual void VehicleMove(VehicleNumberType vehicleNumber, IParking::MoveDirection md) = 0;
    virtual void ManualControl(bool open = true) = 0;
};

class IAccounting {
public:
    virtual ~IAccounting() {}
public:
    virtual bool MoveIn(BarrierIdType id, VehicleNumberType vehicleNumber, std::size_t placeNumber) =0;
    virtual bool MoveOut(BarrierIdType id, VehicleNumberType vehicleNumber) = 0;
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
    virtual void AddListener(IListener*) = 0;
    virtual void RemoveListener(IListener*) = 0;
    virtual void Notify(BarrierIdType id,  IParking::MoveDirection md, VehicleNumberType vehicleNumber,std::size_t placeNumber) = 0;
};

} // namespace BrakeParking
